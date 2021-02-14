#include "../server.h"
#include "../util.h"

#include <vector>
#include <cmath>
#include <chrono>
#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>

namespace {
    const int buffer_size_256 = 256;

    std::string get_str_client_info(struct sockaddr_in* client_addr_info)
    {
        char client_addr_str[INET_ADDRSTRLEN];
        std::string ret;
        if(NULL == inet_ntop(AF_INET, &(client_addr_info->sin_addr), client_addr_str, INET_ADDRSTRLEN))
        {
            std::cout<<"can't convert address to string\n";
            return ret;
        }
        
        ret = {client_addr_str};
        ret += ":";
        int port = ntohs(client_addr_info->sin_port);
        ret += std::to_string(port);
    
        return ret;
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
    std::ofstream file("file");
    const char* message = "PONG";
    int num_bytes = 0;
    char buffer[buffer_size_256];
    while(!m_stopped)
    {
        {
        auto t1 = std::chrono::high_resolution_clock::now();
        num_bytes = recvfrom(m_socket_descriptor, buffer, buffer_size_256, 0, (struct sockaddr*)&m_client_addr_info, &m_socket_length);
        if_error_exit(num_bytes == -1, "srv recvfrom");
        
        file << std::string{buffer} << "\n";
        auto t2 = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout 
         << "recvfrom blocked for " /* << std::fixed << std::setprecision(2) */
         << elapsed_time.count() /* / 1000. */ 
         << "\n";
        }
        
        buffer[num_bytes] = 0;

        std::stringstream out_message;
        out_message <<"server : "<<buffer<<"\t";
        out_message <<"from client "<<get_str_client_info(&m_client_addr_info)<<"\n";
        std::cout << out_message.str();

        {
        auto t1 = std::chrono::high_resolution_clock::now();
        int num_bytes_sent = sendto(m_socket_descriptor, message, sizeof(message), 0, (struct sockaddr *)&m_client_addr_info, m_socket_length);
        if_error_exit(num_bytes_sent != sizeof(message), "srv sendto");
        auto t2 = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout 
         << "sendto blocked for " /* << std::fixed << std::setprecision(2) */
         << elapsed_time.count() /* / 1000. */ 
         << "\n";
        }

        // out_message.str("");
        // out_message.clear();
        // out_message << "bytes to send: "<<sizeof(message)<<"\t";
        // out_message << "bytes sent: "<<num_bytes_sent<<"\n";
        // std::cout<<out_message.str();

    }
}