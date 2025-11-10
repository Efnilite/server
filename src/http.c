#include <stdio.h>
#include <string.h>

#include "http.h"
#include "util.h"

#define HTTP_MAX_HEADER_LEN 4096

/**
 * Parses the request url and method.
 * @param str The string to parse.
 * @param request The request to populate.
 * @return The url of the request and the method.
 */
static int http_parse_method(const char* str, struct http_request_url_t* request) {
    char copy[HTTP_MAX_HEADER_LEN];
    if (strncpy(copy, str, strlen(str)) == NULL) {
        perror("Failed to copy string");
        return FAILURE;
    }

    char* part = strtok(copy, " ");
    if (strcmp(part, "GET") == 0) {
        request->method = REQUEST_METHOD_GET;
    } else if (strcmp(part, "HEAD") == 0) {
        request->method = REQUEST_METHOD_HEAD;
    } else {
        perror("Failed to recognize method");
        return FAILURE;
    }
    fprintf(stderr, "Read method as %s\n", part);

    part = strtok(NULL, " ");
    request->url = part;
    fprintf(stderr, "Read url as %s\n", part);

    part = strtok(NULL, " ");
    request->version = part;
    fprintf(stderr, "Read ver as %s\n", part);

    return SUCCESS;
}

int parse_request(const int fd, struct http_request_t* request) {
    if (request == NULL) {
        perror("Failed to allocate for request");
        return FAILURE;
    }

    FILE* fp = fdopen(fd, "r");
    if (fp == NULL) {
        perror("Failed to open file fp");
        return FAILURE;
    }

    char line[HTTP_MAX_HEADER_LEN];

    if (fgets(line, HTTP_MAX_HEADER_LEN, fp) == NULL) {
        perror("Empty request");
        goto error;
    }

    struct http_request_url_t url;
    if (http_parse_method(line, &url) == FAILURE) {
        perror("Failed to parse url");
        goto error;
    }
    request->url = url;

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
    return SUCCESS;

error:
    fclose(fp);
    return FAILURE;
}

const char* response_to_string(const struct http_response_t* response) {}
