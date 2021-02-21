#include "../client.h"
#include "../utils.h"

#include <sys/socket.h>
#include <unistd.h>

my_client::my_client()
{
    _socket_file_descriptor = socket(AF_INET, SOCK_RAW, 0);
    if_error_exit(_socket_file_descriptor == -1, "socket");
}

my_client::~my_client()
{
    close(_socket_file_descriptor);
}

void my_client::run()
{

}