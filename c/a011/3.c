#include <stdio.h>
#include <stdlib.h>

int main()
{

    void * p = malloc(sizeof(int));
    printf("p=%p\n", p);

    free(p);
    p = NULL;
    printf("after free(p), p=%p\n", p);
    return 0;
}