#include <EventLoop.h>

int main(int argc, char** argv)
{
    EventLoop eventLoop;
    
    eventLoop.init();
    eventLoop.run();
    
    return 0;
}