#include <gtest/gtest.h>
#include <algorithm/algo_1.h>

using algo_one::Node;
using algo_one::numAverageSubtree;

// nullptr
TEST(ALGO_1, empty) {
    Node* _n = nullptr;
    
    ASSERT_TRUE(numAverageSubtree(_n) == 0);
}

// single node - zero value
TEST(ALGO_1, single_0) {
    Node n(0);

    ASSERT_TRUE(numAverageSubtree(&n) == 1);
}

// single node - non-zero value 
TEST(ALGO_1, single_n) {
    Node n(5);

    ASSERT_TRUE(numAverageSubtree(&n) == 1);
}

// basic binary tree with 3 nodes
TEST(ALGO_1, basic) {
    Node left(1);
    Node right(1);
    Node root(2, &left, &right);

    ASSERT_TRUE(numAverageSubtree(&root) == 2);
}

// linked list disguised as binary tree
TEST(ALGO_1, line) {
    Node four(5);                  // flr(5 / 1) = 5       1 
    Node three(4, &four, nullptr); // flr(5+4 / 2) = 4     2
    Node two(3, &three, nullptr);  // flr(5+4+3 / 3) = 4   2
    Node head(4, &two, nullptr);   // flr(5+4+3+4 / 4) = 4 3 

    ASSERT_EQ(numAverageSubtree(&head), 3);
}