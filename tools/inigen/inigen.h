#ifndef GUARD_INIGEN_H
#define GUARD_INIGEN_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER

#define FATAL_ERROR(format, ...)          \
do {                                      \
    fprintf(stderr, format, __VA_ARGS__); \
    exit(1);                              \
} while (0)

#define UNUSED

#else

#define FATAL_ERROR(format, ...)            \
do {                                        \
    fprintf(stderr, format, ##__VA_ARGS__); \
    exit(1);                                \
} while (0)

#define UNUSED __attribute__((__unused__))

#endif // _MSC_VER

#endif //GUARD_INIGEN_H
