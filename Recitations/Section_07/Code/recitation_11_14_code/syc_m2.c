#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// compile by gcc -o syc_m2 syc_m2.c -pthread
// ./syc_m2

int MAX = 10;
int count = 1;

pthread_mutex_t mutex;

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
        if (count % 2 == 0)
        {
            // pthread_mutex_lock(&mutex);
            print_star(count++);
            pthread_mutex_unlock(&mutex);
            // printf(" even: %d\n", count);
            // count++;
            //printf(" even: %d\n", count++);
        }
        // pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

void *odd(void *arg)
{
    //printf("This is odd thread()\n");

    while (count < MAX)
    {
        pthread_mutex_lock(&mutex);
        if (count % 2 == 1)
        {
            // pthread_mutex_lock(&mutex);
            print_star(count++);
            pthread_mutex_unlock(&mutex);
            // printf(" odd: %d\n", count);
            // count++;
            // printf(" odd: %d\n", count++);
        }
        // pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

int main()
{
    pthread_t t1;
    pthread_t t0;

    pthread_mutex_init(&mutex, 0);

    pthread_create(&t1, 0, &odd, NULL);
    pthread_create(&t0, 0, &even, NULL);

    pthread_join(t1, 0);
    pthread_join(t0, 0);

    pthread_mutex_destroy(&mutex);

    return 0;
}