#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// compile by gcc -o syc_c3 syc_c3.c -pthread
// ./syc_c3

int MAX = 10;
int count = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t number = PTHREAD_COND_INITIALIZER;

void print_star(int i)
{
    int j;
    for (j = 1; j <= i; j++)
    {
        printf("*");
    }
    // printf(" %d", i);
    printf("\n");
    //printf(" %d\n", i);
}
void *even(void *arg)
{
    //printf("This is even thread()\n");
    while (count <= MAX)
    {
        pthread_mutex_lock(&mutex);
        if (count % 2 == 1)
        {
            pthread_cond_wait(&number, &mutex);
            // printf(" even: %d\n", count);
            // count++;
            //printf(" even: %d\n", count++);
        }
        printf("This is even thread()\n");
        print_star(count++);
        pthread_cond_signal(&number);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

void *odd(void *arg)
{
    //printf("This is odd thread()\n");
    while (count < MAX)
    {
        pthread_mutex_lock(&mutex);
        if (count % 2 == 0)
        {
            pthread_cond_wait(&number, &mutex);
            // printf(" odd: %d\n", count);
            // count++;
            // printf(" odd: %d\n", count++);
        }
        printf("This is odd thread()\n");
        print_star(count++);
        pthread_cond_signal(&number);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

int main()
{
    pthread_t t1;
    pthread_t t0;

    pthread_create(&t1, 0, &odd, NULL);
    pthread_create(&t0, 0, &even, NULL);

    pthread_join(t1, 0);
    pthread_join(t0, 0);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&number);

    return 0;
}