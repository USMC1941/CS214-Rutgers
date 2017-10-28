#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int main() {
	printf("My pid is %d\n", getpid());
	while(1) {}
	//printf("wake up...\n");
	return 0;
}
