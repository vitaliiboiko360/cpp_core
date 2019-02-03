#include <string.h>
#include <
#include <curses.h>

static const int SNAKE_SIZE = 6;
static const int FOUR = 4; // four directions to move snake's head
static const char CH = 'x';

void print_snake();

int main(int argc, char* argv)
{
    initscr();

    print_snake();
    
    endwin();
    return 0;
}

typdef struct
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
bool is_valid_move(int x, int y);

void print_snake()
{
    snake snake_1;
    while(true)
    {
        move_snake(&snake_1);
    }
}

void move_snake(snake * p_snake)
{
    mvdelch(p_snake->snake_points[0].y, p_snake->snake_points[0].x);

    memmove(p_snake->snake_points,
            p_snake->snake_points+1, 
            (SNAKE_SIZE-1)*sizeof(point));

    p_snake->snake_points[SNAKE_SIZE-1] = next_move_head(p_snake);

    mvaddch(p_snake->snake_points[SNAKE_SIZE-1].y,
            p_snake->snake_points[SNAKE_SIZE-1].x, CH);
    
    napms(100);
}

point next_move_head(snake * p_snake)
{
    point head = p_snake->snake_points[SNAKE_SIZE-1];

    for(int i=0; i<n_directions; ++i)
    {
    }
}

bool is_valid_move(int x, int y, snake * p_snake)
{
    int cols, lines;
    getmaxyx(stdscr, &lines, &cols);

    if((x >= lines || x < 0)) || (y >= cols || y < 0))
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