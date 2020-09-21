/* Personal Collection of Sorting Algorithm Implementations
 * 
 * Includes:
 *      Selection   Bubble  Merge   Heap
 *      Insertion   Quick   Shell   
 * 
 * I plan on eventually creating an algorithm visualizor
 * using either Qt or a JS webapp
 * 
 * Usage:
 * 
 *  1. Build:   ./build
 *  2. Run:     ./sort <type : string> <size : int>
 * 
 *      type options: sl, in, bl, mg, qk, hp, sh
 *      size        : integer greater than two
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "sorting.h"
#include "graphics.h"

char* SORT_TYPES[7] = {"bl", "hp", "in", "mg", "qk", "sh", "sl"};

// main function
// parse execution arguments and execute call to sorting function
int main(int argc, char* argv[]) {
    
    // check correct usage
    if (argc != 3) {
        printf("Usage:  ./sort <type> <size>\n");
        printf("Sorting Types :\n");
        printf(" => bl : Bubble sort\n");
        // printf(" => hp : Heap sort\n");
        printf(" => in : Insertion sort\n");
        printf(" => mg : Merge sort\n");
        // printf(" => qk : Quicksort\n");
        // printf(" => sh : Shell sort\n");
        printf(" => sl : Selection sort\n");
        return 1;
    }
    // check acceptable array size range 
    int size = atoi(argv[2]);
    if (size < 2) {
        printf("Given size must be greater than 2.\n");
        printf("Usage:  ./sort <type> <size>\n");
        return 1;
    }
    // check acceptable sorting type
    char* sortType = argv[1];
    bool accepted = false;
    int type = 0;
    while (type < 7 && !accepted) {
        if (strcmp(SORT_TYPES[type], sortType) == 0) {
            accepted = true;
        }
        type++;
    }
    if (!accepted) {
        printf("Invalid Sorting Type.\n");
        printf(" => bl : Bubble sort\n");
        // printf(" => hp : Heap sort\n");
        printf(" => in : Insertion sort\n");
        printf(" => mg : Merge sort\n");
        // printf(" => qk : Quicksort\n");
        // printf(" => sh : Shell sort\n");
        printf(" => sl : Selection sort\n");
        return 1;
    }
    


    // generate random array
    // fills an array with random numbers from 1 to 2*SIZE
    // might be better to generate an array from 1 to SIZE and then scramble
    int* arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        int num =  1 + rand() / ( RAND_MAX / ((size) - 1 + 1) + 1);
        arr[i] = num;
    }

    // set dimensions for rendered units
    setCellWidth(getScreenWidth() / size);
    setCellHeight(getScreenHeight() / (size));
    setOffset((getScreenWidth() - (getCellWidth() * size)) / 2); 

    // initialize sdl2 graphics
    init();

    // draw unsorted array
    outputRender(arr, size, -1);

    // sdl event loop
    // starts the given sorting algorithm upon keypress
    bool quit = false;
    bool done = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN && done == false) {
                if (strcmp(sortType, "bl") == 0) {
                    bubbleSort(arr, size);
                } else if (strcmp(sortType, "in") == 0) {
                    insertionSort(arr, size);
                } else if (strcmp(sortType, "mg") == 0) {
                    mergeSort(arr, size, 0, size);
                } else if (strcmp(sortType, "sl") == 0) {
                    selectionSort(arr, size);
                }
                
                done = true;
            }
        }
    }

    // close sdl2 subprocesses and free array memory
    close();
    free((void*)arr);

    return 0;
}
