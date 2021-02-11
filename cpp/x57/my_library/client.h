#include <stdint.h>

class my_client
{
    uint16_t m_port{0};
public:
    my_client(char* host, int16_t port);
    void run();
};