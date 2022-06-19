#include "test.h"
#include <items.h> // so long as isnt included in test.h, is private
#include <iostream>

#define MY_MACRO

namespace test_two {

void func() {
    std::cout << "test_two lib\n";

#ifdef TEST_TWO_MACRO
    std::cout << "private macro TEST_TWO_MACRO\n";
#endif
}

}