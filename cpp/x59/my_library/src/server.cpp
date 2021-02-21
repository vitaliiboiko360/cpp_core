#include "../server.h"
#include "../utils.h"

#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

my_server::my_server(uint16_t port)
{
    _socket_file_descriptor = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_error_exit(_socket_file_descriptor == -1, "socket");

    memset(&_server_addrinfo, 0, sizeof(struct sockaddr_in));

    _server_addrinfo.sin_family = AF_INET;
    _server_addrinfo.sin_addr.s_addr = htonl(INADDR_ANY);
    _server_addrinfo.sin_port = htons(port);
}

my_server::~my_server()
{
    close(_socket_file_descriptor);
}

void my_server::run()
{

}