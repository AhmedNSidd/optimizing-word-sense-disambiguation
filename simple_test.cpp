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

int main(void)
{
    vector<int> a(10, 0);
    vector<int> b(10, 1);
    vector<int> c(10, 0);

    for (int i = 0; i < 10; i++) {
        c[i] += (a[i] == b[i]);
        cout << c[i] << endl;
    }
}