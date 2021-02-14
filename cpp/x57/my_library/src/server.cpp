#include "../server.h"
#include "../util.h"

#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>

namespace {
    const int buffer_size_256 = 256;

    void identify_client_info(struct sockaddr_in* client_addr_info)
    {
        char client_addr_str[INET_ADDRSTRLEN];
        if(NULL == inet_ntop(AF_INET, &(client_addr_info->sin_addr), client_addr_str, INET_ADDRSTRLEN))
        {
            std::cout<<"can't convert client address to string\n";
        }
        else
        {
            /* code */
        }
        
    }
}

my_server::my_server(const char* address, uint16_t port)
{
    m_socket_length = sizeof(struct sockaddr_in);
    m_socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if_error_exit(m_socket_descriptor == -1, "srv socket");

    memset(&m_server_addr_info, 0, sizeof(struct sockaddr_in));
    m_server_addr_info.sin_family = AF_INET;
    m_server_addr_info.sin_addr.s_addr = htonl(INADDR_ANY);
    m_server_addr_info.sin_port = htons(port);

    if_error_exit(
        -1 == bind(m_socket_descriptor, (struct sockaddr *)&m_server_addr_info, m_socket_length),
        "bind");
}

my_server::~my_server()
{
    close(m_socket_descriptor);
}

void my_server::run()
{
    
    const char* message = "PONG";
    int num_bytes = 0;
    char buffer[buffer_size_256];
    while(!m_stopped)
    {
        num_bytes = recvfrom(m_socket_descriptor, buffer, 0, buffer_size_256, (struct sockaddr*)&m_client_addr_info, &m_socket_length);
        if_error_exit(num_bytes == -1, "srv recvfrom");

        buffer[num_bytes] = 0;

        std::stringstream out_message;
        out_message <<"server received: "<<buffer<<"\n";
        std::cout << out_message.str();

        int num_bytes_sent = sendto(m_socket_descriptor, message, sizeof(message), 0, (struct sockaddr *)&m_client_addr_info, m_socket_length);
        
        out_message.str("");
        out_message.clear();
        out_message << "bytes to send: "<<sizeof(message)<<"\t";
        out_message << "bytes sent: "<<num_bytes_sent<<"\n";
        std::cout<<out_message.str();
    }
}