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

struct http_request_url_t {
    enum HttpRequestMethodType method;
    char* url;
    char* version;
};

enum HttpEncoding {
    ENCODING_GZIP,
    ENCODING_LENGTH,
};

/**
 * A request sent by the client.
 */
struct http_request_t {
    // headers
    struct http_request_url_t method;
    char* host;
    char* agent;
    char* language;
    enum HttpEncoding encoding[ENCODING_LENGTH];
    char* connection;
};

struct http_request_t* parse_request(int fd);

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

const char* response_to_string(const struct http_response_t* response);

#endif //CS_HTTP_H
