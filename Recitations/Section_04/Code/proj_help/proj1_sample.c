/* Created by Hanxiong Chen @ Oct. 26, 2017 
 *
 * ////////////////////////////////////////
 * THIS CODE IS ONLY A GUIDE FOR SOMEONE 
 * WHO DOES HAVE NO IDEA ABOUT ANYTHING.
 * DO NOT USE THIS CODE AS YOUR PROJECT
 * DIRECTLY.
 * ////////////////////////////////////////
 *
 * This demo code is to recursively print
 * out the directory name and the file n-
 * ame. The first process will receive all
 * the pids created by all the processes \
 * and print them out.
 *
 * You can read the code and comment first
 * Then read the README file to see the l-
 * ayout of program.
 * */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <wait.h>

#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

/* We need this global int array to save the pipe \
 * for talking to parent process. To see the details
 * plese go and check pipe_sample.c*/
int parent[2] = {-1, -1};
int initpid;

/* This buffer is for send buffer or for the final \
 * print use.
 * */
int buffer[255];

/* offset can be used to know the length of msg sent
 * by child process. Since this is a int array not a
 * char array, we cannot know the length of the array
 * by calling strlen() function. We have to maintain
 * the length of the array up to now.
 * */
int offset = 0;

/* This function will be called recursively to print
 * out all the info of directories and subdirectories
 * also the file info under these directories.
 * */
void printDirInfo(char *dir)
{
	DIR *dp = NULL;
	struct dirent *curObj = NULL;
	if ((dp = opendir(dir)) == NULL)
	{
		fprintf(stderr, "Can't open directory: %s\n", dir);
		return;
	}

	while (curObj == readdir(dp))
	{
		if (!strcmp(".", curObj->d_name) ||
			 !strcmp("..", curObj->d_name))
		{
			continue;
		}

		/* The same as pp[] in pipe_sample.c. This is
		 * a pipe to recieve msg from child process*/
		int child[2];
		if (pipe(child) == -1)
		{
			perror("pipe");
			exit(2);
		}

		/* ONE MORE TIME: create pipe before fork! */

		/* Use d_type to know if current file is a 
		 * file or a directory. 
		 * If a file: fork and printout file name and
		 *            file size
		 * If a dir : fork and recursively call this\
		 *            function
		 **/
		if (curObj->d_type == DT_REG)
		{
			int pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(1);
			}
			if (pid == 0)
			{
				char *newPath = (char *)malloc(
					 strlen(curObj->d_name) + strlen(dir) + 2);

				newPath[0] = '\0';
				strcpy(newPath, dir);
				strcat(newPath, "/");
				strcat(newPath, curObj->d_name);

				/* replace this part with your sorter module */
				//////////////////////////////////////
				int fd = open(newPath, O_RDONLY);
				if (fd < 0)
				{
					fprintf(stderr, "Can't open file: %s\n", newPath);
					return;
				}
				int len = lseek(fd, 0, SEEK_END);
				close(fd);

				printf("%-30s%s%d\n", newPath, " ", len);
				free(newPath);
				/////////////////////////////////////

				/* We must use break here not exit(0) 
				 * Or we will suffer from memory leak
				 * */
				break;
			}
			else
			{
				/* The same as pipe_sample.c, wait child
				 * process to be done and receive pids s
				 * ent by its child.
				 * 
				 * You need to block your parent process
				 * here. If you are using signal_handler
				 * to do wait(), then your parent proces
				 * s can be finished before your child \
				 * process. Then you will be failed to \
				 * receive from child and not albe to s-
				 * end all the pids to parent. 
				 */
				wait(NULL);
				close(child[1]);
				/* the parent process for a file only n-
				 * eed to send one pid to its parent. so
				 * only sizeof(int) is enough
				 * */
				int *sendbuf = (int *)malloc(sizeof(int));
				memcpy(sendbuf, &pid, sizeof(int));

				/* The first process don't need to send\
				 * msg to anyone else. The first process
				 * would not modify the global int array
				 * so the value should be -1
				 * */
				if (parent[1] != -1)
				{
					write(parent[1], sendbuf, sizeof(int));
				}

				/* This line of code only to prepare for 
				 * printing out pids.
				 * */
				if (parent[1] == -1)
				{
					memcpy(buffer + offset, sendbuf, sizeof(int));
					offset++;
				}
				free(sendbuf);
				close(child[0]);
			}
		}
		else if (curObj->d_type == DT_DIR)
		{
			int pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(1);
			}
			if (pid == 0)
			{
				char *newPath = (char *)malloc(
					 strlen(curObj->d_name) + strlen(dir) + 2);

				newPath[0] = '\0';

				strcpy(newPath, dir);
				strcat(newPath, "/");

				strcat(newPath, curObj->d_name);
				printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\n", newPath);

				//save parent pipe
				memcpy(parent, child, 2 * sizeof(int));

				/* Only child process for directory will
				 * recursively call this function
				 * */
				printDirInfo(newPath);

				/* In the above code, I said we cannot \
				 * use exit(0) when the child process of
				 * processing files is done and that wi-
				 * ll result in memory leak. Here is the
				 * reason. If you do exit(0), this line\
				 * line of code can never be executed. \
				 * You probably will get memory leak
				 * */
				free(newPath);
				break;
			}
			else
			{
				/* We need to stop to wait our child pro
				 * cesses. Or we gonna lose pids.
				 * */
				wait(NULL);
				close(child[1]);

				int *recvbuf = (int *)malloc(255 * sizeof(int));

				/* This time we may receive a series of pids */
				size_t len = read(child[0], recvbuf, 255 * sizeof(int));
				if (len == -1)
				{
					len = 0;
				}

				int send_size = (len / sizeof(int) + 1) * sizeof(int);
				int *sendbuf = (int *)malloc(send_size);

				memcpy(sendbuf, recvbuf, len);
				memcpy(((char *)sendbuf) + len, &pid, sizeof(int));

				if (parent[1] != -1)
				{
					write(parent[1], sendbuf, send_size);
				}
				free(recvbuf);

				if (initpid == getpid())
				{
					memcpy(buffer + offset, sendbuf, send_size);
					offset += (send_size / sizeof(int));
				}
				close(child[0]);
				free(sendbuf);
				/* We do not break here, because we need to
				 * keep searching current directory
				 * */
			}
		}
	}
	/* Again and Again, Don't forget to close fd */
	close(parent[1]);
	closedir(dp);
	return;
}

int main(int argc, char *argv[])
{
	char *base = ".";
	if (argc >= 2)
	{
		base = argv[1];
	}
	printf("Directory index from %s\n", base);
	initpid = getpid();
	printDirInfo(base);

	if (initpid == getpid())
	{
		printf("------------------------\n");
		for (int i = 0; i < offset; i++)
		{
			printf("pid: %d\n", buffer[i]);
		}
		printf("total process num: %d\n", offset);
	}
	return 0;
}
