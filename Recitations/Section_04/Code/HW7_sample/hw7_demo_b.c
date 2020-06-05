#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int pid = atoi(argv[1]);

	if (pid)
	{
		kill(pid, SIGINT);
	}
	return 0;
}
