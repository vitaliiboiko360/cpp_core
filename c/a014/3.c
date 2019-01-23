#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

typedef enum
{
    JOHN = 0,
    INNA,
    LEONID,
    VITALII,
    SERGII,
    DIMA,
    ROMAN,
    KONSTANTIN,
    TOTAL_PLAYERS
} winner_int;

void who_is_winner(int player_number);

int main()
{

    int array[CHAR_MAX];

    bool is_empty = array[0] != 0;

    if(is_empty)
    {
        printf("it's empty\n");
    }
    else
    {
        printf("it's non empty\n");
    }

    printf("end of stack memory use\n");

    int* p_array_1 = (int*)malloc(CHAR_MAX);
    if(p_array_1)
        printf("successfully allocated some dynamic memory\n");
    else
    {
        perror("malloc\n");
        exit(EXIT_FAILURE);
    }
    printf("size of dyn array in bytes %ld\n", sizeof(p_array_1));
    printf("sizeof(p_array_1)/sizeof(*p_array_1) = %ld\n", sizeof(p_array_1)/sizeof(*p_array_1));
    printf("CHAR_MAX/sizeof(*p_array_1) = %ld\n", CHAR_MAX/sizeof(*p_array_1));
    printf("CHAR_MAX=%d\n", CHAR_MAX);

    free(p_array_1);
    if(p_array_1 == NULL)
    {
        printf("memory freeed\n");
    }
    else
    {
        printf("don't know\n");
    }

    int start=0, end=10;
    while(start++<end)
    {   
        printf("iteration #%d\n", start);
        winner_int win = rand() % TOTAL_PLAYERS;
        who_is_winner(win);
        //printf("thanks for voting\n");
    }
}

void who_is_winner(int player_number)
{
    switch(player_number)
    {
        case JOHN:
            return;
        case INNA:
            printf("inna");
            break;
        case LEONID:
            printf("leonid");
            break;
        case VITALII:
            printf("vitalii");
            break;
        default:
            return;
    };
    printf(" is winner\n");
}