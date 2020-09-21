/* Defines Graphics Methods
 */

#ifndef GRAPHICS_INCLUDED
#define GRAPHICS_INCLUDED

#include <stdbool.h>

// sdl graphics function
extern bool init();
extern void close();
extern void outputRender(int* arr, int size, int comp);
extern void outputRecursive(int* arr, int size, int comp, int left, int subsize);

// graphics globals getter functions
extern int getScreenWidth();
extern int getScreenHeight();
extern int getCellWidth();
extern int getCellHeight();

// graphics globals setter functions
extern void setCellWidth(int w);
extern void setCellHeight(int h);
extern void setOffset(int o);

#endif
