#ifndef ASSERT_H
#define ASSERT_H

#include <cstdio>
#include <map>
#include "stl/common.h"
#include "stl/exceptions.h"

const std::map<char*, int> tests;

namespace stl {
    class assertion_exception : public exception
    {
        const char* what() const noexcept {
            return "assertion exception";
        }
    };
    inline void assert(bool condition, const char *message, int line = __LINE__, const char* file = __FILE__)
    {
        if (condition)
        {
            std::printf("[assertion] %s: %s:%d\n", "passed", getFileName(file), line);
        }
        else
        {
            std::printf("\033[3;41;30m[assertion] %s: %s:%d\033[0m\n", message, getFileName(file), line);
        }
        
    }
};

#define ASSERT_EQUAL(a, b) stl::assert(a == b, "expected equal, got not equal", __LINE__, __FILE__);
#define ASSERT_NOT_EQUAL(a, b) stl::assert(a != b, "expected not equal, got equal", __LINE__, __FILE__);
#define ASSERT_NULL(a) stl::assert(a == nullptr, "expected nullptr, got defined", __LINE__, __FILE__);
#define ASSERT_THROWS(function) try { function() } catch () { stl::assert(false, "", __LINE__, __FILE__) }

#endif