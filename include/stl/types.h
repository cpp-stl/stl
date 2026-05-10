#ifndef TYPES_H
#define TYPES_H

#include "common.h"
namespace stl {
// 64 bit size_t
#ifdef _64BIT
using size_t = unsigned long long;
#elif _32BIT
// 32 bit size_t
using size_t = unsigned int;
#else
// default size is
// 32 bit
// architecture
// size.
using size_t = unsigned int;
#endif

using ptrdiff_t = decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));
};  // namespace stl
#endif
