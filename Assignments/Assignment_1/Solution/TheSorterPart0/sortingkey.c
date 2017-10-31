#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "sortingkey.h"
#include "tokenizer.h"
#include "helper.h"


/*
Gets the index for the sortingkey from the Header Line
Return:
	1 Failed
	0 OK
*/
int getSortingKeyIndexFromHeaderLine(char* input, char* key, SKeyIndex* pSKI) {
	int outcome = 1;
	
	// Check inputs
	if (pSKI == NULL || input == NULL ||key == NULL) {
		return outcome;
	}

	// Initilize to invalid index
	pSKI->index = -1;
	
	if (input[0] != '\0' && key[0] != '\0') {																								// Check input before doing it
		char* pToken;
		//
		Tokenizer tokenizer;
		initTokenizer(&tokenizer, input, DELIMITER, DBLQUOTE);
		//
		pToken = getNextToken(&tokenizer);
		int index = 0;
		//
		while (pToken != NULL) {
			if (strcicmp(pToken, key) == 0) {																								// Key and token are equal case-nonsensitive
				//
				pSKI->index = index;
				outcome = 0;
				//
				break;
			}
			else {																																		// Key and token are not equal. Continue loop
				//
				pToken = getNextToken(&tokenizer);
				index++;
			}
		}
	}
	else {
		// Invalid input
	}
	//
	return outcome;
}