/**
 * console.h - A Single-Header Library for Console Logging
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdlib.h>

#define warning(...)  do \
{ \
    fprintf(stderr, "warning: "); \
    fprintf(stderr, __VA_ARGS__); \
    fputc('\n', stderr); \
} while (0)

#define error(...)  do \
{ \
    fprintf(stderr, "error: "); \
    fprintf(stderr, __VA_ARGS__); \
    fputc('\n', stderr); \
} while (0)

#define fatal_error(...)  do \
{ \
    fprintf(stderr, "fatal error: "); \
    fprintf(stderr, __VA_ARGS__); \
    fputc('\n', stderr); \
    exit(EXIT_FAILURE); \
} while (0)

#endif /* ndef CONSOLE_H */
