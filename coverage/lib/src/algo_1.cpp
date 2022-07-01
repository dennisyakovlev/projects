#include <algorithm/algo_1.h>

namespace algo_one {

__Info __helper(_Node _n_) {
    if (_n_ == nullptr) return { 0,0,0 };
    
    // post order traversal
    __Info l = __helper(_n_->_l);
    __Info r = __helper(_n_->_r);
    int sz = 1 + l.sz + r.sz; // current tree size
    int s = _n_->v + l.s + r.s; // sum of current tree
    
    // is the current node equal to floored average of subtree? 
    return {sz, s, (s / sz == _n_->v) + l.n + r.n};
}

int numAverageSubtree(_Node _n_) {
    return __helper(_n_).n;
}

};