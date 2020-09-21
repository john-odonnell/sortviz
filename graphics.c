/* Implements Graphics functions
 * 
 * Uses SDL2 library for graphics and event handling
 */

#include <stdbool.h>
#include <SDL2/SDL.h>

// initialize global variables
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
int CELL_WIDTH;
int CELL_HEIGHT;
int X_OFFSET;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// getter functions for global variables
extern int getScreenWidth()  { return SCREEN_WIDTH;  }
extern int getScreenHeight() { return SCREEN_HEIGHT; }
extern int getCellWidth()    { return CELL_WIDTH;    }
extern int getCellHeight()   { return CELL_HEIGHT;   }

// setter functions for non-const globals
extern void setCellWidth(int w)  { CELL_WIDTH  = w; return; }
extern void setCellHeight(int h) { CELL_HEIGHT = h; return; }
extern void setOffset(int o)     { X_OFFSET    = o; return; }

//initialize sdl2 graphics
extern bool init() {
    // init flag
    bool success = true;

    // init sld2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize. SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // create window
        window = SDL_CreateWindow("Sorting Suite", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // get window renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        }
    }

    // return success flag
    return success;
}

// close the sdl window
extern void close() {
    // destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();

    return;
}

// render the current iteration of the array, highlighting the
// value currently in use
extern void outputRender(int* arr, int size, int comp) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < size; i++) {
        SDL_Rect rect;
        rect.x = (i * CELL_WIDTH) + X_OFFSET;
        rect.y = SCREEN_HEIGHT - (arr[i] * CELL_HEIGHT);
        rect.h = CELL_HEIGHT * arr[i];
        rect.w = CELL_WIDTH;

        if (i == comp) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        } else {
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
    return;
}

// render the current iteration of the array
// highlight recursive subarray in question
extern void outputRecursive(int* arr, int size, int comp, int left, int subsize) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < size; i++) {
        SDL_Rect rect;
        rect.x = (i * CELL_WIDTH) + X_OFFSET;
        rect.y = SCREEN_HEIGHT - (arr[i] * CELL_HEIGHT);
        rect.h = CELL_HEIGHT * arr[i];
        rect.w = CELL_WIDTH;

        if (i == comp) {
            SDL_SetRenderDrawColor(renderer, 255, 65, 77, 255);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        } else if (i >= left && i < left+subsize) {
            SDL_SetRenderDrawColor(renderer, 217, 236, 242, 255);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        } else {
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
    return;
}
