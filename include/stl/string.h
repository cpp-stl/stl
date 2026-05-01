#ifndef STRING_H
#define STRING_H
#include "types.h"

namespace stl {
inline stl::size_t strlen(const char *str) noexcept {
    stl::size_t count = 0;
    char i = str[count];
    while (i != '\0') {
        count++;
        i = str[count];
    }
    return count;
}
};  // namespace stl

#endif
