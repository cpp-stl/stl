#include <iostream>
#include <chrono>
#include <stl/vector.h>

template <typename T>
using vector = stl::vector<T>;

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    vector<int> a;
    std::cout << a.size() << ", " << a.capacity() << std::endl;

    int b = a.at(100);

    std::cout << b << std::endl;

    for (int i = 0; i < 1000000; ++i)
    {
        a.resize(i);
        a.push_back(i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << ms << "ms" << std::endl;

    return 0;
}
