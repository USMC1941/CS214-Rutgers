#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pid_t child = -2;

void *sleepnprint(void *arg) {

	printf("%d:%s starting up...\n", getpid(), (char *) arg);

	pid_t pid = fork();

	while (child == -2) {
		sleep(1);
	}

  printf("%d:%s finishing...\n",getpid(), (char*)arg);

  return NULL;
}


int main() {
	pthread_t tid1, tid2;
	pthread_create(&tid1,NULL, sleepnprint, "New Thread One");
	pthread_create(&tid2,NULL, sleepnprint, "New Thread Two");

	child = fork();
	printf("%d:%s\n",getpid(), "fork()ing complete");
	sleep(3);

	printf("%d:%s\n",getpid(), "Main thread finished");

	pthread_exit(NULL);

	return 0; /* Never executes */
}