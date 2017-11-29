#include <stdio.h>
#include <pthread.h>

// remember to set compilation option-pthread
// refer to https://stackoverflow.com/questions/2251452/how-to-return-a-value-from-thread-in-c

void *busy(void *ptr)
{
    printf("threadIndex %d is doing sth\n", *((int *)ptr));
    
    sleep(2);
    
    return (void*)12345;
}

int main()
{

    pthread_t id;
    pthread_t self;
    int status;
    int threadNum = 10;

    int i = 0;
    int tIndex = 0;
    
    self = pthread_self();
    printf("current thread id %d\n", self);

    pthread_create(&id, NULL, busy, (void *)&tIndex);
    printf("waiting the terminal of threads id %d\n", id);
    pthread_join(id, (void**)&status);
    //print the return value of the thread
    printf("return value (%d) of the pthread (%d)\n", (int)status, id);
   
    printf("main thread finish, all thread is finished\n");
}

/*
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start)(void *), void *arg);
Returns 0 on success, or a positive error number on error

int pthread_join(pthread_t thread, void **retval);
Returns 0 on success, or a positive error number on error
If retval is a non-NULL pointer, then it receives a copy of the terminated thread’s return value—that is, the value that was specified when the thread performed a return or called pthread_exit()

void pthread_exit(void *retval);
The retval argument specifies the return value for the thread

diff between pthread_exit and return?
https://stackoverflow.com/questions/3844678/pthread-exit-vs-return

*/