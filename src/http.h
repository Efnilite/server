#ifndef CS_HTTP_H
#define CS_HTTP_H

#include <stdint.h>

#define HTTP_VERSION "HTTP/1.1"
#define CRLF "\r\n"

/**
 * The request method type.
 */
enum HttpRequestMethodType {
    REQUEST_METHOD_GET,
    REQUEST_METHOD_HEAD,
    REQUEST_METHOD_LENGTH,
};

/**
 * @param str The string to parse.
 * @return The method type.
 */
enum HttpRequestMethodType http_parse_method_type(const char* str);

/**
 * @param method The method to stringify.
 * @return The appropriate string.
 */
char* http_method_type_to_string(enum HttpRequestMethodType method);

enum HttpEncoding {
    ENCODING_GZIP,
    ENCODING_LENGTH,
};

/**
 * A request sent by the client.
 */
struct http_request_t {
    // headers
    enum HttpRequestMethodType method;
    char* host;
    char* agent;
    char* language;
    enum HttpEncoding encoding[ENCODING_LENGTH];
    char* connection;

    // content
    char* content;
};

/**
 * A response sent by the server.
 */
struct http_response_t {
    // headers
    uint16_t status;
    enum HttpEncoding encoding[ENCODING_LENGTH];

    // content
    char* content;
};

#endif //CS_HTTP_H
