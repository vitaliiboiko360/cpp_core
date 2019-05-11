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
}