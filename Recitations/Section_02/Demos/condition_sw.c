#include <signal.h>
#include <pthread.h>
#include <stdio.h>

#include <sys/param.h>


static int var = 0;
void sigint(int signo) {
    if (signo == SIGINT)
        {
            return;
        }
}

int main(void) {
    pthread_cond_t cvar = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    signal(SIGINT, sigint);
    
    while (var == 0) {
        puts("Waiting");
        pthread_cond_wait(&cvar, &lock);
        if (var == 0) {
            puts("Spurious Wakeup");
        }
    }
    
}