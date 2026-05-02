#include "stl/vector.h"
#include "vector"
#include <iostream>
int main()
{
    stl::vector<int> a{1,2,3,4};
    stl::vector<int>::iterator begin = a.begin();
    stl::vector<int>::iterator end = a.end();
    for(auto i = begin; i != end; i++)
    {
        int val = *i;
        std::cout << val << std::endl;
    }
}
