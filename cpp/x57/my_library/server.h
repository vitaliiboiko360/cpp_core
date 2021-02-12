#include <netinet/in.h>
class my_server
{
    int m_socket_descriptor;
    struct sockaddr_in m_server_addr_info;
    struct sockaddr_in m_client_addr_info;
    bool m_stopped{false};
public:
    my_server(const char* address, uint16_t port);
    ~my_server();
    void run();
};
