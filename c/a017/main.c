
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    int bytes_read = 0;
    int counter = 0;
    const int iteration_limit = 1000;
    while(counter++ < iteration_limit)
    {
        bytes_read = snprintf(buffer+current_size, max(0, BUFFER_SIZE-current_size), "%d ", rand());
        if (bytes_read == -1)
        {
            perror("snprintf");
            break;
        }
        current_size += bytes_read;
        //sleep(1);

        if(current_size > BUFFER_SIZE*3/4 && counter == iteration_limit)
        {
            printf("%s \n", buffer);
            current_size = 0;
        }
    }
    pthread_detach(pthread_self());
    printf("THREAD REACHED ITS END\n");
}

int main(int argc, char* argv[])
{

    pthread_t t1;
    pthread_create(&t1, NULL, &generate_random_stream, NULL);

    int size_1 = __CHAR_BIT__*__CHAR_BIT__;
    char str_1[size_1];
    memset(&str_1, '-', size_1);
    str_1[size_1] = '\0';
    int i=0;
    while(i++ < 10);
    {
        printf("MSG from main %d \n%s\n", i, str_1);
        sleep(1);
    }

    int result = 0;
}