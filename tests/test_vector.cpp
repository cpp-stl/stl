#include <stl/vector.h>
#include <test/common.h>

TEST("default constructor", [](){
    stl::vector<int> a;
    ASSERT_EQUAL(a.size(), 5);
    ASSERT_EQUAL(a.capacity(), 0);
});

TEST("specialized constructor", [](){
    stl::vector<int> a(5, 10);
    ASSERT_EQUAL(a.size(), 5);
    ASSERT_EQUAL(a.capacity(), 5);

    for (int i = 0; i < 5; i++) {
        ASSERT_EQUAL(a.at(i), 10);
    }

    stl::vector<int> b(5);
    ASSERT_EQUAL(b.size(), 5);
    ASSERT_EQUAL(b.capacity(), 5);

    for (int i = 0; i < 5; i++) {
        ASSERT_EQUAL(b.at(i), 0);
    }
});

void test_specialized_constructor() {
    stl::vector<int> a(5, 10);
    ASSERT_EQUAL(a.size(), 5);
    ASSERT_EQUAL(a.capacity(), 5);

    for (int i = 0; i < 5; i++) {
        ASSERT_EQUAL(a.at(i), 10);
    }

    stl::vector<int> b(5);
    ASSERT_EQUAL(b.size(), 5);
    ASSERT_EQUAL(b.capacity(), 5);

    for (int i = 0; i < 5; i++) {
        ASSERT_EQUAL(b.at(i), 0);
    }

    stl::vector<void*> c(5);
    ASSERT_EQUAL(c.size(), 5);
    ASSERT_EQUAL(c.capacity(), 5);

    for (int i = 0; i < 5; i++) {
        ASSERT_NULL(c.at(i));
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

void test_iterator()
{
    stl::vector<int> a{1, 2, 3, 4, 5};

    int i = 0;
    for (auto j = a.begin(); j != a.end(); j++) {
        ASSERT_EQUAL(*j, a[i]);
        i++;
    }

    stl::vector<int> b;
    ASSERT_NULL(b.begin());
    ASSERT_NULL(b.end());

    stl::vector<int> c;
    c.push_back(1);
    c.clear();

    ASSERT_NULL(c.begin().base());
}


int main() {
    //test_default_constructor();
    //test_copy_constructor();
    //test_specialized_constructor();
    //test_initializer_list();
    
    //test_types();
    //test_resize();
    //test_reserve();
    //test_iterator();

    RUN_TESTS();
}
