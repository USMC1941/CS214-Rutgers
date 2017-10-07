/*Author: Hanxiong Chen*/

//////////////////////////////////////////////////////////
// This code is not just for HW3, it is also an example //
// of a better coding style. Pay attention to the way I //
// name the variables and functions. Also notice the    //
// spaces I use. For some introduction of coding style  //
// you can check the last slide of Recitation 2.        //
//////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Description: 
 *		find the location of target string
 *		in the given string
 * Input: 
 *		source: a pointer to a given string
 *		target: a pointer to a target string
 * return:
 *		position of the first matching place; 
 *		-1 on not found
 * */
int findSubstr(const char *source, const char *target) {
	if (source == NULL || target == NULL) {
		return -1;
	}
	int target_size = strlen(target);
	int source_size = strlen(source);
	int i, j;
	for (i = 0; i < source_size - target_size + 1; i++) {
		for (j = 0; j < target_size; j++) {
			if (source[i + j] != target[j]) {
				break;													
			}
		}
		if (j == target_size) {
			return i;
		}
	}
	return -1;
}

/* Description: 
 *		find the string in a given string and replace it with a 
 *		new string. The "to" string must have the same length 
 *		with "from" string.
 * Input: 
 *		string: original string
 *		from: the target string you want to replace
 *		to: the string you want to replace with
 * Return:		
 *		none
 * */
void replace(char string[], char from[], char to[]) {
	if (string == NULL || from == NULL || to == NULL) {
		return;
	}
	int stringLen = strlen(string);
	int fromLen = strlen(from);
	int toLen = strlen(to);

	/*step 1: search the target*/
	int pos = findSubstr(string, from);
	if (pos == -1) {
		return;
	}
	/*step2: replace the string*/
	for (int i = 0 ; i < toLen ; i++) {
		string[pos + i] = to[i];
	}
}

/* Description:
 *		Find the string "from" from the given string "*string"
 *		Then replace "from" with "to". In this function, the 
 *		length of "from" and "to" is not necessarily the same
 * Input:
 *		**string: the pointer of the given string's pointer;
 *		from: the target string you want to replace
 *		to: the string you want to replace "from" with
 * Return:
 *		none
 * */
void replace2(char *string[], char from[], char to[]) {
	
	if (string == NULL || *string == NULL || 
			from == NULL || to == NULL) {
		return;
	}
	int stringLen = strlen(*string);
	int fromLen = strlen(from);
	int toLen = strlen(to);

	/* step 1: search the target */
	int pos = findSubstr(*string, from);
	if (pos == -1) {
		return;
	}

	/* step2: replace the string */
	int size = stringLen - fromLen + toLen;
	char * newString = (char *) malloc(sizeof(char) * size); 
	
	memcpy(newString, *string, pos - 0);
	memcpy(newString + pos, to, toLen);
	memcpy(newString + pos + toLen, 
		   *string + pos + fromLen,
		   size - pos - toLen + 1);
	/* ONLY FOR AN EXAMPLE */
	*string = newString;
}


int main(int argc, char **argv) {
	/********* EXPERIMENT 1 ***********/
	// This is to show the question 0 in HW3
	/*char *s = "Hello";
	char s1[] = "Hello";
	printf("sizeof print: %d\n", sizeof(s));
	printf("strlen print: %d\n", strlen(s));
	printf("sizeof s1[] : %d\n", sizeof(s1));
	return 0;*/

	/********* EXPERIMENT 2 **********/
	// This is to show the question 1 in HW3
	/*char string[] = "recieve";
	printf("original string: %s\n", string);
	replace(string, "ie", "ei");
	printf("after replace: %s\n", string);
	return 0;*/

	/********* EXPERIMENT 3 *********/
	// This experiment shows how to replace
	// a string with one who has different
	// length
	/*char * string = argv[1];
	char * from = argv[2];
	char * to = argv[3];
	printf("original: %s\n", string); 
	// The function replace2 will change
	// the address of variable string 
	replace2(&string, from, to);
	printf("after replace: %s\n", string);
	
	// Only for an example. Not a good way. 
	free(string);
	return 0;*/

	/******** EXPERIMENT 4 *********/
	// This is to show question 2 in HW3
	char * str1 = argv[1];
	char * str2 = argv[2];
	size_t str1Len = strlen(str1);
	size_t str2Len = strlen(str2);

	char * container = (char *) malloc( sizeof(char) * (str1Len + str2Len + 1) );
	// Why I need to copy str1Len + 1 bytes instead of str1Len bytes?
	// Think about how does strcat function work and how does it know
	// where to start the concatenation.
	memcpy(container, str1, str1Len + 1);
	strcat(container, str2);
	printf("string 1: %s\n", container);

	// This method is a better choice
	char * container2 = (char *) malloc( sizeof(char) * (str1Len + str2Len + 1) );
	strcpy(container2, str1);
	strcat(container2, str2);
	printf("string 2: %s\n", container2);

	// This is to show you that how does strcat work.
	char * container3 = (char *) malloc( sizeof(char) * (str1Len + str2Len + 1) );
	strcpy(container3, str1);
	strcpy(container3 + str1Len, str2);
	printf("string 3: %s\n", container3);

	return 0;
}