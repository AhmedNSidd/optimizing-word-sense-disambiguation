#include "picojson.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main(void) {
    picojson::value v;
    std::ifstream i("final_dictionary/st.json");
    i >> v;
    // std::cout << v.get("stock") << std::endl;

    std::vector<std::string> items; 
    std::vector<picojson::value> tmp;
    tmp = v.get("stock").get<picojson::array>();
    for (int i = 0; i < tmp.size(); i++) {
        items.push_back(tmp[i].get<std::string>());
    }
}