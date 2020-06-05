// sample code for basic type
#include <stdio.h>
#include <string.h>

typedef struct
{
	char a;
	int b;
	float c;
	double d;
} Test;

enum weekday
{
	sun,
	mon,
	tue,
	wed,
	thu,
	fri,
	sat
};

int main(int argc, char const *argv[])
{
	/*
	key point behind the different type the length of byte it take in memory
	*/
	printf("sizeof char (%ld)\n", sizeof(char));
	printf("sizeof integer (%ld)\n", sizeof(int));
	printf("sizeof float (%ld)\n", sizeof(float));
	printf("sizeof double (%ld)\n", sizeof(double));

	enum weekday day = sun;
	printf("sizeof enumn (%ld)\n", sizeof(day));
	Test t;

	// struct alignment depends on underlying archetecture
	printf("sizeof Test (%ld)\n", sizeof(t));
	int a[10];
	printf("sizeof array (%ld)\n", sizeof(a));

	int *p = a;
	printf("sizeof pointer (%ld)\n", sizeof(p));
	printf("print %p\n", p);

	char str[20] = "abcdefg";
	printf("sizeof string (%ld)\n", sizeof(str));
	printf("len of str (%ld)\n", strlen(str));
	printf("the contents of string (%s)\n", str);

	int i = 0;
	int length = strlen(str);
	for (i = 0; i < length + 1; i++)
	{
		printf("%c\n", str[i]);
	}
	//
	return 0;
}
