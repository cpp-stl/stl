#ifndef COMMON_H
#define COMMON_H

#include "stl/types.h"
#include "string.h"

inline char *getFileName(const char *file_path) {
    stl::size_t len = stl::strlen(file_path);

#if defined(_WIN64) || defined(_M_X64)
    char slash = '\\';
#else
    char slash = '/';
#endif
    stl::size_t pos = len;
    char start = file_path[pos];
    while (start != slash) {
        pos--;
        start = file_path[pos];
    }
    pos = pos + 1;

    char *buffer = new char[len - pos];
    stl::size_t incr = 0;
    while (file_path[pos + incr] != '\0') {
        buffer[incr] = file_path[pos + incr];
        incr++;
    }
    buffer[incr] = file_path[pos + incr];
    return buffer;
}

#endif
