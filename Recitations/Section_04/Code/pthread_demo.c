/* To run the code, please change the name of main function
 * to main() and change other tests main function to other
 * names..
 * To compile the code:
 * $ gcc -o test ./test.c -lpthread
 *
 * */

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

//////  TEST 1: call pthread_cancel to cancel itself //////
void * func(void *arg) {
	printf("\n Thread one is running...\n");

	// pthread_self() returns the caller's tid
	exit(1);
	//pthread_cancel(pthread_self());
	//pthread_exit(NULL);
}

int main1(void) {
	int err;
	// These two variables stores our thread ids
	pthread_t thread1, thread2;
	
	// Create a thread
	err = pthread_create(&thread1, NULL, func, NULL);

	// sleep(3);
	// like malloc(), pthread_create is not always successful
	if (err != 0) {
		printf("\ncan't create thread :[%s]", strerror(err));
	}
	else {
		printf("\n Thread created successfully\n");
	}

	// Thread version of waitpid()
	pthread_join(thread1, NULL);

	printf("thread exit...\n");
	return 0;
}

/////////////////// TEST 1 END ///////////////////////////


/// TEST 2: call pthread_cancel to cancel other thread ///
/* In this demo, you will see thread 2, which is running
 * func2 will be terminated by thread 1 by calling pthr-
 * ead_cancel.
 * */
pthread_t temp_thread;

void * func1(void *p) {
	int counter = 0;
	while (1) {
		printf("thread one is running...\n");
		sleep(1);
		counter++;
    /* If counter == 2 cancel thread 2 and exit */
		if (counter == 2) {
			pthread_cancel(temp_thread);
			pthread_exit(NULL);
		}
	}
}

void * func2(void *p) {
	temp_thread = pthread_self();
	while (1) {
		printf("thread two is running...\n");
		sleep(1);
	}
}

int main() {
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, func1, NULL);
	pthread_create(&thread2, NULL, func2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return 0;
}

/////////////////// TEST 2 END ///////////////////////////

//// TEST 3: use pthread_exit() return value to caller ///
/* This code is from 
 * http://www.thegeekstuff.com/2012/04/terminate-c-thread/
 */

pthread_t tid[2];
int ret1, ret2;

void * doSomeThing(void *arg) 
{
	unsigned long i = 0;
	pthread_t id = pthread_self();

	for (i = 0 ; i < (0xFFFFFFFF) ; i++);

	if (pthread_equal(id, tid[0]))
	{
		printf("\n First thread processing done\n");
		ret1 = 100;
		pthread_exit(&ret1);
	}
	else
	{
		printf("\n Second thread processing done\n");
		ret2 = 200;
		pthread_exit(&ret2);
	}
	return NULL;
}

int main3(void)
{
	int i = 0;
	int err; 
	int *ptr[2];

	while(i < 2)
	{
		err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
		if (err != 0)
		{
			printf("\n can't create thread: [%s]", strerror(err));
		}
		else
		{
			printf("\n Thread created successfully \n");
		}
		i++;
	}

	pthread_join(tid[0], (void**) &(ptr[0]));
	pthread_join(tid[1], (void**) &(ptr[1]));

	printf("\n return value from first thread id [%d]\n", *ptr[0]);
	printf("\n return value from second thread is [%d]\n", *ptr[1]);

	return 0;
}

/////////////////// TEST 3 END ////////////////////////////////


