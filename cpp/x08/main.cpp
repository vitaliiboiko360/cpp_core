<<<<<<< HEAD
#include <curses.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    initscr();

    
    box(stdscr, '*','*');
    printw("hello");
    refresh();
    sleep(2);

    endwin();

    return 0;
=======
#include <EventLoop.h>

int main(int argc, char** argv)
{
    EventLoop eventLoop;
    
    eventLoop.init();
    eventLoop.run();
    
    return 0;
>>>>>>> 01c6fcb93247f160fb90f4ebba6ad62ac32886f6
}