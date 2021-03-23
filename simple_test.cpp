#include "nmmintrin.h"
#include <immintrin.h>
#include <emmintrin.h>
#include <x86intrin.h>
#include <iostream>
#include <vector>

/* 
We have an array of strings 

*/

using namespace std;

int STRING_LENGTH = 16;

// vector<string> get_first_vector()
// {
//     /* 
//     This function will query dictionary.json and get the definition of the
//     word. It will then parse through the definition and get all the senses.
//     It will then store all those senes in the given vector: all_senses
//     */
//     // read a JSON file
//     vector<string> vector1;

//     vector1.push_back("Ball");
//     vector1.push_back("Football");
//     vector1.push_back("Soccer");
//     vector1.push_back("Bottle");
//     vector1.push_back("Box");
//     vector1.push_back("Light");
//     vector1.push_back("Ronaldo");
//     vector1.push_back("Chair");

//     vector1.push_back("Handstand");
//     vector1.push_back("Wheelchair");
//     vector1.push_back("Door");
//     vector1.push_back("Play");
//     vector1.push_back("Run");
//     vector1.push_back("Dog");
//     vector1.push_back("Cat");
//     vector1.push_back("Bark");
//     return vector1;
// }

// vector<string> get_second_vector()
// {
//     /* 
//     This function will query dictionary.json and get the definition of the
//     word. It will then parse through the definition and get all the senses.
//     It will then store all those senes in the given vector: all_senses
//     */
//     // read a JSON file
//     vector<string> vector2;

//     vector2.push_back("Cattle");
//     vector2.push_back("Bruce");
//     vector2.push_back("Water");
//     vector2.push_back("Football");
//     vector2.push_back("There");
//     vector2.push_back("Can");
//     vector2.push_back("Jordan");
//     vector2.push_back("Tinder");

//     vector2.push_back("Smirnoff");
//     vector2.push_back("Basket");
//     vector2.push_back("Pig");
//     vector2.push_back("Cow");
//     vector2.push_back("Pakistan");
//     vector2.push_back("London");
//     vector2.push_back("Floor");
//     vector2.push_back("Ceiling");
//     return vector2;
// }

// vector<int> get_int_vector(vector<string> strings)
// {
//     vector<int> ints;

//     for (int i = 0; i < STRING_LENGTH; i++) {
//         string curr_str = strings[i];
//         int curr_str_len = curr_str.size() + 1;
//         for (int j = 0; j < curr_str_len; j++) {
//             ints.push_back((int) curr_str[j]);

//         }

            
//     }

//     while (ints.size() % 16 != 0) {
//         ints.push_back(-1);
//     }

        

//     return ints;
// }

// int get_hash(string str) {
//     std::hash<std::string> hasher;
//     int hashed = hasher(str); //returns std::size_t
//     return hashed;
// }

int main(void)
{
    /* 
    Have to convert the first vector into an array of ints. Afterwards, 
    have to load the ints into a register.

    */


    vector<int> vector1;

    vector1.push_back(1);
    vector1.push_back(2);
    vector1.push_back(3);
    vector1.push_back(4);

    vector<int> vector2;

    vector2.push_back(2);
    vector2.push_back(2);
    vector2.push_back(3);
    vector2.push_back(1);

    __m128i a = _mm_loadu_si128((__m128i const*) &vector1[0]);
    __m128i b = _mm_loadu_si128((__m128i const*) &vector2[0]);


    __m128i equality = _mm_cmpeq_epi32 (a, b);

    cout << _mm_extract_epi32(equality, 3) << "\n";


    // //  __m128i a = _mm_setr_epi32(0, 1, 2, 3);
    // __m128i values = _mm_loadu_si128((__m128i const*) &vector1[0] );

    // __m128i result = _mm_hadd_epi32(values, values);
    // result = _mm_hadd_epi32(result, result);

    // int first_value = _mm_extract_epi32(result, 0);

    // cout << first_value << "\n";
    
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