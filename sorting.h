/* Defines Sorting Algorithm Methods
 */

#ifndef SORTING_INCLUDED
#define SORTING_INCLUDED

// print array for testing
void printArr(int* arr, int size);

// externally defined sorting algorithms
extern void bubbleSort(int* arr, int size);
// extern void heapSort(int* arr, int size);
extern void insertionSort(int* arr, int size);
extern void mergeSort(int* arr, int size, int left, int subsize);
extern void quickSort(int* arr, int size, int left, int pivot, int subsize);
// extern void shellSort(int* arr, int size);
extern void selectionSort(int* arr, int size);


#endif
