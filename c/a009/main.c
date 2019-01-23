#include <stdlib.h>
#include <curses.h>

static void finish(int sig);


int main(int argc, char* argv[])
{
    initscr();
    cbreak();

    printw("i use my curses\n");
    refresh();

    printw("\nthe screen has:\n");
    printw("LINES: %d\nCOLUMNS: %d\n", LINES, COLS);
    refresh();

    finish(0);
}


static void finish(int sig)
{
    endwin();
    exit(0);
}