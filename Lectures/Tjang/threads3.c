#include <pthread.h>
#include <stdio.h>
void* myfunc(void* ptr) {
    int i = *((int *) ptr);
    printf("%d ", i);
    return NULL;
}

int main() {
	//create 10 threads calling myfunc with successively higher numbers

	int i=0;
	pthread_t tid;

	for(i=0; i<10; i++){

		pthread_create(&tid, NULL, myfunc, &i);
	}

	pthread_exit(NULL);
}

