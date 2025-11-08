#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>
#include <bits/signum-generic.h>

#include "shared.h"

int fd;

void handle_term(const int _) {
    (void)fprintf(stderr, "Stopping\n");

    if (close(fd) != 0) {
        ERROR("Failed to close socket");
    }

    exit(EXIT_SUCCESS);
}

int main(void) {
    fprintf(stderr, "Client init\n");

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        ERROR("Failed to open socket");
    }
    signal(SIGTERM, handle_term);

    const struct sockaddr_in addr_in = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr = {.s_addr = htonl(INADDR_LOOPBACK)}
    };

    if (connect(fd, (const struct sockaddr*)&addr_in, sizeof(addr_in)) != 0) {
        ERROR("Failed to connect to peer socket");
    }

    const char* hey = "hey";

    write(fd, hey, strlen(hey));

    (void)fprintf(stderr, "Sent hey\n");

    char buff[4096];
    for (int i = 0; i < LEN(buff); ++i) {
        buff[i] = '\0';
    }

    const ssize_t confirm = read(fd, buff, sizeof(buff)-1);
    if (confirm < 0) {
        ERROR("Failed to get confirmation message")
    }

    (void)fprintf(stderr, "Read %s\n", buff);

    while (true) {

    }

    handle_term(0);
    return 0;
}
