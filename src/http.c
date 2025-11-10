#include <stdio.h>
#include <string.h>

#include "http.h"
#include "util.h"

#define HTTP_MAX_HEADER_LEN 4096

/**
 * Parses the request url and method.
 * @param str The string to parse.
 * @return The url of the request and the method.
 */
struct http_request_url_t* http_parse_method(char* str) {
    struct http_request_url_t* request = malloc(sizeof(struct http_request_url_t));
    if (request == NULL) {
        perror("Failed to allocate request url");
        return NULL;
    }

    char* part = strtok(str, " ");
    if (strcmp(part, "GET") == 0) {
        request->method = REQUEST_METHOD_GET;
    } else if (strcmp(part, "HEAD") == 0) {
        request->method = REQUEST_METHOD_HEAD;
    } else {
        request->method = REQUEST_METHOD_LENGTH;
    }
    fprintf(stderr, "Read method as %s\n", part);

    part = strtok(NULL, " ");
    request->url = part;
    fprintf(stderr, "Read url as %s\n", part);

    part = strtok(NULL, " ");
    request->version = part;
    fprintf(stderr, "Read ver as %s\n", part);

    return request;
}

struct http_request_t* parse_request(const int fd) {
    FILE* fp = fdopen(fd, "r");

    if (fp == NULL) {
        perror("Failed to open file fp");
        return NULL;
    }

    struct http_request_t* request = malloc(sizeof(struct http_request_t));
    if (request == NULL) {
        fclose(fp);
        perror("Failed to allocate for request");
        return NULL;
    }

    char line[HTTP_MAX_HEADER_LEN];

    if (fgets(line, HTTP_MAX_HEADER_LEN, fp) == NULL) {
        perror("Empty request");
        goto error;
    }

    while (fgets(line, HTTP_MAX_HEADER_LEN, fp) != NULL) {
        const size_t len = strlen(line);

        if (len == HTTP_MAX_HEADER_LEN && line[len - 1] != '\n') {
            perror("Header longer than max length");
            goto error; // line is longer than max header length
        }

        if (strcmp(line, CRLF) == 0) {
            break; // eof
        }


    }

    if (ferror(fp)) {
        perror("File error occurred");
        goto error;
    }

    fclose(fp);
    return request;

error:
    fclose(fp);
    free(request);
    return NULL;
}

const char* response_to_string(const struct http_response_t* response) {}
