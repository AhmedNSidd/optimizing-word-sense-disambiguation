using namespace std;

int compute_overlap(string sense, set<string> context) ;
void get_all_senses(string word, vector<string> &all_senses);
set<string> get_word_set(string word, string sentence) ;
set<string> tokenize_string(string sentence);