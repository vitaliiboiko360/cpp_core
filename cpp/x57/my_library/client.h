#include <stdint.h>

class my_client
{
public:
    my_client(char* host, int16_t port);
    void run();
};