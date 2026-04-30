#include "stl/vector.h"
#include <cstdio>
#include <iostream>
#include <chrono>

template <typename T>
using vector = stl::vector<T>;

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    vector<int> a;

    int b = 0;
    a.push_back(5);
    stl::pop_back_status c = a.pop_back(b);

    switch (c) {
        case stl::pop_back_status::success:
            std::printf("YAYYY %d\n", b);
            break;
            
        default:
            std::printf("AWWWWW\n");
    }

    std::cout << a.size() << ", " << a.capacity() << std::endl;

    a.resize(5);
    a[0] = 100;

    std::cout << a.capacity() << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << ms << "ms" << std::endl;

    return 0;
}