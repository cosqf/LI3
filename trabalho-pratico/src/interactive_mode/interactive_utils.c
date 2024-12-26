#include <ncurses.h>
#include <panel.h>
#include <interactive_utils.h>
#include <string.h>

int printWrapped (WINDOW* win, char* str, int posy, int posx) {
    int height, width;
    getmaxyx(win, height, width);
    (void) height;

    int maxWidth = width - 2* posx;
    int line = 0, index = 0;
    int size = strlen (str);
    while (index < size) {
        char temp[maxWidth + 1];      
        strncpy(temp, str + index, maxWidth);
        temp[maxWidth] = '\0';        

        mvwprintw(win, posy + line, posx, "%s", temp); 
        index += maxWidth;
        line++;                            
    }
    return line;
}

WINDOW* newWindowWithBorder (int height, int width, int posy, int pox){
    WINDOW* win = newwin(height, width, posy, pox);  
    refresh();
    box (win, 0, 0);
    wrefresh(win);
    return win;
}

void printHighlightedText (WINDOW* win, int y, int x, char* text, bool highlight) {
    if (highlight) wattron(win, A_REVERSE | A_BLINK);
    mvwprintw(win, y, x, "%s", text);
    if (highlight) wattroff(win, A_REVERSE | A_BLINK);
}
