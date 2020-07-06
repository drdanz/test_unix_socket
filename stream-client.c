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
    } else {
        log("socket ok");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SRV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (connect(srv_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) < 0) {
        err_sys("connect error");
    } else {
        log("connect ok");
    }

    while ((bytes = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(srv_fd, buf, bytes) != bytes) {
            err_sys("write error");
        } else {
            log("write ok");
        }

        if ((read(srv_fd, buf, BUFFSIZE)) > 0) {
            log("read ok")
            if (write(STDOUT_FILENO, buf, bytes) != bytes) {
                err_sys ("write (STDOUT) error");
            } else {
                log("write ok");
            }
        } else {
            log("read error");
        }
    }

    if (bytes < 0) {
        err_sys("read (STDIN) error");
    } else {
        log("read (STDIN) ok");
    }

    exit(EXIT_SUCCESS);
}
