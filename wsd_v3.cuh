#ifndef SIMPLIFIED_WSD_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define SIMPLIFIED_WSD_H

using namespace std;

int hash_string(string str);
string remove_punctuation(string str);
__global__ void compute_overlap(const string *senses, const string *context, int *overlaps, int senses_size, int context_size);
vector<string> get_all_senses(string word);
vector<int> get_word_set(string word, string sentence);
vector<int> tokenize_string(string sentence) ;
string simplified_wsd(string word, string sentence);

#endif
