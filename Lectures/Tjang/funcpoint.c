#include <stdio.h>
#include <string.h>

void foo();
void bar();

int main(){
	printf("main() is at: %p \n", &main);
	
	printf("bar() is at: %p \n", &bar);
	foo();
	//
	return 0;
}

void printarr(char * arr, int size) {
	int i;
	for(i = 0; i < size; i++){
		printf("%d\n",arr[i]);
	}
}

void foo(){
	printf("-----\n%p\n%p\n%p\n%p\n%p\n%p\n-------");
	int z;
	int k[5];
	int x;
	printf("In foo() x is at: %p\n", &x);

	void ** y = (void *) &z;
	*(y + 3) = &bar;
	//
	int i = 0;
	for(i = 0; i < 10; i++){
		// y++;
		printf("x + %d : %p \n",i, *y);
		y++;
	}
}

void bar() {
	printf("This should never ever run!!! WE smashed the stack!\n");
}