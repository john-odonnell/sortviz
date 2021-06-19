#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// quicksort
// first call: arr, size, 0, random, size
extern void quickSort(int* arr, int size, int left, int pivot, int subsize) {
    outputRecursive(arr, size, pivot, left, subsize);

    time_t t;

    if (subsize <= 1) {
        // base case
        // return subarrays of length 0 or 1
        outputRecursive(arr, size, left, left, subsize);
        return;
    } else {

        int pivot_value = arr[pivot];

        // sort around pivot and place
        int _left = left;
        int _right = left + subsize - 1;

        int placeholder;
        while (_right > _left) {
            // move left value until larger than pivot
            while (_left <= _right && arr[_left] <= pivot_value) {
                _left++;
                outputRecursive(arr, size, pivot, left, subsize);
            }
            // move right value until larger than pivot
            while (_left < _right && arr[_right] > pivot_value) {
                _right--;
                outputRecursive(arr, size, pivot, left, subsize);
            }
            if (_left < _right) {

                // swap left and right values
                placeholder = arr[_left];
                arr[_left] = arr[_right];
                arr[_right] = placeholder;

                // if the pivot was swapped, update pivot position
                if (_left == pivot) {
                    pivot = _right;
                } else if (_right == pivot) {
                    pivot = _left;
                }
                outputRecursive(arr, size, pivot, left, subsize);
            }
        }
        outputRecursive(arr, size, pivot, left, subsize);

        // swap pivot 
        placeholder = arr[pivot];
        arr[pivot] = arr[_left -1];
        arr[_left -1] = placeholder;

        int sorted = _left -1;

        outputRecursive(arr, size, sorted, left, subsize);

        // calculate markers for next recursive call
        int left_left = left;
        int right_left = sorted + 1;

        int left_sub = sorted - left;
        int right_sub = subsize - left_sub - 1;

        // generate two new pivots
        // one between sorted+1 and (left + subsize - 1)
        srand((unsigned) time(&t));
        int left_pivot = 0;
        int right_pivot = 0;
        if (left_sub > 0) {
            left_pivot = (rand() % (sorted - left)) + left;
        }
        if (right_sub > 0) {
            right_pivot = (rand() % ((left + subsize - 1) - (sorted + 1) + 1)) + (sorted + 1);
        }

        // call quicksort on left and right of pivot
        quickSort(arr, size, left_left, left_pivot, left_sub);
        quickSort(arr, size, right_left, right_pivot, right_sub);
        outputRecursive(arr, size, sorted, left, subsize);

    }
    return;
}
