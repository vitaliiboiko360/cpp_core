#include <ncurses.h>
#include <stdlib.h> 
#include <stdio.h>

const char* lines_height = "5";

int main()
{
    const char* lines_var_name = "LINES";
    char t1[] = "Shall I compare thee";
    char t2[] = " to a summer's day?";
    
    char* prev_lines = getenv(lines_var_name);
    setenv(lines_var_name, lines_height, 1);

    initscr();
    //setenv(lines_var_name, prev_lines, 1);

    addstr(t1);     /* add the first string */
    addstr(t2);     /* add the second string */
    refresh();      /* display the result */
    getch();        /* wait */
    
    endwin();       
    return(0);
}