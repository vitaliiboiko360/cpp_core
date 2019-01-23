#include <stdio.h>

void func1(int arr[]);
void change_ptr(int * ptr_int);
void change_ptr2(int ** ptr_int);
int * find_largest(int * begin, int * end);

int main()
{
    int numbers[3] = { 101, 202, 303 };
    // printf("sizeof(array) %ld\n", sizeof(numbers));
    // printf("sizeof(&array) %ld\n", sizeof(&numbers));

    // int array1[10];
    // int * p_1 = array1;
    // func1(array1);
    // func1(&array1);

    // printf("pointer before function call %p\n", p_1);
    // change_ptr(p_1);
    // printf("pointer after function call %p\n", p_1);

    // printf("ptr before change %p\n", p_1);
    // change_ptr2(&p_1);
    // printf("ptr after change %p\n", p_1);

    printf("find largest element in array\n");
    int * p_to_largest = find_largest(numbers, numbers+(sizeof(numbers)/sizeof(numbers[0])));
    if(p_to_largest)
        printf("largest element is %d\n", *p_to_largest);
    p_to_largest = find_largest(numbers, numbers);
    if(p_to_largest)
        printf("largest element is %d\n", *p_to_largest);

    return 0;
}

void func1(int arr[])
{
    printf("sizeof array argument %ld\n", sizeof(arr));
}

void change_ptr(int * ptr_int)
{
    ptr_int = NULL;
}

void change_ptr2(int ** ptr_int)
{
    *ptr_int = NULL;
}

int * find_largest(int * begin, int * end)
{
    printf("start=%p\nend=%p\nend-start=%d\n", begin, end, (int)(end-begin));
    int * p_to_largest = NULL;
    if(begin == end ) return p_to_largest;
   
    for(;begin < end; begin++)
    {
        if(p_to_largest)
        {
            if (*p_to_largest < *begin)
                p_to_largest = begin;
        }
        else
        {
            p_to_largest = begin;
        }
    }
    return p_to_largest;
}