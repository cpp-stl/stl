#include <vector>
#include <iostream>
#include <chrono>

int main()
{
    /*
    std::vector<int> a(100);
    std::cout << a.capacity() << std::endl;

    a.push_back(10); 

    a.reserve(11);
    std::cout << a.size() << ", " << a.capacity() << std::endl;

    a.resize(201);
    std::cout << a.size() << ", " << a.capacity() << std::endl;
    */

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> a;
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