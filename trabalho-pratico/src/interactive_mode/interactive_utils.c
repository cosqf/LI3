#include <ncurses.h>
#include <panel.h>
#include <interactive_utils.h>
#include <string.h>
#include <stdlib.h>
#include <utils.h>
#include <unistd.h>

int getNumberFromInput (WINDOW* win, int posy, int posx, int digits, int minVal, int maxVal) {
    int widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);

    char numberS[digits+1];
    int number;
    mvprintw (heightS-1, 1, "Type \"exit\" to leave");
    refresh();
    curs_set(1);

    while (true) {
        wmove(win, posy, posx);
        wgetnstr(win, numberS, digits);

        if (strcmp(numberS, "exit") == 0 || 
            (digits == 2 && strcmp(numberS, "ex") == 0)||
            (digits == 3 && strcmp (numberS, "exi") == 0)) {
            curs_set(0);
            return -1;
        }
        char* numberString = numberS;
        int convertSuccess = convertToInt (numberString, &number);
        if (convertSuccess && number >= minVal && number <= maxVal) break;
        else {
            attron (A_UNDERLINE);
            mvprintw (heightS/5 - 1, widthS /2 - 12, "Invalid input, try again");
            attroff (A_UNDERLINE);
            refresh();
            for (int i = 0; i < digits; i++) mvwaddch(win, posy, posx + i, ' '); // cleanup
            wrefresh(win);
            int size = sizeof (numberS);
            memset(numberS, 0, size);
        }
    }
    curs_set(0);
    return number;
}

void getStringFromInput (WINDOW* win, int posy, int posx, char* string, int digits) {
    int widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);
    (void) widthS;
    mvprintw (heightS-1, 1, "Type \"exit\" to leave");
    refresh();

    wmove (win, posy, posx);
    curs_set(1);
    wgetnstr(win, string, digits);
    curs_set(0);
}

int getIdFromInput (WINDOW* win, int posy, int posx, char* idString, int flag) { // flag == 0 : just users, flag == 1 : users and artists
    int widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);

    int id = 0;
    while (true) {
        getStringFromInput (win, posy, posx, idString, 8);
        if(strcmp (idString, "exit") == 0) return -1;
        if (convertToInt(idString + 1, &id)) {
            if ((flag == 0 && idString[0] == 'U') ||                      /**< Flag 0: Allows 'U' */
                (flag == 1 && (idString[0] == 'U' || idString[0] == 'A')))  /**< Flag 1: Allows 'U' and 'A' */ 
                break;
        }
        int size = sizeof (idString);
        memset (idString, 0, size);
        attron (A_UNDERLINE);
        mvprintw (heightS/5 - 1, widthS /2 - 12, "Invalid input, try again");
        attroff (A_UNDERLINE);
        for (int i = 0; i < 8; i++) mvwaddch(win, posy, posx + i, ' '); // cleanup
        wrefresh(win);
        refresh();
    }
    return id;
}

char** readOutputFiles() {
    char path[] = "resultados/command1_output.txt";
    FILE* file = fopen(path, "r");
    if (file == NULL) return NULL;

    char** results = malloc(maxSize * sizeof(char*)); // max number of lines a query can output
    if (mallocErrorCheck (results)) {
        fclose(file);
        return NULL;
    }
    int i = 0;
    char buffer[DEFAULT]; 

    while (fgets(buffer, sizeof(buffer), file) != NULL && i < maxSize) {
        buffer[strcspn(buffer, "\n")] = '\0';

        results[i] = strdup(buffer); 
        if (!results[i]) { 
            for (int j = 0; j < i; j++) {
                free(results[j]);
            }
            free(results);
            fclose(file);
            return NULL;
        }
        i++;
    }
    results[i] = NULL;

    return results;
}

