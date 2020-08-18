
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"
#include "error_hndl_funcs.h"

int u_client::run()
{
    struct sockaddr_un addr;

    int sfd = 0;
    ssize_t bytes_read;
    const int BUF_SZ = 256;
    const char* socket_path = "/tmp/socket_a";

    char buffer[BUF_SZ];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        error_exit("socket");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

    if(connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
        error_exit("connect");
    
    while((bytes_read = read(STDIN_FILENO, buffer, BUF_SZ)) > 0)
        if (write(sfd, buffer, bytes_read) != bytes_read)
            error_exit("partial/failed write");

    if (bytes_read == -1)
        error_exit("read");
    
    return 0;
}