#include "my_library/client.h"
#include "my_library/server.h"

const uint16_t port = 30000;

int main()
{
    my_server srv(port);
    my_client cli;
}