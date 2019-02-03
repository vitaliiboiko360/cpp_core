#include <string.h>
#include <stdlib.h>
#include <curses.h>

#define SNAKE_SIZE 6
static const int FOUR = 4; // four valid_directions to move snake's head
static const char CH = 'x';

void print_snake();

int main(int argc, char* argv)
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
    init_snake(&snake_1);
    while(true)
    {
        move_snake(&snake_1);
        napms(100);
    }
}

void init_snake(snake * p_snake)
{
    int cols, lines;
    getmaxyx(stdscr, cols, lines);

    int x = cols / 2;
    int y = lines / 2;

    point snake_start_point = {x, y};

    point point_to_add = { -1, -1};
    for(int i=0; i<SNAKE_SIZE; ++i)
        p_snake->snake_points[i] = point_to_add;

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
    point valid_directions[FOUR];
    
    int direction_index = 0;
    
    if(is_valid_move(head.x+1, head.y, p_snake))
    {
        valid_directions[direction_index].x = head.x+1;
        valid_directions[direction_index].y = head.y;
        direction_index++;
    }
    if(is_valid_move(head.x-1, head.y, p_snake))
    {
        valid_directions[direction_index].x = head.x-1;
        valid_directions[direction_index].y = head.y;
        direction_index++;
    }
    if(is_valid_move(head.x, head.y+1, p_snake))
    {
        valid_directions[direction_index].x = head.x;
        valid_directions[direction_index].y = head.y+1;
        direction_index++;
    }
    if(is_valid_move(head.x, head.y-1, p_snake))
    {
        valid_directions[direction_index].x = head.x;
        valid_directions[direction_index].y = head.y-1;
        direction_index++;
    }

    if(direction_index == 0)
        return head;
    
    int direction_random = rand() % direction_index;
        return valid_directions[direction_random];
}

bool is_valid_move(int x, int y, snake * p_snake)
{
    int cols, lines;
    getmaxyx(stdscr, lines, cols);

    if(( (x >= lines) || (x < 0) )  || ( (y >= cols) || (y < 0) ) )
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