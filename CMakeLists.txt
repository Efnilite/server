cmake_minimum_required(VERSION 4.0)
project(web_server C)

set(CMAKE_C_STANDARD 11)

add_executable(server src/server.c
        src/util.c
        src/util.h
        src/http.c
        src/http.h)

add_executable(client src/client.c
        src/util.c
        src/util.h
        src/http.c
        src/http.h)
