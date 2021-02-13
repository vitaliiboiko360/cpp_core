#include "../client.h"
#include "../util.h"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sstream>

namespace {
    const int buffer_size_256 = 256;
}

my_client::my_client(int16_t port)
{
    m_socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if_error_exit(m_socket_descriptor == -1, "socket");

    memset(&m_server_addr_info, 0, sizeof(struct sockaddr_in));
    m_server_addr_info.sin_family = AF_INET;
    m_server_addr_info.sin_port = htons(port);
}

my_client::~my_client()
{
    close(m_socket_descriptor);
}

void my_client::run()
{
    const char* message = "PING";
    int num_bytes = 0;
    char buffer[buffer_size_256];
    while(!m_stopped)
    {
        num_bytes = sendto(m_socket_descriptor, message, sizeof(message), 0, (struct sockaddr*)&m_server_addr_info, sizeof(struct sockaddr_in));
        if_error_exit(num_bytes == -1, "sendto");

        num_bytes = recvfrom(m_socket_descriptor, buffer, buffer_size_256, 0, NULL, NULL);
        if_error_exit(num_bytes == -1, "recvfrom");
        buffer[num_bytes] = 0;

        std::stringstream out_message;
        out_message <<"client received: "<<buffer<<"\n";
        std::cout << out_message.str();
    }
}