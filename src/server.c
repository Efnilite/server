#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <signal.h>
#include <stdbool.h>
#include <bits/signum-generic.h>

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

int main(int argc, char* argv[]) {
    fprintf(stderr, "Server init\n");

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        ERROR("Failed to open socket");
    }
    signal(SIGTERM, handle_term);

    const struct sockaddr_in addr_in = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr = {.s_addr = htonl(INADDR_LOOPBACK)}
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
    if (accept(fd, &other_addr, &other_len) != 0) {
        ERROR("Failed to accept peer connection");
    }

    struct pollfd poll_fd[1] = {
        {
            .fd = fd,
            .events = POLLIN | POLLERR | POLLHUP | POLLNVAL,
            .revents = 0
        }
    };

    while (true) {
        const int result = poll(poll_fd, LEN(poll_fd), -1);
        if (result <= 0) {
            ERROR("An error occurred while trying to poll file descriptor");
        }

        for (int i = 0; i < LEN(poll_fd); ++i) {

        }

        char buff[MAX_TCP_BYTES_SIZE];
        const ssize_t count = read(fd, &buff, MAX_TCP_BYTES_SIZE);
        if (count <= 0) {
            continue; // empty message
        }
    }

    return 0;
}
