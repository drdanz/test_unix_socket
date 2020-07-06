#include "stream-proto.h"

int main (int argc, char** argv)
{
    struct sockaddr_un addr;
    int srv_fd;
    int cli_fd;
    ssize_t bytes;
    char buf[BUFFSIZE];
    if ((srv_fd = socket(AF_UNIX, SOCK_STREAM, 0 )) < 0) {
        err_sys("socket error");
    }
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy (addr.sun_path, SRV_SOCK_PATH, sizeof(addr.sun_path ) - 1) ;
    if (access(addr.sun_path, F_OK) == 0) {
        unlink(addr.sun_path);
    }
    if (bind(srv_fd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un)) < 0) {
        err_sys("bind error") ;
    }
    if (listen(srv_fd ,SRV_BACKLOG) < 0) {
        err_sys("listen error");
    }

    for( ; ; ) {
        if ((cli_fd = accept(srv_fd, NULL, NULL)) < 0) {
            err_sys ("accept error");
        }
        while ((bytes = read(cli_fd, buf, BUFFSIZE)) > 0) {
            if (write(STDOUT_FILENO, buf, bytes) != bytes ) {
                err_sys ("write error");
            }
        }
        if (bytes < 0) {
            err_sys("read error");
        }
        if (close(cli_fd) < 0) {
            err_sys ( "close error ");
        }
    }
}
