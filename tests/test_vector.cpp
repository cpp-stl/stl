#include "stl/assert.h"
#include "stl/exceptions.h"
#include "stl/vector.h"

void test_types() {
    stl::vector<stl::vector<int>> a;
    ASSERT_NOT_THROWS([]() { throw stl::bad_alloc(); });
}

void test_constructor() {
    stl::vector<int> a;
    ASSERT_EQUAL(a.size(), 0);
    ASSERT_EQUAL(a.capacity(), 0);
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

int main() {
    test_types();
    test_constructor();
    test_resize();
    test_reserve();
}
