#include <netinet/in.h>

class my_server
{
    int _socket_file_descriptor;
    struct sockadd_in _server_addrinfo;
public:
    my_server(uint16_t port);
    ~my_server();

    void run();
};