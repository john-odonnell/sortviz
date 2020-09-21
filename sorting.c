#include <stdio.h>

#include "sorting.h"
#include "graphics.h"

// printing function for terminal testing
void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// bubble sort
extern void bubbleSort(int* arr, int size) {
    int placeholder;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                placeholder = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = placeholder;
            }
            outputRender(arr, size, j);
        }
    }
    return;
}

// insertion sort
extern void insertionSort(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        int comp = arr[i];
        int j = i-1;
        while (j >= 0 && comp < arr[j]) {
            arr[j+1] = arr[j];
            j--;
            outputRender(arr, size, j);
        }
        arr[j+1] = comp;
        outputRender(arr, size, j+1);
    }
    return;
}

// selection sort
extern void selectionSort(int* arr, int size) {
    int smallest;
    int idxSmall;
    for (int i = 0; i < size-1; i++) {
        idxSmall = i;
        for (int j = i+1; j < size; j++) {
            if (arr[j] < arr[idxSmall]) {
                idxSmall = j;
            }
            outputRender(arr, size, j);
        }
        smallest = arr[idxSmall];
        arr[idxSmall] = arr[i];
        arr[i] = smallest;
        outputRender(arr, size, i);
    }
    return;
}

// in place merge sort
// first call: arr, size, 0, size
extern void mergeSort(int* arr, int size, int left, int subsize) {
    outputRecursive(arr, size, left, left, subsize);

    if (subsize <= 1) {
        // base case
        // return subarrays of sublength 1
        return;
    } else {
        int mid = left + (subsize/2);
        
        // call recursion on subarrays still contained in the main array
        mergeSort(arr, size, left, mid-left);
        mergeSort(arr, size, mid, subsize-(mid-left));
        
        // idxs for left and right array comp
        int L = left;
        int R = mid;
        
        // merge left and right subarrays in place
        int placeholder;
        while (L != R && R < left+subsize) {
            outputRecursive(arr, size, L, left, subsize);

            if (arr[L] <= arr[R]) {
                L++;
            } else if (arr[R] < arr[L]) {
                placeholder = arr[R];
                for (int j = R-1; j >= L; j--) {
                    arr[j+1] = arr[j];
                }
                arr[L] = placeholder;
                L++;
                R++;
            }
            outputRecursive(arr, size, L, left, subsize);
        }
        outputRecursive(arr, size, left, left, subsize);

    }
    outputRecursive(arr, size, left, left, subsize);

    return;
}
