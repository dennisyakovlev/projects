#include <gtest/gtest.h>
#include <algorithm/algo_2.h>
#include <string>

using algo_two::numSplits;
using namespace std;

// single
TEST(ALGO_2, single) {
    string s(" ");

    ASSERT_TRUE(numSplits(s) == 0);
}

// basic
TEST(ALGO_2, basic) {
    string s("abcd");

    ASSERT_TRUE(numSplits(s) == 1);
}

// less basic
TEST(ALGO_2, less_basic) {
    string s("aacaba");

    ASSERT_TRUE(numSplits(s) == 2);
}