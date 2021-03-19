#include "nmmintrin.h"
#include <immintrin.h>
#include <emmintrin.h>
#include <iostream>
#include <vector>

/* 
We have an array of strings 

*/

using namespace std;

int STRING_LENGTH = 16;

vector<string> get_first_vector()
{
    /* 
    This function will query dictionary.json and get the definition of the
    word. It will then parse through the definition and get all the senses.
    It will then store all those senes in the given vector: all_senses
    */
    // read a JSON file
    vector<string> vector1;

    vector1.push_back("Ball");
    vector1.push_back("Football");
    vector1.push_back("Soccer");
    vector1.push_back("Bottle");
    vector1.push_back("Box");
    vector1.push_back("Light");
    vector1.push_back("Ronaldo");
    vector1.push_back("Chair");

    vector1.push_back("Handstand");
    vector1.push_back("Wheelchair");
    vector1.push_back("Door");
    vector1.push_back("Play");
    vector1.push_back("Run");
    vector1.push_back("Dog");
    vector1.push_back("Cat");
    vector1.push_back("Bark");
    return vector1;
}

vector<string> get_second_vector()
{
    /* 
    This function will query dictionary.json and get the definition of the
    word. It will then parse through the definition and get all the senses.
    It will then store all those senes in the given vector: all_senses
    */
    // read a JSON file
    vector<string> vector2;

    vector2.push_back("Cattle");
    vector2.push_back("Bruce");
    vector2.push_back("Water");
    vector2.push_back("Football");
    vector2.push_back("There");
    vector2.push_back("Can");
    vector2.push_back("Jordan");
    vector2.push_back("Tinder");

    vector2.push_back("Smirnoff");
    vector2.push_back("Basket");
    vector2.push_back("Pig");
    vector2.push_back("Cow");
    vector2.push_back("Pakistan");
    vector2.push_back("London");
    vector2.push_back("Floor");
    vector2.push_back("Ceiling");
    return vector2;
}

vector<int> get_int_vector(vector<string> strings)
{
    vector<int> ints;

    for (int i = 0; i < STRING_LENGTH; i++) {
        string curr_str = strings[i];
        cout << curr_str << "\n";
        int curr_str_len = curr_str.size() + 1;
        for (int j = 0; j < curr_str_len; j++) {
            cout << curr_str[j] << "\n";
            cout << (int) curr_str[j] << "\n";
            ints.push_back((int) curr_str[j]);

        }

            
    }

    while (ints.size() % 16 != 0) {
        ints.push_back(-1);
    }

    cout << ints.size() << "<<<<<<<<\n";
        

    return ints;
}

int main(void)
{
    /* 
    Have to convert the first vector into an array of ints. Afterwards, 
    have to load the ints into a register.

    */

    vector<string> vector1 = get_first_vector();
    vector<string> vector2 = get_second_vector();

    for (int i = 0; i < STRING_LENGTH; i++)
        cout << vector1[i] << "\n";
    
    cout << "*******\n";

    for (int i = 0; i < STRING_LENGTH; i++)
        cout << vector2[i] << "\n";

    vector<int> int_vector1 = get_int_vector(vector1);
    vector<int> int_vector2 = get_int_vector(vector2);

    std::vector<int> sub(&int_vector1[0],&int_vector1[16]);

    cout << "Size of vector 1 is: " << sub.size() << "\n";

    for (int i = 0; i < sub.size(); i++) {
        cout << sub[i] << "\n";
    } 

     __m128i a = _mm_setr_epi32(0, 1, 2, 3);

    // __m128i vector1_register = _mm_load_epi32((__m128i const*) &sub );
    
    // _mm512_load_epi32((__m512i const*) &sub);

    return 0;



    // int array[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    // // char* test = "test6789tettffss";
    // // for (int i = 0; i < 17; i++) {
    // //     array.push_back((int) test[i]);
    // //     std::cout << "Test[i] is " << test[i] << "\n";
    // // }
    // // std::cout << "Original word is " << test << " and the size is: " << sizeof(test)/sizeof(char) <<"\n";
    
    // // __m256i chunk = _mm256_loadu_epi16 ((__m128i const*)&array);
    // // __m128i chunk = _mm_load_epi32( &array );
    // __m128i chunk = _mm_load_epi32(&array);

    // int* translated = (int*) &chunk;

    // std::cout << "Translated word is " << translated << " and the size is: " << sizeof(translated)/sizeof(char) <<"\n";
    // return 0;    
}