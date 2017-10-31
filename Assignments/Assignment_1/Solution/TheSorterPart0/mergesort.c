#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "sortingkey.h"
#include "record.h"
#include "mergesort.h"


/*
 Merges two subarrays of arr[].
 First subarray is arr[l..m]
 Second subarray is arr[m+1..r]
*/
void merge(void* arr[], int l, int m, int r, void* pHint, PFUNC_COMPARE_DATA pFuncCompare) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
	
    // Create Temp Arrays
    void* tempArr1[n1];
	void* tempArr2[n2];
	
    // Copy data to temp arrays tempArr1[] and tempArr2[]
    for (i = 0; i < n1; i++) {
		tempArr1[i] = arr[l + i];
	}
	
    for (j = 0; j < n2; j++) {
        tempArr2[j] = arr[m + 1+ j];
	}
	
    // Merge the temp arrays back into arr[l..r]
    i = 0; 																// Initial index of first subarray
    j = 0; 																// Initial index of second subarray
    k = l;																// Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (pFuncCompare(tempArr1[i], tempArr2[j], pHint) <= 0 ) {
            arr[k] = tempArr1[i];
            i++;
        } 
		else {
            arr[k] = tempArr2[j];
            j++;
        }
        k++;
    }
	
    // Copy the remaining elements of tempArr1[], if there are any
    while (i < n1) {
        arr[k] = tempArr1[i];
        i++;
        k++;
    }
	
	// Copy the remaining elements of tempArr2[], if there are any 
    while (j < n2) {
		arr[k] = tempArr2[j];
        j++;
        k++;
    }
}


/*
Sorts the array
l is for left index and r is right index of the sub-array of arr to be sorted 
*/
void mergeSort(void* arr[], int l, int r, void* pHint, PFUNC_COMPARE_DATA pFuncCompare) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and h
        int m = l + (r - l) / 2;
		
        // Sort first and second halves
        mergeSort(arr, l, m, pHint, pFuncCompare);
        mergeSort(arr, m + 1, r, pHint, pFuncCompare);
		
        merge(arr, l, m, r, pHint, pFuncCompare);
    }
}