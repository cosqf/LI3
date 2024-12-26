#include <ncurses.h>
#include <panel.h>

#ifndef _INTERACTIVE_UTILS_H_
#define _INTERACTIVE_UTILS_H_

WINDOW* newWindowWithBorder (int height, int width, int posy, int pox);

void printHighlightedText (WINDOW* win, int y, int x, char* text, bool highlight);

int printWrapped (WINDOW* win, char* str, int posy, int posx);

#endif