void printResults (WINDOW* win) {
    int widthS, heightS, widthW, heightW;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(win, heightW, widthW);
    (void) heightW;
    char** results = readOutputFiles ();
    if (results[0][0] == '\0') mvwprintw (win, heightW/3, widthW/2 - 5, "No output.");
    else for (int i = 0, j = 0; results[i]; i++, j++) {
            int lines = printWrapped (win, results[i], j + 1, (int)(widthW / 11));
            j += lines - 1;
        }

    attron (A_BLINK);
    mvprintw (heightS-1, widthS -25, "Press any key to return");
    attroff(A_BLINK);
    wrefresh(win);
    getch();
    for (int i = 0; results[i]; i++) free (results[i]);
    free (results);
}

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

int countLines (int width, char* str, int posx) {
    int maxWidth = width - 2* posx;
    int line = 0, index = 0;
    int size = strlen (str);
    while (index < size) {
        index += maxWidth;
        line ++;                  
    }
    return line;
}

void printHighlightedText (WINDOW* win, int y, int x, char* text, bool highlight) {
    if (highlight) wattron(win, A_REVERSE | A_BLINK);
    mvwprintw(win, y, x, "%s", text);
    if (highlight) wattroff(win, A_REVERSE | A_BLINK);
}

void readResultsScrollable(int height, int width, int posy, int posx) {
    int heightS, widthS;
    getmaxyx (stdscr, heightS, widthS);
    (void) widthS;

    char** results = readOutputFiles ();
    if (!results || results[0][0] == '\0') {
        mvprintw(posy, posx+1, "No results available.");
        mvprintw(posy+1, posx+1, "Press any key to leave.");
        refresh();
        getch();
        return;
    }
    int i, j;
    for (i = 0, j = 0; results[i]; i++) {
        int lines = countLines (width, results[i], (int)(width / 11)); //getting the number of lines;
        j += lines+1; // assuming one space in between every line
    }
    int maxRow = j; // total rows required

    WINDOW* pad = newpad(maxRow, width);
    if (!pad) {
        mvprintw(posy, posx, "Failed to create pad.");
        refresh();
        getch ();
        return;
    }

    for (i = 0, j = 0; results[i]; i++) {
        int lines = printWrapped (pad, results[i], j, (int)(width/ 11)); //printing
        j += lines +1;
    }
    mvprintw(heightS - 1, 0, "Use UP/DOWN arrow keys to scroll. Press 'Esc' to quit.");
    refresh();

    int firstRow = 0; 
    int visibleRows = height-1;
    int visibleCols = width-1;

    prefresh(pad, firstRow, 0, posy, posx, posy + visibleRows - 1, posx + visibleCols - 1);
    int ch;
    while ((ch = getch()) != 27) { // 'Esc' key
        switch (ch) {
            case KEY_UP:
                if (firstRow > 0) firstRow--;
                break;
            case KEY_DOWN:
                if (firstRow < maxRow - visibleRows +1) firstRow++;
                break;
        }
        //prefresh (pad pminrow pmincol sminrow simincol smaxrow smaxcol)
        //pminrow and pmincol specify the upper left-hand corner of the rectangle to be displayed in the pad. 
        //sminrow, smincol, smaxrow, and smaxcol specify the edges of the rectangle to be displayed on the screen. 
        prefresh(pad, firstRow, 0, posy, posx, posy + visibleRows -1, posx + visibleCols -1);
    }
    delwin(pad);
    for (i = 0; results[i]; i++) free(results[i]);
    free(results);
}

WINDOW* newWindowWithBorder (int height, int width, int posy, int pox){
    WINDOW* win = newwin(height, width, posy, pox);  
    refresh();
    box (win, 0, 0);
    wrefresh(win);
    return win;
}

void loadDotAnimation () {
    int x, y, widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);

    int nextX = 0;
    int direction = 1;
    x = 0;
    y = 0;
    int delayTime = 2000000 / (heightS * (widthS + 3)); // takes 2 sec
    while(true){
        if (y == heightS) break;
        mvprintw(y , x, ".");
        refresh();

        usleep(delayTime);

        nextX = x + direction;
        if(nextX >= widthS || nextX < 0){
            direction*= -1;
            y++;
        }
        else x += direction;
        if (y == heightS) break;
    }
}