#include <curses.h>

void print_border();
void count_down();

int main(int argc, char** argv)
{
    initscr();

    while(true)
    {
        count_down(0);
        print_border();
        
    }

    endwin();
    return 0;
}

void print_border()
{
    clear();
    wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
    refresh();
    return;
}

void count_down(int sec)
{
    sec = 300;
    int i = 0;

    while(i < sec)
    {
        mvprintw(1, 1, "%s", "     ");
        mvprintw(1, 1, "%d", sec-i);
        refresh();
        napms(1);
        i += 1;
    }
}