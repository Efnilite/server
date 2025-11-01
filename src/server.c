#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(void) {
    fprintf(stderr, "Server init\n");

    const int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("Failed to open socket");
        exit(EXIT_FAILURE);
    }

    const struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 80;
    addr.sin_addr = 0;

    const int bound = bind(fd, &addr, sizeof(addr));
    if (!bound) {

    }

    return 0;
}