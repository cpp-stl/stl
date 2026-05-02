#include "vector"
#include <iostream>
#include <vector>
int main()
{
    std::vector<int> a;
    a.push_back(1);
    a.clear();
    std::cout << (a.begin().base() == nullptr ? "true" : "false") << std::endl;
}
