#pragma once
#include <initializer_list>

/* begins with _ is pointer
   begins with __ is "internal"
   ends with _, function param 
*/

namespace algo_one {

struct Node;

using _Node = Node*;

struct __Info {
    // sz - current size of tree
    // s  - current sum
    // n  - number of nodes which passed
    int sz, s, n;

    __Info() : sz(0), s(0), n(0) {}
    // not very good idea, but for convience
    __Info(std::initializer_list<int> l_) : sz(*l_.begin()), s(*(l_.begin() + 1)), n(*(l_.begin() + 2)) {}
};

struct Node {
public:
    using t = int;
    using _p = Node*;
    
    t v; // value of node
    _p _l; // left child
    _p _r; // right child

    Node(t v_) : v(v_), _l(nullptr), _r(nullptr) {}
    Node(t v_, _p _l_, _p _r_) : v(v_), _l(_l_), _r(_r_) {}
};

int numAverageSubtree(_Node);

};