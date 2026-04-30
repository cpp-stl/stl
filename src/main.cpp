#include "stl/exceptions.h"
#include "stl/vector.h"
#include <iostream>
#include <chrono>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    stl::vector<stl::vector<int>> a;
    std::cout << a.size() << ", " << a.capacity() << std::endl;

    for (int i = 0; i < 1000000; ++i)
    {
        a.resize(i);
        for (int j = 0; j < 100; ++j) {
        }
        
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << ms << "ms" << std::endl;

    return 0;
}