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

#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>
#include "simplified_wsd.hpp"

using json = nlohmann::json;
using namespace std;


int compute_overlap(string sense, set<string> context) {
    /*
    In this function, we want to go tokenize the sense. After that, we want to compute the
    */
    int overlap = 0;
    set<string> sense_tokens = tokenize_string(sense);
    for (set<string>::iterator i = sense_tokens.begin(); i != sense_tokens.end(); i++) {
        for (set<string>::iterator j = context.begin(); j != context.end(); j++) {
            if (boost::iequals(*i, *j)) {
                overlap++;
            }
        }
    }
    return overlap;
}

void get_all_senses(string word, vector<string> &all_senses) {
    /* 
    This function will query dictionary.json and get the definition of the
    word. It will then parse through the definition and get all the senses.
    It will then store all those senes in the given vector: all_senses
    */
    // read a JSON file
    std::ifstream i("dictionary.json");
    json j;
    i >> j;

    vector<string> definitions = j[word];
    for (int i = 0; i < definitions.size(); i++) {
        all_senses.push_back(definitions[i]);
    }
}

set<string> get_word_set(string word, string sentence) {
    set<string> words = tokenize_string(sentence);
    words.erase(word);
    return words;
}

set<string> tokenize_string(string sentence) {
    stringstream stream(sentence);
    set<string> words;
    string tmp;
    while (getline(stream, tmp, ' ')) {
        words.insert(tmp);
    }
    
    return words;
}


string simplified_wsd(string word, string sentence) {
    string best_sense;
    int max_overlap = 0;
    set<string> context = get_word_set(word, sentence);// This is the set of words in a sentence excluding the word itself.
    vector<string> all_senses; // This is all the senses of the word.
    get_all_senses(word, all_senses);
    for (int i = 0; i < all_senses.size(); i++) {
        int overlap = compute_overlap(all_senses[i], context);
        if (overlap > max_overlap) {
            max_overlap = overlap;
            best_sense = all_senses[i];
        }
    }

    return best_sense;
}
