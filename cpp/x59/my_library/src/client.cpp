#include "../client.h"
#include "../utils.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

my_client::my_client()
{
    _socket_file_descriptor = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_error_exit(_socket_file_descriptor == -1, "cli socket");
}

my_client::~my_client()
{
    close(_socket_file_descriptor);
}

void my_client::run()
{

}