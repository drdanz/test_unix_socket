#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
// #include "helpers.h"

#define SRV_SOCK_PATH "/tmp/ux_socket"

#define BUFFSIZE 1024

#define SRV_BACKLOG 100

#include <stdio.h>
#define err_sys(x) fprintf(stderr, x "\n")
