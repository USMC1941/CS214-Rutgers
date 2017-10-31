#ifndef MERGESORT_H
#define MERGESORT_H


/*
Pointer type to function that compares two items
*/
typedef int (*PFUNC_COMPARE_DATA)(void* pData1, void* pData2, void* pHint);


/*
 Merges two subarrays of arr[].
 First subarray is arr[l..m]
 Second subarray is arr[m+1..r]
*/
void merge(void* arr[], int l, int m, int r, void* pHint, PFUNC_COMPARE_DATA pFuncCompare);


/*
Sorts the array

l is for left index and r is right index of the sub-array of arr to be sorted 
*/
void mergeSort(void* arr[], int l, int r, void* pHint, PFUNC_COMPARE_DATA pFuncCompare);


#endif