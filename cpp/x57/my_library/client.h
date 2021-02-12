#include <stdint.h>
#include <netinet/in.h>
class my_client
{
    int m_socket_descriptor{-1};
    struct sockaddr_in m_server_addr_info;
    bool m_stopped{false};
public:
    my_client(int16_t port);
    ~my_client();
    void run();
};