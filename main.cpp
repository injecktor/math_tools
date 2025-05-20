#include <iostream>

#include "math_tools.hpp"

using namespace std;
using namespace math_tools;

int main() {
    int a = 0x11223344;
    printf("%08x\n", htol32(a));


    return 0;
}