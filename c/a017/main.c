
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

const int BUFFER_SIZE = 256;

int max(int a, int b)
{
    if (a < b)
        return b;
    return a;
}

void* generate_random_stream(void* arg)
{
    int current_size = 0;
    char buffer[BUFFER_SIZE];
    while(1)
    {
        current_size += snprintf(buffer+current_size, max(0, BUFFER_SIZE-current_size), "%d ", rand());
        //sleep(1);

        if(current_size > BUFFER_SIZE*3/4)
        {
            printf("%s \n", buffer);
            current_size = 0;
        }
    }
}

int main(int argc, char* argv[])
{

    pthread_t t1;
    pthread_create(&t1, NULL, &generate_random_stream, NULL);

    int i=0;
    while(i++ > 10);
    {
        printf("main\n");
        sleep(2);
    }

    int result = 0;

    printf("reached pthread_join ");
    pthread_join(t1, (void**)&result);
    printf("thread returned %d\n", result);
}