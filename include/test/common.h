#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <string>
#include <format>
#include <stl/vector.h>
#include "stl/common.h"
#include "stl/exceptions.h"

//const std::map<const char *, int> tests;
namespace test {
    struct __test {
        const char* fileName;
        const char* testName;
        _FUNCTION_POINTER<void> fnc;
        bool passed;
    };
    inline stl::vector<__test> __tests;
    class __test_secret_exception : public stl::exception {
        public:
        __test_secret_exception(int line = __LINE__, const char* what = nullptr) : line_(line), message_(what) {};
        const int line() const noexcept { return this->line_; }
        const char * what() const noexcept override { return this->message_ ? this->message_ : "test failed"; }
        private:
            int line_;
            const char* message_;
    };
    inline void __assert(bool condition, std::string message, int line) {
    if (condition) {
        // throw
        throw test::__test_secret_exception(line, message.c_str());
    }
}
};  // namespace test

#define ASSERT_EQUAL(a, b) {test::__assert(a == b, std::format("got {}, expected {}", std::to_string(a), std::to_string(b)), \
                __LINE__);}
#define ASSERT_NOT_EQUAL(a, b) {test::__assert(a == b, std::format("got {}, expected {}", std::to_string(a), std::to_string(b)), \
                __LINE__);}
#define ASSERT_NULL(a) \
    test::__assert(a == nullptr, "expected nullptr, got defined", __LINE__);
#define ASSERT_NOT_NULL(a) \
    test::__assert(a != nullptr, "expected defined, got nullptr", __LINE__);
#define ASSERT_THROWS(function)                                      \
    try {                                                            \
        function();                                                  \
        test::__assert(false, "expected to throw", __LINE__); \
    } catch (stl::exception & e) {                                   \
        test::__assert(true, nullptr, __LINE__);              \
    }
#define ASSERT_NOT_THROWS(function)                                      \
    try {                                                                \
        function();                                                      \
        test::__assert(true, nullptr, __LINE__, __FILE__);                  \
    } catch (stl::exception & e) {                                       \
        test::__assert(false, "expected to not throw", __LINE__, __FILE__); \
    }

#define TEST_CAT_(a, b) a##b                                                                                                                                 
#define TEST_CAT(a, b)  TEST_CAT_(a, b)

#define TEST(name, fnc)\
      static const int TEST_CAT(_test_reg_, __COUNTER__) = []{\
          test::__tests.push_back(test::__test{__FILE_NAME__, name, fnc, false});  \
          return 0;\
      }()\

inline void run_tests(const char* fileName = __FILE_NAME__) {
    int testsPassed = 0;
    int testsFailed = 0;
    for (auto test = test::__tests.begin(); test != test::__tests.end(); test++) {
        if (test.base()->fileName == fileName) {
            //std::printf("\nRunning test \"%s\"\n", test.base()->testName);
            if (test.base()->fnc) {
                try {
                    test.base()->fnc();
                    testsPassed++;
                } catch (test::__test_secret_exception& exception) {
                    testsFailed++;
                    std::printf("\033[3;41;30m[assertion] %s: %s:%d\033[0m\n", exception.what(), fileName, exception.line());
                }
            }
        }
    }

    std::printf("\nTotal tests ran: %d\n", test::__tests.size());
    std::printf("Tests passed: %d\n", testsPassed);
    std::printf("Tests failed: %d\n", testsFailed);
}

#define RUN_TESTS(file) { run_tests(__FILE_NAME__); };

#endif
