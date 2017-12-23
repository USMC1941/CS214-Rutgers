#include <string.h>
#include <stdio.h>


char *to_message(int num) {
	char static result [256];

	if (num < 10) {
		sprintf(result, "%d: blah blah", num);
	}
	else {
		strcpy(result, "Unknown");
	}

	return result;
}
