#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int pid = fork();
	char *argv[2] = {"./hello", NULL};
	if (pid == 0)
	{
		printf("Now in child process");
		//run executable "hello" under current dir in child process
		execv("./hello", argv);
		_exit(0);
	}
	else
	{
		wait(2);
		printf("finished parent process.\n");
	}
	return 0;
}
