/* Author: Hanxiong Chen
 * ///////////////////////////////////////////////////////
 * This demo code is to show how to create multi-processes
 * and send a sequence of messages to their parents.
 * The structure is:
 * Process: A --create-> B --create-> C --create-> D
 * Message: A <-pid_cd-- B <--pid_d-- C <-nothing- D
 * 
 * My code will try to create four processes. D is the la-
 * st process to be created. I will send all the pids to \
 * the first porcess and try to print out all of them.
 *
 * D send nothing to C, and C send the pid of D to B. B r-
 * eceive the msg of D and append the pid of C, then send
 * to its parent A. A will printout all the pids it gets.
 *
 * To understand this code, you need to know that fork() \
 * will keep    all the variable status until you call f-
 * ork(). That means all the arrays and variables shoud h-
 * ave the same values. If you want your child process to
 * have the same values as parent process, make sure to do
 * that before fork(). Everything after fork can be diffe-
 * rent.
 *
 * To compile:
 *   $ gcc -o test ./pipe_sample.c 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	int initpid = getpid();
	/* Each child process shoud maintain two
	 * pipes. One is to talk to its parent,\
	 * another one is to talk to its child.
	 * So we need to save the pipe of parent
	 * outside of for loop to make sure that
	 * we will not loose it
	 * */
	int parent[2] = {-1, -1};
	for (int i = 0 ; i < 4 ; i++) {
		/* every new loop, we create a new
		 * pipe for its child process */
		int pp[2];
		if (pipe(pp) == -1) {
			perror("pipe");
			exit(2);
		}
		/* Again, do pipe before fork() */

		int pid = fork();
		if (pid < 0) {
			perror("fork");
			exit(1);
		}
		if (pid == 0) {
			/* Save the pipe for talking to parent */
			memcpy(parent, pp, 2 * sizeof(int));
			/* Since we are not doing the next for 
			 * loop, so pp and parent are the same 
			 * we just close the read file descri-
			 * ptor of parent pipe because we only
			 * need this pipe to write pids not to
			 * read anything.
			 * */
			close(pp[0]);

			/* continue to the next for loop and \
			 * we will create a new pipe pp. Then
			 * we can use the new pp to talk to n-
			 * ew child process
			 * */
			continue;
		}
		else {
			/* parent process just wait their chi-
			 * ld process. Then we can read infor-
			 * mation through the pipe
			 * */
			wait(NULL);

			/* pp is the pipe to receive msg from
			 * child process. We don't need to w-
			 * rite to it. So close the write fi-
			 * le descriptor
			 * */
			close(pp[1]);
			int * recvbuf = (int*) malloc(255 * sizeof(int));

			/* read from pp[0] to receive pids s-
			 * ent by its child process.*/
			size_t len = read(pp[0], recvbuf, 255 * sizeof(int));
			close(pp[0]);

			/* As what we can see at the beginning
			 * the last process will not send any-
			 * thing to its parent. So we need to 
			 * handle this case by setting len to 0
			 * */
			if (len == -1) {
				len = 0;
			}

			/* prepare the send buffer: copy the r-
			 * eceived data to buffer and append i-
			 * ts child process' pid
			 * */
			int send_size = (len / sizeof(int) + 1) * sizeof(int);
			int * sendbuf = (int*) malloc(send_size);

			memcpy(sendbuf, recvbuf, len);
			memcpy( ((char*)sendbuf) + len, &pid, sizeof(int) );

			/* send our message to our parent thr-
			 * ough our saved parent pipe: parent[1]
			 * */
			if (parent[1] != -1) {
				write(parent[1], sendbuf, send_size);
			}
			/* Don't forget to close pipe and free \
			 * allocated memories*/
			close(parent[1]);
			free(recvbuf);

			printf("true pid: %d\n", pid);

			/* If it is the first process, I will c-
			 * all printf to printout all the pids*/
			if (initpid == getpid()) {
				printf("-------------------\n");
				for (int i = 0; i < send_size / sizeof(int); i++) {
					printf("test pid: %d\n", sendbuf[i]);
				}
			}
			free(sendbuf);
			break;
		}
	}	
	return 0;
}
