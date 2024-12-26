#include <ncurses.h>
#include <panel.h>

#ifndef _INTERACTIVE_QUERIES_H_
#define _INTERACTIVE_QUERIES_H_

int loadQ1 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr);

int loadQ2 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr);

int loadQ3 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr);

int loadQ4 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr);

#endif