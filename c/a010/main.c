#include <unistd.h>
#include <curses.h>

#define DELAY 3000

int main()
{
    initscr();
    noecho();
    curs_set(0);

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    int direction = 1;
    int next_x = 0;
    int x = 0, y = 0;
    while(1)
    {
        clear();
        mvprintw(y, x, "o");
        refresh();

        usleep(DELAY);
        next_x = x + direction;

        if(next_x >= max_x || next_x < 0)
        {
            direction *= -1;
        }
        else
        {
            x += direction;
        }
    }

    endwin();
}