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
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include "picojson.h"
#include "wsd_v3.cuh"

using namespace picojson;
using namespace std;

#define MAX_SENSE_SIZE 100


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


__global__ 
void compute_overlap(const int *senses, const int *context, int *overlaps, int senses_size, int context_size) {
    int sense_index = (threadIdx.x + blockIdx.x * blockDim.x) * MAX_SENSE_SIZE;
    if (sense_index < senses_size) {
        for (int i = sense_index; i < sense_index + MAX_SENSE_SIZE; i++) {
            if (senses[i] == -1) {
                break;
            }
            for (int j = 0; j < context_size; j++) {
                overlaps[sense_index/MAX_SENSE_SIZE] += (senses[i] == context[j]);
            }
        }
    }
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
    value v;
    i >> v;

    std::vector<std::string> items; 
    std::vector<picojson::value> tmp = v.get(word).get<picojson::array>();
    for (int i = 0; i < tmp.size(); i++) {
        items.push_back(tmp[i].get<std::string>());
    }

    return items;
}

vector<int> get_word_set(string word, string sentence) {
    vector<int> words = tokenize_string(sentence);
    words.erase(std::remove(words.begin(), words.end(), hash_string(word)), words.end());
    return words;
}

vector<int> tokenize_string(string sentence) {
    stringstream stream(sentence);
    set<int> words;
    string tmp;
    while (getline(stream, tmp, ' ')) {
        words.insert(hash_string(remove_punctuation(tmp)));
    }
    
    return vector<int>(words.begin(), words.end());
}

// We need to turn compute overlap into a kernel function.
// We need to get rid of the for loop, create dev_senses, dev_context, 
// and send in a results array to compute_overlap, 
// cudaMalloc, cudaMemcpy, cudaFree them up, then 
// find the max result from that array 
string simplified_wsd(string word, string sentence) {
    string best_sense;
    int max_overlap = 0;
    vector<int> context = get_word_set(word, sentence);// This is the set of words in a sentence excluding the word itself.
    vector<string> all_senses = get_all_senses(word);
    vector<int> hashed_sense_tokens; 
    for (int i = 0; i < all_senses.size(); i++) {
        // for every sense, we want to tokenize the string, then for every token, we want to add that to a new vector. 
        vector<int> tokens = tokenize_string(all_senses[i]);
        for (int j = 0; j < tokens.size(); j++) {
            hashed_sense_tokens.push_back(tokens[j]);
        }
        while (hashed_sense_tokens.size() % MAX_SENSE_SIZE != 0) {
            hashed_sense_tokens.push_back(-1);
        }
    }
    int *dev_senses;
    int *dev_context;
    int *dev_results;
    int overlaps[all_senses.size()];
    int const block_size = 128;
    cudaMalloc((void **) &dev_senses, all_senses.size() * MAX_SENSE_SIZE * sizeof(hashed_sense_tokens[0]));
    cudaMalloc((void **) &dev_context, context.size() * sizeof(context[0]));
    cudaMalloc((void **) &dev_results, all_senses.size() * sizeof(int));

    cudaMemcpy(dev_senses, &hashed_sense_tokens[0], hashed_sense_tokens.size() * sizeof(hashed_sense_tokens[0]), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_context, &context[0], context.size() * sizeof(context[0]), cudaMemcpyHostToDevice);
    auto const num_blocks = ceil(all_senses.size() / static_cast<float>(block_size));
    auto const start = chrono::steady_clock::now();

    compute_overlap<<<num_blocks, block_size>>>(dev_senses, dev_context, dev_results, all_senses.size() * MAX_SENSE_SIZE, context.size());
    cudaMemcpy(overlaps, dev_results, all_senses.size() * sizeof(int), cudaMemcpyDeviceToHost);

    for (int i = 0; i < all_senses.size(); i++) {
        if (overlaps[i] > max_overlap) {
            best_sense = all_senses[i];
            max_overlap = overlaps[i];
        }
    }

    auto const end = chrono::steady_clock::now();

    cudaFree(dev_results);
    cudaFree(dev_context);
    cudaFree(dev_senses);
    
    cout << "Time to run compute overlap was: " << chrono::duration <double, milli> (end - start).count() << " ms" << endl;
    cout << "best sense is " << best_sense << endl;
    return best_sense;
}

int main(int argc, char ** argv)
{
    /*
     cout << "Find the best sense of the word 'stock' in the following sentence:\n\tI'm expecting to make a lot of money from the stocks I'm investing in using my bank account.\n";
     cout << "The best sense of the word stock in our example is:\n" << simplified_wsd("stock", "I'm expecting to make a lot of money from the stocks I'm investing in using my bank account.") << "\n";
     */
    
    // auto start = chrono::steady_clock::now();
    
    simplified_wsd("set", "My opponent won the first set in our tennis game.");
    
    // auto end = chrono::steady_clock::now();
    // auto diff = end - start;
    
    // cout << "Total time to run was: " << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    
     return 0;
}
