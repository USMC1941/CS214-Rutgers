#include <stdio.h>

//min=7,  predict= 12
struct X {
	short s;
	int   i;
	char  c;
};

//min = 7, predict = 8
struct Y {
	int   i;
	char  c;
	short s;
};

//min = 7, predict = 8
struct Z {
	int   i;
	short s;
	char  c;
	struct X  x;
};


union M {
	char c1;
	int i2;
	struct X sX;
	struct Y sY;
	struct Z sZ;
};


int getCounter();


const int sizeX = sizeof(struct X);
const int sizeY = sizeof(struct Y);
const int sizeZ = sizeof(struct Z);
const int sizeM = sizeof(union M);

int main(){
	printf("%d  %d  %d %d\n", sizeX, sizeY, sizeZ, sizeM);
	
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	printf("%d\n", getCounter());
	
}


int getCounter() {
	static int s_counter = 0;
	
	return s_counter++;
}