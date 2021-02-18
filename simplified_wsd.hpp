#ifndef SIMPLIFIED_WSD_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define SIMPLIFIED_WSD_H

using namespace std;

int compute_overlap(string sense, set<string> context);
void get_all_senses(string word, vector<string> &all_senses);
set<string> get_word_set(string word, string sentence);
set<string> tokenize_string(string sentence);
string simplified_wsd(string word, string sentence);

#endif
