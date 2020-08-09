
#include <sys/un.h>
#include <sys/socket.h>

#include "error_hndl_funcs.h"

int main(int argc, char* argv[])
{

    const char *SOCKNAME = "/tmp/socket_a";

    int sfd;

    struct sockaddr_un addr;

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1)
        error_exit("socket");

    return 0;
}