#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN(a) sizeof(a)/sizeof(a[0])

#define ERROR(message) \
    (void)perror(message); \
    (void)exit(EXIT_FAILURE);

#define ERROR_NO(no, message) \
    errno = no; \
    (void)perror(message); \
    (void)exit(EXIT_FAILURE);

/**
 * Represents an argument that can be passed to the program argument.
 */
struct p_argument_t {
    /**
     * The char used to identify an argument.
     */
    char name;

    /**
     * The amount of text with spaces after the argument to consider part of the argument.
     */
    uint8_t len;

    /**
     * Parses the provided string as the argument.
     */
    void (*parser)(const char*);
};

/**
 * Parses program arguments.
 * @param p_args The argument parse types.
 * @param p_args_len The size of p_args.
 * @param count The amount of arguments.
 * @param args The arguments passed.
 */
void parse_program_arguments(
    const struct p_argument_t* p_args, size_t p_args_len,
    int count, char* args[]
);

/**
 * Parses an int from a string.
 * @param str The integer string to parse.
 * @return The parsed integer, exits if parsing fails.
 */
long int parse_int(const char* str);

#endif //UTIL_H
