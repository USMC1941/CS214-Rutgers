/* Author: Hanxiong Chen
 * /////////////////////////////////////////////
 * This demo code shows how to use pipes to create
 * two way communications between two processes. 
 * /////////////////////////////////////////////
 *
 * You must remember that one pipe is only allows
 * one-to-one communication on one direction. Two
 * way talk must use two pipes.
 *
 * You can compile the code by:
 *  $ gcc -o twoway ./two_way_pipe_comm.c
 * Then run
 *  $ ./twoway
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	/* prepare two pipes */
	int parent[2];
	int child[2];

	/* parent pipe: parent --write--> child */
	/* child pipe:  parent <--write-- child */
	if (pipe(parent) == -1) {
		printf("parent pipe broken...\n");
	}
	if (pipe(child) == -1) {
		printf("child pipe broken...\n");
	}
	/* Once you have done this part, you will create two 
	 * pipes. Each pipe has two file descriptors. Take 
	 * parent as an example: parent[0] is for reading msg
	 * from  pipe and parent[1] is for writing msg to the
	 * pipe. 
	 * */

	/* Important: Make sure to create pipes before fork() */
	/* If you do fork first and then call pipe(), you will
	 * not be able to create a pipe between parent and child
	 * processes.
	 * */
	int pid = fork();
	if (pid < 0) {
		perror("fail: ");
	}

	if (pid == 0) {
		/* child process */
		char buffer[20];
		
		/* parent pipe is for parent writing to child 
		 * so we don't need the write file descriptor
		 * in child process here. Just close it.
		 * */
		close(parent[1]);

		/* read the message sent by parent through p-
		 * arent pipe: parent[0]
		 * Remember: 0 is for reading msg*/
		read(parent[0], buffer, 20);
		printf("child process receive message from parent: %s\n", buffer);

		/* Don't forget to close the fd once you are 
		 * done. Here we don't need to receive msg \
		 * through child pipe in child process, so \
		 * we close child[0]
		 * */
		close(parent[0]);
		close(child[0]);

		char sendbuf[] = "Hi, daddy!";
		/* Write msg to parent process through child
		 * pipe: child[1]
		 * */
		write(child[1], sendbuf, strlen(sendbuf) + 1);

		/* Don't forget to close fd */
		close(child[1]);
		exit(0);
	}
	else {
		char sendbuf[] = "Hi, my baby.";
		/* Parent process do not need to receive msg
		 * from parent pipe, so we just close the w-
		 * rting file descriptor of parent pipe.
		 * */
		close(parent[0]);
		write(parent[1], sendbuf, strlen(sendbuf) + 1);

		/* we need to wait for child process to be \
		 * done. Then we are sure there will be a msg
		 * for us to read
		 * */
		wait(NULL);

		/* we don't need to write anything through \
		 * child pipie because we are parent process
		 * . So we close child[1]. Actually you can 
		 * close it before wait() is fine.
		 * */
		close(child[1]);

		char recvbuf[20];

		/* Read from child pipe: child[0] */
		read(child[0], recvbuf, 20);

		printf("parent process receive message from child: %s\n", recvbuf);

		/* Again, NEVER FORGET TO CLOSE PIPE*/
		close(child[0]);
		close(parent[1]);
	}

	return 0;
}
