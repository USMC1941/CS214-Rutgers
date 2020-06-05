// gcc -o pcp1 pcp1.c -pthread
// ./pcp1

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 5 //queue length

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t full;
sem_t empty;

int top = 0;    //queue top
int bottom = 0; //queue bottom

void *produce(void *arg)
{
    int i;
    for (i = 0; i < MAX * 2; i++)
    {
        printf("producer is preparing data\n");
        sem_wait(&empty);

        pthread_mutex_lock(&mutex);

        top = (top + 1) % MAX;
        printf("now top is %d\n", top);

        pthread_mutex_unlock(&mutex);

        sem_post(&full);
    }
    return (void *)1;
}

void *consume(void *arg)
{
    int i;
    for (i = 0; i < MAX * 2; i++)
    {
        printf("consumer is preparing data\n");
        sem_wait(&full);

        pthread_mutex_lock(&mutex);

        bottom = (bottom + 1) % MAX;
        printf("now bottom is %d\n", bottom);

        pthread_mutex_unlock(&mutex);

        sem_post(&empty);
    }

    return (void *)2;
}

int main(int argc, char *argv[])
{
    pthread_t thid1;
    pthread_t thid2;
    pthread_t thid3;
    pthread_t thid4;

    int ret1;
    int ret2;
    int ret3;
    int ret4;

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, MAX);

    pthread_create(&thid1, NULL, produce, NULL);
    pthread_create(&thid2, NULL, consume, NULL);
    pthread_create(&thid3, NULL, produce, NULL);
    pthread_create(&thid4, NULL, consume, NULL);

    pthread_join(thid1, (void **)&ret1);
    pthread_join(thid2, (void **)&ret2);
    pthread_join(thid3, (void **)&ret3);
    pthread_join(thid4, (void **)&ret4);

    return 0;
}