#include "http.h"

#include <string.h>

enum HttpRequestMethodType http_parse_method_type(const char* str) {
    if (strcmp(str, "GET") == 0) {
        return REQUEST_METHOD_GET;
    }
    if (strcmp(str, "HEAD") == 0) {
        return REQUEST_METHOD_HEAD;
    }

    // unsupported method
    return REQUEST_METHOD_LENGTH;
}

char* http_method_type_to_string(const enum HttpRequestMethodType method) {
    switch (method) {
    case REQUEST_METHOD_GET: return "GET";
    case REQUEST_METHOD_HEAD: return "HEAD";
    default: return NULL;
    }
}
