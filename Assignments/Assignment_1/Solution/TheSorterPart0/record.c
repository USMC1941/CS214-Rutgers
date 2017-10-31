#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "sortingkey.h"
#include "record.h"
#include "tokenizer.h"
#include "helper.h"


/*
Create a record. Including abstract sorting key
Also detect what data type is the key: long, float or string
*/
Record* createRecord(char* buffer, SKeyIndex* pSKI) {
	Record* pRec = NULL;
	
	// Create the record
	if (buffer == NULL || *buffer == '\0' || pSKI==NULL) {
		// No input or empty input
	}
	else {
		// Create a new Record
		pRec = (Record*)malloc(sizeof(Record) + strlen(buffer));				// recordData[1] is declared one byte. strlen(buffer) additional bytes are allocated to hold the string
		
		if (pRec) {
			strcpy(pRec->recordData, buffer);												// Make a copy of the line
		}
		else {
			// Could not allocate memory to Record
		}
	}
	//
	// Find sorting key
	if (pRec != NULL) {
		Tokenizer tokenizer;
		initTokenizer(&tokenizer, buffer, DELIMITER, DBLQUOTE);
			
		char* bufferStart = buffer;																// Pointer buffer will move along the string. Remember the start here.
		char* pToken;
		
		pToken = getNextToken(&tokenizer);
		int index = 0;
		//
		while(pSKI->index > index) {														// Go to (pSKI->index)th field, which is the sorting key
			// Key and token are not equal. Continue loop
			pToken = getNextToken(&tokenizer);
			index++;
		}
		//
		int offset;																						// Offset of the key in line
		int length;																						// Length of the key
		if (pToken == NULL) {																	// No token matched. The field is NULL
			offset = strlen(pRec->recordData);												// Point to terminate char: '\0'
			length = 0;
		}
		else {
			offset = pToken - bufferStart;
			length = strlen(pToken);
		}
		//
		pRec->pSKey 			= pRec->recordData + offset;
		pRec->pSKeyTerm 	= pRec->recordData + offset + length;
		pRec->chHold 			= *pRec->pSKeyTerm;									// Remember the char at  pRec->pSKeyTerm (to be reset later)
		*pRec->pSKeyTerm 	= '\0';															// Set pRec->pSKeyTerm to null. Now pRec->pSKey is a proper string
		//
		pRec->lKey = 0L;																			// Try to convert to long
		pRec->fKey = 0.0f;																		// Try to convert to float
		char	cTemp;
		if (length > 0) {
			char* pDot = strchr(pRec->pSKey, DOT);									// Check if "." in the key
			//
			// Determine what data type it is
			// Initially assume is INDEX_TYPE_INTEGER
			// Change to INDEX_TYPE_FLOAT if encounter float number which is not INDEX_TYPE_INTEGER.
			// Change to INDEX_TYPE_STRING if encounter non-number data.
			if (pSKI->idxType == INDEX_TYPE_INTEGER) {
				if (!pDot && sscanf(pRec->pSKey, "%ld%c", &(pRec->lKey), &cTemp) == 1) {				// integer number
					pRec->fKey = pRec->lKey;
				}
				else if (pDot && sscanf(pRec->pSKey, "%f%c", &(pRec->fKey), &cTemp) == 1) {			// float number
					pSKI->idxType = INDEX_TYPE_FLOAT;																	// set the data type to INDEX_TYPE_FLOAT as there is at least one float number
				}
				else {
					pSKI->idxType = INDEX_TYPE_STRING;																	// set the data type to INDEX_TYPE_STRING as there is at least one non-number
				}
			}
			else if (pSKI->idxType == INDEX_TYPE_FLOAT) {
				if (!pDot && sscanf(pRec->pSKey, "%ld%c", &(pRec->lKey), &cTemp) == 1) {
					pRec->fKey = pRec->lKey;
				}
				else if (pDot && sscanf(pRec->pSKey, "%f%c", &(pRec->fKey), &cTemp) == 1) {
					//
				}
				else {
					pSKI->idxType = INDEX_TYPE_STRING;
				}
			}
			else {
				// INDEX_TYPE_STRING
			}
		}
	}
	//
	return pRec;
}


/*
Compare keys of two records:
NULL will come first
The key could be long, float, or string type
*/
int compare(void* pData1, void* pData2, void* pHint) {
	//
	Record* pRecord1 = (Record*)pData1;
	Record* pRecord2 = (Record*)pData2;
	//
	int outcome;
	
	SKeyIndex* pSKI = (SKeyIndex*)pHint;
	int idxType = pSKI->idxType;
	//
	int len1 = strlen(pRecord1->pSKey);
	int len2 = strlen(pRecord2->pSKey);
	//
	// If at least one key is NULL 
	if (len1 == 0 && len2 > 0) {																	// First one NULL
		outcome = -1;
	} 
	else if (len1 > 0 && len2 == 0) {															// Second one NULL
		outcome = 1;
	}
	else if (len1 == 0 && len2 == 0) {															// Both NULLs
		outcome = 0;
	}
	else {																									// Neither NULL
		long 	ldelta;
		float fdelta;
		//
		switch(idxType) {
			case INDEX_TYPE_INTEGER:
				ldelta = pRecord1->lKey - pRecord2->lKey;
				if (ldelta == 0L) {
					outcome = 0;
				}
				else if (ldelta > 0L) {
					outcome = 1;
				}
				else {
					outcome = -1;
				}
				break;
			
			case INDEX_TYPE_FLOAT :
				fdelta = pRecord1->fKey - pRecord2->fKey;
				if (fdelta == 0.0) {
					outcome = 0;
				}
				else if (fdelta > 0.0) {
					outcome = 1;
				}
				else {
					outcome = -1;
				}
				break;
		  
		   default : // INDEX_TYPE_STRING
				outcome = strcicmp(pRecord1->pSKey, pRecord2->pSKey);			// Not case sensitive
				break;
		}
	}
	//
	return outcome;
}