#include <stdio.h>
#include <stdlib.h>

#ifndef __cplusplus
typedef char bool;
#define true 1
#define false 0
#endif // __cplusplus

typedef struct 
{
    int red;
    int green;
    int blue;
    int black;
} color;

struct list_element
{
    struct list_element * next;
};
typedef struct list_element list_element;
typedef struct 
{
    list_element * first;
    list_element * last;
} list;

void list_init(list * container)
{
    container->first = NULL;
    container->last = NULL;
}

bool list_empty(list * container)
{
    return NULL == container->first;
}

list_element * list_begin(list * container)
{
    return container->first;
}

list_element * list_next(list_element * element)
{
    return element->next;
}

void list_push_back(list * container, list_element * element)
{
    if (list_empty(container))
    {
        container->last->next = element;
        container->last = element;
    }
    else
    {
        container->last = element;
        container->last->next = element;
    }

    element->next = NULL;
}

list_element * list_pop_front(list * container)
{
    list_element * element = container->first;
    container->first = container->first->next;
    return element;
}



typedef struct
{
    list_element header;
    int value;
} apple;

int main(int argc, char* argv[])
{

    list apples;
    apple * a = (apple *)malloc(sizoof(apples));
    apple * b = (apple *)malloc(sizoof(apples));
    apple * c = (apple *)malloc(sizoof(apples));

    list_init(&apples);
    if(list_empty(&apples))
    {
        list_push_back(&apples, a);
        list_push_back(&apples, b);
        list_push_back(&apples, c);
    }

    apple * it = list_begin(&apples);
    do
    {
        if(it != NULL)
            printf("it=%p\tvalue=%d\n", it, *it->value);
    } while(it->next != NULL);
    return 0;
}

