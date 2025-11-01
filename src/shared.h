#ifndef SHARED_H
#define SHARED_H

#include <stdint.h>

#define LEN(a) sizeof(a)/sizeof(a[0])

#define ERROR(message) \
    perror(message); \
    exit(EXIT_FAILURE);

struct p_argument_t {
    /**
     * The char used to identify an argument.
     */
    char name;

    /**
     * The amount of text with spaces after the argument to consider part of the argument.
     */
    uint8_t len;
};

void parse_program_arguments(int count, char* args[]);

#endif //SHARED_H
