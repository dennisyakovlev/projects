#include <algorithm/algo_2.h>
#include <unordered_map>
#include <unordered_set>
#include <string>

namespace algo_two {

int numSplits(std::string& s) {
    std::unordered_set<char> first;
    std::unordered_map<char, int> second;
    for (std::string::size_type i = 0; i != s.size(); ++i) {
        second.insert_or_assign(s[i], i);
    }

    int total = 0;
    for (std::string::size_type i = 0; i != s.size(); ++i) {
        auto c = s[i];
        first.insert(c);
        if (second.contains(c) && second.find(c)->second == i) second.erase(c);
        if (first.size() == second.size()) ++total;
    }

    return total;
}

};