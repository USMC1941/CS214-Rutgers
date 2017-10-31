#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "tokenizer.h"


/*
Initilizes the tokenizer
*/
void initTokenizer(Tokenizer* pTokenizer, char* _current_pointer, int _delimiter, int _quote) {
	pTokenizer->current_pointer = _current_pointer;
	//
	pTokenizer->pToken = NULL;
	pTokenizer->delimiter = _delimiter;
	pTokenizer->quote = _quote;
	pTokenizer->isEnded = FALSE;
}


/*
Tokenizes next token

return either the token or NULL if no more token.
Token could be an empty string.
This function changes the input string.

Handling token quoted with \"
Trim the token
*/
char* getNextToken(Tokenizer* pTokenizer) {
	char* pOutput;

	// Checks for either NULL Tokenizer pointer or no more tokens
	if (!pTokenizer) {																												// Null Tokenizer
		return NULL;	
	}
	else if (pTokenizer->isEnded) {																							// No more token
		return NULL;
	} 
	
	// Trim leading space
	while (isspace((unsigned char)*(pTokenizer->current_pointer))) {
		pTokenizer->current_pointer++;
	}

	// Handle quoted token. First check if it is a quoted token (token inside double quotes)
	if (*(pTokenizer->current_pointer) == pTokenizer->quote ) {												// If quoted token
		pTokenizer->current_pointer++;																						// Go pass the open quote
		//
		char* pQuote = strchr(pTokenizer->current_pointer, pTokenizer->quote);							// Find the closing quote
		//
		if (pQuote != NULL) {
			int length = pQuote - pTokenizer->current_pointer;														// Length of token: between two quotes. Could be 0
			//
			pTokenizer->pToken = pTokenizer->current_pointer;													// Get token
			*(pTokenizer->pToken + length) = '\0';																		// NULL  terminated the token
			//
			pTokenizer->current_pointer = pQuote + 1;																// Go past closing quote
			if (pTokenizer->current_pointer != '\0') {
				char* pDelimiter = strchr(pTokenizer->current_pointer, pTokenizer->delimiter);		// Find the delimiter
				if (pDelimiter) {
					pTokenizer->current_pointer = pDelimiter + 1;													// Go past delimiter
				}
				else {
					pTokenizer->isEnded = TRUE;																			// No more token
				}
			}
			else {
				pTokenizer->isEnded = TRUE;																				// no more token
			}
		}
		else {																															// If pQuote is NULL (end quote not found)
			pTokenizer->pToken = pTokenizer->current_pointer;													// The remaining will be treat as one token
			pTokenizer->isEnded = TRUE;
		}
	}
	// Last token is empty token
	else if (*(pTokenizer->current_pointer) == '\0') {																// Empty token
			pTokenizer->pToken = pTokenizer->current_pointer;;
			pTokenizer->isEnded = TRUE;
	}
	// Token not quoted
	else {																																// Normal token
		char* pDelimiter = strchr(pTokenizer->current_pointer, pTokenizer->delimiter);				// Find the next delimiter
		if (pDelimiter) {
			int length = pDelimiter - pTokenizer->current_pointer;
			//
			// Length could be 0
			pTokenizer->pToken = pTokenizer->current_pointer;													// Get token
			*(pTokenizer->pToken + length) = '\0';																		// NULL  terminated the token
			//
			pTokenizer->current_pointer = pDelimiter + 1;															// Go past delimiter
		}
		else {
			pTokenizer->pToken = pTokenizer->current_pointer;													// The remaining will be treated as one token
			pTokenizer->isEnded = TRUE;
		}
	}
	
	//
	pOutput = trim(pTokenizer->pToken);
	pTokenizer->pToken = pOutput;
	
	//
	return pOutput;
}


/*
Trims leading and trailing whitespace
This function changes the input string
*/
char* trim(char* pInput) {
	if (!pInput) {																													// Null input
		//
	}
	else {
		if (*pInput == '\0') {																									// Input empty string
			//
		}
		else {																															// Good input
			// Trim leading space
			while (isspace((unsigned char)*pInput)) {
				pInput++;
			}
			
			// All spaces: empty after triming leading space
			if (*pInput == '\0') {
				//
			}
			else {
				char *end;
				//
				// Trim trailing space
				end = pInput + strlen(pInput) - 1;
				//
				while (end > pInput && isspace((unsigned char)*end)) {
					end--;
				}
				//
				// Write new null terminator
				*(end+1) = 0;
			}
		}
	}
	//
	return pInput;
}