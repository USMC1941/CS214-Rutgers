#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "helper.h"


/*
Initialize a BUFFER by allocate initSize byte of memory
*/
char* initBuffer(BUFFER* pBuf, int initSize) {
	if (initSize == 0) {
		pBuf->data = NULL;
		pBuf->length = 0;
	}
	else {
		pBuf->data = (char*)malloc(initSize * sizeof(char));
		if (pBuf->data == NULL) {
			pBuf->length = 0;
		}
		else {
			pBuf->length = initSize;
		}
	}
	//
	return pBuf->data;
}


/*
Resizes the BUFFER by re-allocate size byte of memory
*/
char* resizeBuffer(BUFFER* pBuf, int size) {
	if (pBuf->length == size) {
		// No change needed
	}
	else {
		pBuf->data = realloc(pBuf->data, size);
		if (pBuf->data == NULL) {
			pBuf->length = 0;
		}
		else {
			pBuf->length = size;
		}
	}
	//
	return pBuf->data;
}


/*
Frees buffer memory
*/
void freeBuffer(BUFFER* pBuf) {
	if (pBuf->data) {
		free(pBuf->data);
		//
		pBuf->data = NULL;
		pBuf->length = 0;
	}
}


/*
Strip of Newline char at the end of the string
*/
void stripOffNewline(BUFFER* pBuf) {
	int len = strlen(pBuf->data);
	// The last character
	if ( *(pBuf->data + len - 1) == '\n' ) {
		*(pBuf->data + len - 1)  = '\0';
	}
}


/*
Compare string regardless cases
*/
int strcicmp(char const *input1, char const *input2) {
	int i;
    for (;; input1++, input2++) {
        i = tolower(*input1) - tolower(*input2);
        if (i != 0 || !*input1) {
            return i;
		}
    }
}