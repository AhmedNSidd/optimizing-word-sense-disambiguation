/* 
* Simplified Sense Word Disambiguation algorithm written by Ahmed Siddiqui and
* Jordan Kirchner based off of Michael Lesk's simplified algorithm
* (https://en.wikipedia.org/wiki/Lesk_algorithm#Simplified_Lesk_algorithm)
*/

/*

Algorithm: 
function SIMPLIFIED LESK(word,sentence) returns best sense of word
    best-sense <- most frequent sense for word
    max-overlap <- 0
    context <- set of words in sentence
    for each sense in senses of word do
        signature <- set of words in the gloss and examples of sense
        overlap <- COMPUTEOVERLAP (signature,context)
        if overlap > max-overlap then
            max-overlap <- overlap
            best-sense <- sense
end return (best-sense)

*/

#include <chrono>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>
#include "wsd_v2.hpp"

using json = nlohmann::json;
using namespace std;


string remove_punctuation(string str) {
    string result;
    std::remove_copy_if(str.begin(), str.end(),            
                std::back_inserter(result), //Store output           
                ::ispunct);

    return result;
}


int hash_string(string str) {
    /* 
    Need to lowercase first, and then hash it. 
    */
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::hash<std::string> hasher;
    return hasher(str);
}


int compute_overlap(string sense, set<int> context) {
    /*
    In this function, we want to go tokenize the sense. After that, we want to compute the
    */    
    int overlap = 0;
    set<int> sense_tokens = tokenize_string(sense);
    
    vector<int> vector_sense(sense_tokens.begin(), sense_tokens.end());
    vector<int> vector_context(context.begin(), context.end());
    
    auto const sense_len = vector_sense.size();
    auto const context_len = vector_context.size();

    for (int i = 0; i < sense_len; i++) {
        // cout << hash_word_dictionary[vector_sense[i]] << "\n";
        for (int j = 0; j < context_len; j++) {
            // cout << hash_word_dictionary[vector_context[j]] << "\n";
            if (vector_sense[i] == vector_context[j]) {
                overlap++;
            }
        }
    }

    return overlap;
}

vector<string> get_all_senses(string word) {
    /* 
    This function will query dictionary.json and get the definition of the
    word. It will then parse through the definition and get all the senses.
    It will then store all those senes in the given vector: all_senses
    */
    // read a JSON file
    string dictionary_name = "final_dictionary/";
    dictionary_name += word[0];
    if (word[1] != '\0')
        dictionary_name += word[1];
    dictionary_name += ".json";

    std::ifstream i(dictionary_name);
    json j;
    i >> j;

    return j[word];
}

set<int> get_word_set(string word, string sentence) {
    set<int> words = tokenize_string(sentence);
    words.erase(hash_string(word));
    return words;
}

set<int> tokenize_string(string sentence) {
    stringstream stream(sentence);
    set<int> words;
    string tmp;
    while (getline(stream, tmp, ' ')) {
        words.insert(hash_string(remove_punctuation(tmp)));
    }
    
    return words;
}


string simplified_wsd(string word, string sentence) {
    string best_sense;
    int max_overlap = 0;
    set<int> context = get_word_set(word, sentence);// This is the set of words in a sentence excluding the word itself.
    vector<string> all_senses= get_all_senses(word);
        // TIMING BEGIN
    auto const start = chrono::steady_clock::now();
    for (int i = 0; i < all_senses.size(); i++) {
        int overlap = compute_overlap(all_senses[i], context);
        if (overlap > max_overlap) {
            max_overlap = overlap;
            best_sense = all_senses[i];
            
            // cout << "best_sense: " << best_sense << "\n";
        }
    }
    auto const end = chrono::steady_clock::now();
    
    cout << "Time to run compute overlap was: " << chrono::duration <double, milli> (end - start).count() << " ms" << endl;


    return best_sense;
}

int main(int argc, char ** argv)
{
    /*
     cout << "Find the best sense of the word 'stock' in the following sentence:\n\tI'm expecting to make a lot of money from the stocks I'm investing in using my bank account.\n";
     cout << "The best sense of the word stock in our example is:\n" << simplified_wsd("stock", "I'm expecting to make a lot of money from the stocks I'm investing in using my bank account.") << "\n";
     */
    
    // auto start = chrono::steady_clock::now();
    
    simplified_wsd("set", "It was a great day of tennis. Game, set, match");
    
    // auto end = chrono::steady_clock::now();
    // auto diff = end - start;
    
    // cout << "Total time to run was: " << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    
     return 0;
}
