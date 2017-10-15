#include <stdio.h>

int main(){
	char buff[] = {1,2,3,4,5,6,7,8,9,10};
	char x = 0;
	
	*(buff -1) = 16;
	
	buff [10] = 16;
	
	printf("%p  %p  %p %d\n", &buff[0],  &buff[9], &x, x);
}