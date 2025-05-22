#include <iostream>

#include "math_tools.hpp"

using namespace std;
using namespace math_tools;

int main() {
    unsigned char a[255] = "AAAAAAAAAA";
    printf("%08x\n", crc32_fast(a, 10));


    return 0;
}