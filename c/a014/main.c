#include <stdio.h>
#include <limits.h>
#include <math.h>

#define NSIZE 10

void func1(int* array, int size);

int main()
{
    /*
    printf("proof that arrays are pointers in disguise\n");
    printf("define array on stack\n");
    int array_1[NSIZE];
    printf("sizeof(*array) = %ld\n", sizeof(*array_1));
    int * p_int_1;
    printf("sizeof(ptr_to_int) = %ld\n", sizeof(p_int_1));

    for(int i=0; i<NSIZE; ++i)
    {
        array_1[i] = (i+1)*(i+1);
    }

    int * p_int_2 = array_1;
    int start=0, end=NSIZE;
    while(start++ < end)
    {
        printf("#iteration #%d\t", start);
        printf("pointer value: %p\tinteger value: %d\n", p_int_2, *p_int_2);
        p_int_2++;
    }
    */

   int array[NSIZE];
   for(int i=0;i<NSIZE; ++i)
    {
        array[i] = exp2(i);
    }

    func1(array, NSIZE);

    return 0;
}

void func1(int array[], int size)
{
    int start=0, end=size;
    printf("sizeof(array[]) %ld\n", sizeof(array));
    while(start++ < size)
    {
        printf("value: %d\tat address: %p\n", *array, array);
        ++array;
    }
}