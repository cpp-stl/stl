#include "stl/assert.h"
#include "stl/vector.h"

void test_types() { 
    stl::vector<stl::vector<int>> a;
}

void test_default_constructor() {
    stl::vector<int> a;
    ASSERT_EQUAL(a.size(), 0);
    ASSERT_EQUAL(a.capacity(), 0);
    a.push_back(1);
}

void test_copy_constructor() {
    stl::vector<int> a;
    a.push_back(0);
    a.push_back(1);
    a.push_back(2);

    stl::vector<int> b(a);
    ASSERT_EQUAL(a.size(), 3);
    ASSERT_EQUAL(a.capacity(), 4);

     for (int i = 0; i < 3; i++) {
        ASSERT_EQUAL(a.at(i), i);
    }
}

void test_specialized_constructor() {
    stl::vector<int> a(5, 10);
    ASSERT_EQUAL(a.size(), 5);
    ASSERT_EQUAL(a.capacity(), 5);

    for (int i = 0; i < 5; i++) {
        ASSERT_EQUAL(a.at(i), 10);
    }

    stl::vector<int> b(5);
    ASSERT_EQUAL(a.size(), 5);
    ASSERT_EQUAL(a.capacity(), 5);

    for (int i = 0; i < 5; i++) {
        ASSERT_EQUAL(b.at(i), 0);
    }
}

void test_destructor() {
    {
        stl::vector<int> a;
    }
}

void test_initializer_list()
{
    stl::vector<int> a{1,2,3,4,5};

    ASSERT_EQUAL(a.size(), 5);
    ASSERT_EQUAL(a.capacity(), 5);

    for(size_t i = 0; i < 5; i++)
    {
        ASSERT_EQUAL(a[i], i + 1);
    }
}

void test_resize() {
    stl::vector<int> a;
    a.resize(100, 100);
    ASSERT_EQUAL(a.capacity(), 100);
    ASSERT_EQUAL(a.size(), 100);

    a.resize(10);
    ASSERT_EQUAL(a.capacity(), 100);
    ASSERT_EQUAL(a.size(), 10);
}

void test_reserve() {
    stl::vector<int> a;
    a.reserve(50);
    ASSERT_EQUAL(a.capacity(), 50);
    ASSERT_EQUAL(a.size(), 0);

    a.reserve(10);
    ASSERT_EQUAL(a.capacity(), 50);
    ASSERT_EQUAL(a.size(), 0);
}

void test_index_out_of_bounds()
{
    stl::vector<int> a;
    //technically no error?
    a[-1];
}

int main() {
    test_default_constructor();
    test_copy_constructor();
    test_specialized_constructor();
    test_initializer_list();
    
    test_types();
    test_resize();
    test_reserve();
}
