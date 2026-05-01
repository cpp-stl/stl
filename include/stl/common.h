#ifndef COMMON_H
#define COMMON_H

#include "stl/types.h"
#include "string.h"

inline void getFileName(const char *file_path, char *&buffer) {
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

    buffer = new char[len - pos + 1];
    stl::size_t incr = 0;
    while (file_path[pos + incr] != '\0') {
        buffer[incr] = file_path[pos + incr];
        incr++;
    }
    buffer[incr] = '\0';
}

#endif
