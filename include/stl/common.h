#ifndef COMMON_H
#define COMMON_H

template <typename T, typename ...PARAMS>
using _FUNCTION_POINTER = T(*)(PARAMS...);

#define WINDOWS defined(_WIN64) || defined(_M_X64)
#define _64BIT defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__LP64__) || \
    defined(_WIN64)
#define _32BIT defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)

#define POINTERDIFF(R, L) stl::ptrdiff_t diff() {return (static_cast<int*>(R) - static_cast<int*>(L));}
// RIP to getFileName(), my favorite method I did first try - Joseph Alemu

#endif
