#include <unistd.h>
#include <ncurses.h>

#define MAX_COUNT_CLOSE_SEC 12
#define DEF_COUNT_CLOSE_SEC 12

void print_border();

int main()
{
    initscr();

    print_border();
   
    endwin();
    return 0;
}

void print_border()
{
    int x = 0;
    int x_max = getmaxx(stdscr);
    while(x < x_max)
    {
        addch('*');
        move(0, x++);
        refresh();
        napms(50);
    }
    x = x_max-1;

    int y = 0;
    int y_max = getmaxy(stdscr);
     while(y < y_max)
    {
        addch('*');
        move(y++, x);
        refresh();
        napms(50);
    }
}

void count_and_close(int n_count)
{
    if(n_count > MAX_COUNT_CLOSE_SEC)
        n_count = MAX_COUNT_CLOSE_SEC;
    if(n_count < 1)
        n_count = MAX_COUNT_CLOSE_SEC;

    int x_pos = 0;
    int y_pos = 0;

    getsyx(y_pos, x_pos);

    move(y_pos+1, 0);
    addstr("The application closes after... ");
    refresh();
    getsyx(y_pos, x_pos);
    while(n_count > 8)
    {
        move(y_pos, x_pos);
        clrtoeol();
        mvprintw(y_pos, x_pos, "%d sec", n_count-=1);
        refresh();
        napms(1000);
    }
}