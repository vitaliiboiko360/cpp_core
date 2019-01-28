#include <unistd.h>
#include <ncurses.h>

#define COUNT_CLOSE_SEC 20
#define DEF_COUNT_CLOSE_SEC 15

void count_and_close(int n_count);

int main()
{
    initscr();
    char text[] = "some line to be printed!";
    char * t = text;
    while(*t)
    {
        addch(*t);
        t++;
        refresh();
        napms(100);
    }
   
    count_and_close(DEF_COUNT_CLOSE_SEC);
    endwin();
    return 0;
}

void count_and_close(int n_count)
{
    if(n_count > COUNT_CLOSE_SEC)
        n_count = COUNT_CLOSE_SEC;
    if(n_count < 1)
        n_count = COUNT_CLOSE_SEC;

    int x_pos = 0;
    int y_pos = 0;

    getsyx(y_pos, x_pos);

    move(y_pos+1, 0);
    addstr("The application closes after... ");
    refresh();
    getsyx(y_pos, x_pos);
    while(n_count > 0)
    {
        move(y_pos, x_pos);
        clrtoeol();
        mvprintw(y_pos, x_pos, "%d sec", n_count-=2);
        refresh();
        napms(1000);
    }
}