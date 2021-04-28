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
#include <set>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include "picojson.h"
#include <boost/algorithm/string.hpp>
#include "wsd.hpp"

using namespace picojson;
using namespace std;


int compute_overlap(string sense, set<string> context) {
    /*
    In this function, we want to go tokenize the sense. After that, we want to compute the
    */
   
    auto const cache_line_size = 64u;
    auto const tile_size = cache_line_size / 8; // median word size is 4.7 characters, so we expect to easily fit 8 words into the cache.
    
    int overlap = 0;
    set<string> sense_tokens = tokenize_string(sense);
    
    std::vector<string> vector_sense(sense_tokens.begin(), sense_tokens.end());
    std::vector<string> vector_context(context.begin(), context.end());
    
    auto const n = vector_sense.size();
    auto const o = vector_context.size();
    
    for(auto i = 0u; i < n; i++){
        for (auto j = 0u; j < o; j++){
            if (boost::iequals(vector_sense[i], vector_context[j]))
                overlap++;
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
        all_senses.push_back(tmp[i].get<std::string>());
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

int main(void )
{
    /*
     cout << "Find the best sense of the word 'stock' in the following sentence:\n\tI'm expecting to make a lot of money from the stocks I'm investing in using my bank account.\n";
     cout << "The best sense of the word stock in our example is:\n" << simplified_wsd("stock", "I'm expecting to make a lot of money from the stocks I'm investing in using my bank account.") << "\n";
     */
    
    // auto start = chrono::steady_clock::now();
    
    simplified_wsd("set", "It was a great day of tennis. Game, set, match. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent in nunc ac metus condimentum volutpat. Vivamus ornare orci nec congue cursus. Curabitur ultricies sem eget metus lacinia, faucibus sagittis odio porta. Cras mollis malesuada justo sit amet fringilla. Fusce dolor est, pulvinar sit amet eleifend sollicitudin, pulvinar vel libero. Nunc nulla diam, vulputate in cursus in, faucibus non arcu. Phasellus semper tempus maximus. Mauris turpis velit, pulvinar eget tempor sit amet, pharetra id ante. Pellentesque blandit ac magna vel condimentum. Aenean aliquet pellentesque turpis sit amet eleifend. In dolor ligula, tempor non lacus euismod, blandit iaculis ex.Vestibulum maximus facilisis condimentum. Maecenas pretium malesuada nisi. Duis nec turpis vel justo mattis facilisis. Sed vulputate nulla in diam ultricies mollis vitae non dui. Nam nec tellus interdum lorem suscipit mollis. Aenean et nisl euismod, blandit augue sit amet, pellentesque tellus. Curabitur maximus mollis nibh eget mattis. Duis varius hendrerit euismod. Ut ac ipsum imperdiet, pretium purus et, aliquet risus. Nam nisi mauris, maximus ac venenatis a, lacinia ut nibh. Praesent id ligula volutpat, mollis orci ac, iaculis ligula. Aliquam pretium tortor posuere urna vestibulum efficitur. Suspendisse aliquet diam nec lectus consectetur, ut condimentum est consectetur. Vivamus blandit interdum leo quis tincidunt.Suspendisse potenti. Duis volutpat justo at eros lacinia feugiat. In sit amet volutpat turpis. Nulla tempor imperdiet elit, in vulputate urna placerat eu. Integer congue dolor nisi, vitae sagittis purus eleifend id. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Ut libero arcu, tempus sollicitudin leo a, euismod maximus ex. Nunc varius aliquet metus, a fermentum ligula sagittis vitae.Integer hendrerit nunc eget urna rutrum, ut viverra ligula tincidunt. Nulla viverra orci lectus, ut varius erat viverra ut. Proin ac lacus congue, bibendum lorem ut, placerat ex. Mauris a rhoncus sapien. Pellentesque vel ultricies tortor, at hendrerit metus. Nunc cursus commodo facilisis. In tempor neque ut condimentum cursus. Mauris ut erat facilisis, pulvinar lectus vitae, euismod erat. Nullam feugiat sollicitudin finibus. Cras ante quam, tincidunt sed ultrices quis, rutrum vel nibh. Suspendisse eu velit vitae tellus porttitor mollis a eget lectus. Sed vel nisl sed dui elementum feugiat. Fusce fermentum ex vel mi pellentesque, a ultrices erat vehicula. Aenean auctor erat eu justo tristique, eget fringilla augue commodo.Phasellus vel risus ante. Cras tristique neque velit, et suscipit metus maximus ut. Proin quis sem purus. Maecenas pharetra at felis eget pellentesque. Fusce blandit libero eget massa efficitur semper. Nulla eget euismod enim. Sed id enim ac eros luctus sodales in maximus mi.");
    
    // auto end = chrono::steady_clock::now();
    // auto diff = end - start;
    
    // cout << "Total time to run was: " << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    
     return 0;
}