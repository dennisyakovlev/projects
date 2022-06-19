#include <iostream>
#include <test/test.h>
#include <test_two/test.h>

int main(int argc, char const *argv[]) {
    
    std::cout << "hiii\n";

    test::func();
    test_two::func();

#ifdef TEST_TWO_MACRO
    std::cout << "TEST_TWO_MACRO does propigate\n";
#endif

    return 0;
}
