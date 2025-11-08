#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>

#include "shared.h"

#define PORT 8080
#define MAX_BACKLOG 10
#define MAX_TCP_BYTES_SIZE 4096

int fd;

struct p_argument_t arguments[] = {
    {'p', 1}, // the port
};

void handle_term(const int _)  {
    fprintf(stderr, "Stopping\n");

    if (close(fd) != 0) {
        ERROR("Failed to close socket");
    }

    exit(EXIT_SUCCESS);
}

int main(void) {
    fprintf(stderr, "Server init\n");

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        ERROR("Failed to open socket");
    }
    signal(SIGTERM, handle_term);

    const struct sockaddr_in addr_in = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr = {.s_addr = htonl(INADDR_ANY)}
    };

    if (bind(fd, (const struct sockaddr*)&addr_in, sizeof(addr_in)) != 0) {
        ERROR("Failed to bind socket");
    }

    if (listen(fd, MAX_BACKLOG) != 0) {
        ERROR("Failed to set listening mode");
    }

    (void)fprintf(stderr, "Waiting to connect to peer...\n");

    struct sockaddr other_addr;
    socklen_t other_len;
    const int other_fd = accept(fd, &other_addr, &other_len);
    if (other_fd == -1) {
        ERROR("Failed to accept peer connection");
    }

    while (true) {
        // const int result = poll(poll_fd, LEN(poll_fd), -1);
        // if (result <= 0) {
        //     ERROR("An error occurred while trying to poll file descriptor");
        // }

        char buff[MAX_TCP_BYTES_SIZE];
        const ssize_t count = read(other_fd, &buff, MAX_TCP_BYTES_SIZE-1);
        (void)fprintf(stderr, "Read %s\n", buff);
        if (count <= 0) {
            ERROR("WTF"); // empty message
        }

        (void)fprintf(stderr, "2 Read %s\n", buff);

        const char* b = "OK";

        if (write(other_fd, b, strlen(b)) <= 0) {
            ERROR("Failed to write");
        }
    }

    handle_term(0);
    return 0;
}
