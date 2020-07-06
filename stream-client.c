#include "stream-proto.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
    struct sockaddr_un addr;
    int srv_fd;
    ssize_t bytes;
    char buf [BUFFSIZE];

    if ((srv_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        err_sys("socket error");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SRV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (connect(srv_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) < 0) {
        err_sys("connect error");
    }

    while ((bytes = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(srv_fd, buf, bytes) != bytes) {
            err_sys("write error");
        }
    }

    if (bytes < 0) {
        err_sys("read error");
    }

    exit(EXIT_SUCCESS);
}
