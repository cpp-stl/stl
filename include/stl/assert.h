#ifndef ASSERT_H
#define ASSERT_H

#include "stl/common.h"
#include "stl/exceptions.h"
#include <cstdio>
#include <map>

const std::map<const char *, int> tests;

namespace stl {
class assertion_exception : public exception {
    const char *what() const noexcept { return "assertion exception"; }
};
inline void assert(bool condition, const char *message = "", int line = __LINE__,
                   const char *file = __FILE__) {
    char *fileName;
    getFileName(file, fileName);

    if (condition) {
        std::printf("[assertion] %s: %s:%d\n", "passed", fileName, line);
    } else {
        std::printf("\033[3;41;30m[assertion] %s: %s:%d\033[0m\n", message, fileName, line);
    }
    delete[] fileName;
}
}; // namespace stl

#define ASSERT_EQUAL(a, b) stl::assert(a == b, "expected equal, got not equal", __LINE__, __FILE__);
#define ASSERT_NOT_EQUAL(a, b)                                                                     \
    stl::assert(a != b, "expected not equal, got equal", __LINE__, __FILE__);
#define ASSERT_NULL(a)                                                                             \
    stl::assert(a == nullptr, "expected nullptr, got defined", __LINE__, __FILE__);
#define ASSERT_THROWS(function)                                                                    \
    try {                                                                                          \
        function();                                                                                \
        stl::assert(false, "expected to throw", __LINE__, __FILE__);                               \
    } catch (stl::exception & e) {                                                                 \
        stl::assert(true, nullptr, __LINE__, __FILE__);                                            \
    }
#define ASSERT_NOT_THROWS(function)                                                                \
    try {                                                                                          \
        function();                                                                                \
        stl::assert(true, nullptr, __LINE__, __FILE__);                                            \
    } catch (stl::exception & e) {                                                                 \
        stl::assert(false, "expected to not throw", __LINE__, __FILE__);                           \
    }

#endif
