#include <limits.h>
#include <curses.h>

int main(int argc, char* argv[])
{
    initscr();
    printw("hi courses\n");
    printw("enter me sth:\n");
    refresh();

    char str[CHAR_MAX];
    getstr(str) ;
    str[CHAR_MAX-1] = '\0';

    printw("you entered:\n%s\n", str);
    printw("\nthe end\n");
    
    getch();

    endwin();  
    return 0;
}