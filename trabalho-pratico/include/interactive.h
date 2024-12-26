#include <ncurses.h>
#include <panel.h>
#include <utils.h>
#include <parsing.h>

#ifndef _INTERACTIVE_H_
#define _INTERACTIVE_H_

int loadMainPage ();

int gettingData (WINDOW* win, hashtableManager* mngr);

int gettingQuery (WINDOW* win);

#endif