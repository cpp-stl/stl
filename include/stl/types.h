#ifndef TYPES_H
#define TYPES_H

namespace stl {
// 64 bit size_t
#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__LP64__) || \
    defined(_WIN64)
using size_t = unsigned long long;
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
// 32 bit size_t
using size_t = unsigned int;
#else
// default size is
// 32 bit
// architecture
// size.
using size_t = unsigned int;
#endif
};  // namespace stl
#endif
