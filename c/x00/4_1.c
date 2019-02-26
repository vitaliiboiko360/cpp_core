#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

<<<<<<< HEAD:c/x00/4.c
#define SNAKE_SIZE 6
=======
const int SNAKE_SIZE = 16;
>>>>>>> 32b9a5c74636d24cc379addbf00bf834e9e613b6:c/x00/main.c
const int FOUR = 4; // four valid_directions to move snake's head
const char CH = 'x';

void print_snake();

int main(int argc, char** argv)
{
    initscr();

    print_snake();
    
    endwin();
    return 0;
}

typedef struct
{
    int x;
    int y;
} point;

typedef struct 
{
    point snake_points[SNAKE_SIZE];
} snake;

void move_snake(snake * p_snake);
point next_move_head(snake * p_snake);
bool is_valid_move(int x, int y, snake * p_snake);
void init_snake(snake * p_snake);

void print_snake()
{
    snake snake_1;
    printw("before snake init\n");
    refresh();
    usleep(500000);
    init_snake(&snake_1);
    printw("after snake init\nbefore loop\n");
    refresh();
    usleep(500000);
    int i=0,j=0;
    while(true)
    {
        move_snake(&snake_1);
        if((++i % 100) == 0)
        {
            mvprintw(1,1,"#%d",j++);
            refresh();
        }
        napms(500);
    }
}

void init_snake(snake * p_snake)
{
    int cols, lines;
    getmaxyx(stdscr, lines, cols);

    int x = cols / 2;
    int y = lines / 2;

    point snake_start_point = {x, y};

    for(int i=0; i<SNAKE_SIZE; ++i)
        p_snake->snake_points[i] = snake_start_point;

    p_snake->snake_points[0] = snake_start_point;

    point * last_assigned_point = &snake_start_point;
    for(int i=1; i<SNAKE_SIZE; ++i)
    {
        p_snake->snake_points[SNAKE_SIZE-1] = *last_assigned_point;
        p_snake->snake_points[i] = next_move_head(p_snake);
        last_assigned_point = &(p_snake->snake_points[i]);
    }
}

void move_snake(snake * p_snake)
{
<<<<<<< HEAD:c/x00/4.c
    point snake_tail = p_snake->snake_points[0];
=======
    mvaddch(p_snake->snake_points[0].y, p_snake->snake_points[0].x, ' ');
>>>>>>> 32b9a5c74636d24cc379addbf00bf834e9e613b6:c/x00/main.c

    /* 
    memmove(p_snake->snake_points,
            p_snake->snake_points+1, 
            (SNAKE_SIZE-1)*sizeof(point));
    */

    for(int i=0; i<(SNAKE_SIZE-1); i++)
    {
        p_snake->snake_points[i] = p_snake->snake_points[i+1];
    }

    mvdelch(snake_tail.y, snake_tail.x);
    refresh();

    p_snake->snake_points[SNAKE_SIZE-1] = next_move_head(p_snake);

    mvaddch(p_snake->snake_points[SNAKE_SIZE-1].y,
            p_snake->snake_points[SNAKE_SIZE-1].x, CH);
    refresh();
    napms(30);
}


point next_move_head(snake * p_snake)
{
    point head = p_snake->snake_points[SNAKE_SIZE-1];
    point valid_directions[FOUR];
    
    int n_directions = 0;
    
    if(is_valid_move(head.x+1, head.y, p_snake))
    {
        valid_directions[n_directions].x = head.x+1;
        valid_directions[n_directions].y = head.y;
        n_directions++;
    }
    if(is_valid_move(head.x-1, head.y, p_snake))
    {
        valid_directions[n_directions].x = head.x-1;
        valid_directions[n_directions].y = head.y;
        n_directions++;
    }
    if(is_valid_move(head.x, head.y+1, p_snake))
    {
        valid_directions[n_directions].x = head.x;
        valid_directions[n_directions].y = head.y+1;
        n_directions++;
    }
    if(is_valid_move(head.x, head.y-1, p_snake))
    {
        valid_directions[n_directions].x = head.x;
        valid_directions[n_directions].y = head.y-1;
        n_directions++;
    }

    if(n_directions == 0)
        return head;
    
    int direction_random = rand() % n_directions;
        return valid_directions[direction_random];
}

bool is_valid_move(int x, int y, snake * p_snake)
{
    int cols, lines;
    getmaxyx(stdscr, lines, cols);

    if(( (x >= cols) || (x < 0) )  || ( (y >= lines) || (y < 0) ) )
        return false;

    point * pts = p_snake->snake_points;
    for(int i=0; i<SNAKE_SIZE; ++i)
    {
        if(pts[i].x == x && pts[i].y == y)
        {
            return false;
        }
    }

    return true;
}