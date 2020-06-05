#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main()
{
	printf("My pid is %d\n", getpid());
	int i = 60;
	while (--i)
	{
		write(1, ".", 1);
		if (i == 55)
		{
			kill(getpid(), SIGINT);
		}
		sleep(1);
	}
	write(1, "Done!", 5);
	return 0;
}
