#include <pthread.h>
#include <unistd.h>
#include <iostream>

pthread_mutex_t mtx;
pthread_cond_t cv;

void* func_1(void* arg)
{
    (void)arg;
    for(;;)
    {   
        pthread_mutex_lock(&mtx);
        std::cout<<".1.";
        pthread_mutex_unlock(&mtx);
        sleep(1);
        std::cout.flush();
    }
}

void* func_2(void* arg)
{
    (void)arg;
    int i = 0;
    for(;;)
    {
        pthread_mutex_lock(&mtx);

        std::cout<<".x.";
        sleep(1);
        std::cout.flush();

        if (i++ > 5)
        {
            pthread_cond_signal(&cv);
        }
        pthread_mutex_unlock(&mtx);
    }
}

int main(int argc, char* argv[])
{
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, func_1, NULL);
    pthread_create(&t2, NULL, func_2, NULL);

    void* ret;
    pthread_join(t1, &ret);
    pthread_join(t2, &ret);

    return 0;
}