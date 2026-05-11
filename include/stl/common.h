#ifndef COMMON_H
#define COMMON_H

template <typename T, typename ...PARAMS>
using _FUNCTION_POINTER = T(*)(PARAMS...);

#if defined(_WIN64) || defined(_M_X64)
#define WINDOWS 
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__LP64__) || \
    defined(_WIN64)
#define _64BIT

#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#define _32BIT

#endif

// GCC, Clang, etc.
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LITTLE_ENDIAN true
#define BIG_ENDIAN false
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define LITTLE_ENDIAN false
#define BIG_ENDIAN true
#else
#error "Mixed-endian architecture not supported"
#endif

// Windows (MSVC) is always little-endian
#elif defined(_MSC_VER)
#define LITTLE_ENDIAN true
#define BIG_ENDIAN false

#elif defined(__APPLE__)
#include <machine/endian.h>
#if BYTE_ORDER == LITTLE_ENDIAN
#define LITTLE_ENDIAN true
#define BIG_ENDIAN false
#else
#define LITTLE_ENDIAN false
#define BIG_ENDIAN true
#endif

#else
#error "Cannot determine endianness on this platform"
#endif

#define POINTERDIFF(R, L) stl::ptrdiff_t diff() {return (static_cast<int*>(R) - static_cast<int*>(L));}
// RIP to getFileName(), my favorite method I did first try - Joseph Alemu

#endif
