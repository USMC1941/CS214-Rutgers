#ifndef RECORD_H
#define RECORD_H


// Data for one movie record
// It holds one line in the csv file, and its sorting key, which could be long, float or string.
typedef struct Record {
	char* 		pSKey;						// Pointer to sorting key in recordData
	char*		pSKeyTerm;				// Pointer to terminating char of sorting key in recordData. It will be set to '\0' while processing. And reset back before output record to file
	char			chHold;						// Hold the char for *pSKeyTerm. Will be set back before output to file
	long 			lKey;							// integer number if sorted by number
	float			fKey;						// floating point number is sorted by float number
	//
	char 			recordData[1];			// String for one record. Define here as array of 1. More memory wiill be allocated to hold one line in csv. 
} Record;


/*
Create a record. Including abstract sorting key
Also detect what data type is the key: long, float or string
*/
Record* createRecord(char* buffer, SKeyIndex* pSKI);


/*
Compare keys of two records:
NULL will be treated the smallest and comes first
The key could be long, float, or string type
*/
int compare(void* pData1, void* pData2, void* pHint);


#endif
