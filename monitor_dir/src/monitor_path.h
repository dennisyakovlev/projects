#include <string>

namespace monitor {

constexpr int buf_sz = 256; 

void monitor (std::string&);
void monitor(const std::string&);
void monitor(std::string&&);

void monitor(std::string*);
void monitor(const char*);

};