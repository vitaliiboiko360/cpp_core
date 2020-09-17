#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


#define size 256
struct string
{
    char buffer[size];
};

void* fill_string(void* arg)
{
    struct string* str = (struct string*)arg;
    int acc = 0;
    for(int i=0; i<size; ++i)
    {
        str->buffer[i] = (char)((rand() % 25) + 97);
        for(int i=0; i<100; ++i)
        {
            if (i % 2 == 0)
            {
                acc += i;
            }
        }
        acc = 0;
    }
    str->buffer[size] = 0;
    printf("END OF FILL STRING FUNCTION\n");
}

void* thread_function(void* arg)
{
    struct string* str = (struct string*)arg;
    printf("thread recieved str:\n %s \n", str->buffer);
    printf("END OF THREAD FUNCTION\n");
}

int main(int argc, char* argv[])
{
    int number = 5000;
    struct string str;
    int status;
    void* result;
    for (int i=0; i<5; i++)
    {
        printf("\n\n\n\nITERATION NUMBER %d\n\n\n\n", i);
        sleep(1);
        pthread_t t1;
        pthread_t t2;
        status = pthread_create(&t1, NULL, &fill_string, (void*)&str);
        status = pthread_create(&t2, NULL, &thread_function, (void*)&str);

        pthread_join(t1, &result);
        pthread_join(t2, &result);
    }

    return 0;
}