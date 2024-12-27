#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>
#include <panel.h>

#include <interactive.h>
#include <interactive_queries.h>
#include <interactive_utils.h>
#include <validateDatatypes.h>

#include <query1.h>
#include <query2.h>
#include <query3.h>
#include <query4.h>

#define maxSize 60
char** readOutputFiles() {
    char path[] = "resultados/command1_output.txt";
    FILE* file = fopen(path, "r");
    if (file == NULL) return NULL;

    char** results = malloc(15 * sizeof(char*)); // max number of lines a query can output
    if (mallocErrorCheck (results)) {
        fclose(file);
        return NULL;
    }
    int i = 0;
    char buffer[100]; 

    while (fgets(buffer, sizeof(buffer), file) != NULL && i < 15) {
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
    // terminate the array
    results[i] = NULL;

    return results;
}

int getNumberFromInput (WINDOW* win, int posy, int posx, char* numberS, int digits, int minVal, int maxVal, int flag) { // flag: reading ids ("A0000")
    int widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);

    int number;
    mvprintw (heightS-1, 1, "Type \"exit\" to leave");
    refresh();
    curs_set(1);

    while (true) {
        wmove(win, posy, posx);
        wgetnstr(win, numberS, digits);

        if (strcmp(numberS, "exit") == 0 || 
            (digits == 2 && strcmp(numberS, "ex") == 0)) {
            curs_set(0);
            return -1;
        }
        int check = 0;
        char* numberString = numberS;
        if (flag == 1) {
            if (numberS[0] == 'A' || numberS[0] == 'U') check = 1;
            numberString ++;
        }
        int convertSuccess = convertToInt (numberString, &number);
        if (convertSuccess && number >= minVal && number <= maxVal && (!flag || check)) break;
        else {
            attron (A_UNDERLINE);
            mvprintw (heightS/5 + 1, widthS /2 - 12, "Invalid input, try again");
            attroff (A_UNDERLINE);
            refresh();
            mvwprintw(win, posy, posx, "         ");
            wrefresh(win);
            int size = sizeof (numberS);
            memset(numberS, 0, size);
        }
    }
    curs_set(0);
    return number;
}

void readResults (WINDOW* win) {
    int widthS, heightS, widthW, heightW;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(win, heightW, widthW);
    (void) heightW;
    char** results = readOutputFiles ();
    for (int i = 0, j = 0; results[i]; i++, j++) {
        int lines = printWrapped (win, results[i], j + 1, (int)(widthW / 11));
        j += lines - 1;
    }

    attron (A_BLINK);
    mvprintw (heightS-1, widthS -25, "Press any key to leave");
    attroff(A_BLINK);
    wrefresh(win);
    getch();
    free (results);
}

char* getStringFromInput (WINDOW* win, char* string, int digits) {
    curs_set(1);
    wgetnstr(win, string, digits);
    curs_set(0);
    return string;
}

int loadQ1 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);

    mvprintw (heightS/5, widthS /2 - 9, "Input the user ID"); 
    refresh();
    char idString [10];
    int id = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 8), idString, 9, 0, 9999999, 1);
    if (id == -1) return -1;

    //creation of cmd
    CMD* cmd = createEmptyCMD ();
    setCMDQuery (cmd, 1);
    setCMDEntity (cmd, idString[0]);
    setCMDId (cmd, id);

    query1 (cmd, mngr, 1);
    readResults (outWin);

    freeCmd (cmd);
    return 0;
}


int loadQ2 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);
    int num;
    char string[10];
    while (true){
        mvprintw ((int) heightS/5, (int) (widthS /2) - 21, "Input the number of artists; the max is 10"); 
        refresh();
        num = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 8), string, 9, 0, 9999999, 0);
        if (num == -1) return -1;
        if (num >10) {
            mvprintw ((int) (heightS/5) + 1, (int) (widthS /2) - 13, "The number must be smaller than 10");
            refresh();
        }
        else break;
    }

    // clearing the messages
    move ((int) heightS/5, (int) (widthS /2) - 21);
    clrtoeol ();
    move ((int) (heightS/5) + 1, (int) (widthS /2) - 12);
    clrtoeol ();

    
    mvprintw ((int) (heightS/5), (int) (widthS /2) - 14, "Input the country filter"); 
    mvprintw ((int) (heightS/5) +1, (int) (widthS/2) -18, "To have no filter, just hit \"Enter\"");
    refresh();
    wmove (inWin, (int)(heightW1 / 2), (int)(widthW1 / 4));
    char country[maxSize];
    getStringFromInput (inWin, country, maxSize-1);
    mvprintw (heightS, widthS, "%s", country);

    // creation of cmd
    CMD* cmd = createEmptyCMD ();
    setCMDQuery (cmd, 2);
    setCMDTopN (cmd, num);
    if (country[0] != '\0') setCMDCountry (cmd, country);

    query2 (cmd, mngr, 1);
    readResults (outWin);

    freeCmd (cmd);
    return 0;
}

int loadQ3 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);

    char minAgeS[10], maxAgeS[10];
    int minAge, maxAge;
    while (true) {
        mvprintw ((int) (heightS/5),(int) (widthS / 2) - 11, "Input the minimum age"); 
        refresh();
        minAge = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 4), minAgeS, 3, 0, 200, 0);
        if (minAge == -1) return -1;

        mvprintw ((int) (heightS/5),(int) (widthS / 2) - 11, "Input the maximum age"); 
        refresh();
        maxAge = getNumberFromInput (inWin,(int)(heightW1 / 2), (int)(widthW1 *3 / 4), maxAgeS, 3, 0, 200, 0);
        if (maxAge == -1) return -1;

        if (maxAge >= minAge) break;
        memset (minAgeS, 0, sizeof (minAgeS));
        memset (maxAgeS, 0, sizeof (maxAgeS));
        mvwprintw(inWin, (int)(heightW1 / 2), (int)(widthW1 / 4), "         ");
        mvwprintw(inWin, (int)(heightW1 / 2), (int)(widthW1 *3 / 4), "         ");
        mvprintw (heightS/5 + 1, widthS /2 - 13, "Invalid input, try again");
        wrefresh(inWin);
    }
    
    // creation of cmd
    CMD* cmd = createEmptyCMD ();
    setCMDQuery (cmd, 3);
    setCMDAgeMin (cmd, minAge);
    setCMDAgeMax (cmd, maxAge);

    UserManager* u_mngr = getUserManager (mngr);
    MusicManager* m_mngr = getMusicManager (mngr);

    query3 (cmd, u_mngr, m_mngr, 1);
    readResults (outWin);

    freeCmd (cmd);
    return 0;
}

int loadQ4 (WINDOW* inWin, WINDOW* outWin, hashtableManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);
    
    bool flag = false; // filter
    while (true) {
        printHighlightedText(stdscr, (int) (heightS / 2), (int) (widthS / 2) - 7, "Input filter", !flag);
        printHighlightedText(stdscr, (int) (heightS * 2 / 3), (int) (widthS / 2) - 5, "No filter", flag);
        refresh();  
        int key = getch ();
        if (key == KEY_UP || key == KEY_DOWN) flag = ! flag;
        else if (key == 10 || key == KEY_RIGHT) {
            mvprintw ((int) (heightS / 2), (int) (widthS / 2) - 7, "            "); 
            mvprintw ((int) (heightS * 2 / 3), (int) (widthS / 2) - 5, "            "); 
            refresh();
            break;
        }
    }
    char minDateS[12], maxDateS[12];
    Date min, max;
    while (!flag) {
        mvwprintw (inWin,(int)(heightW1 / 2), (int)(widthW1 / 4) -5, "                         ");
        mvwprintw (inWin,(int)(heightW1 / 2), (int)(widthW1 / 4) -5, "YYYY/MM/DD");
        mvwprintw (inWin, (int)(heightW1 / 2), (int)(widthW1 *3 / 4) -5, "YYYY/MM/DD");
        wrefresh(inWin);

        mvprintw ((int) (heightS/5),(int) (widthS / 2) - 22, "Input the minimum date following the format"); 
        refresh();
        wmove (inWin, (int)(heightW1 / 2), (int)(widthW1 / 4 - 5));
        getStringFromInput (inWin, minDateS, 10);
        if (strcmp (minDateS, "exit") == 0) return -1;

        mvprintw ((int) (heightS/5),(int) (widthS / 2) - 22, "Input the maximum date following the format"); 
        refresh();
        wmove (inWin, (int)(heightW1 / 2), (int)(widthW1 *3 / 4 - 5));
        getStringFromInput (inWin, maxDateS, 10);
        if (strcmp (maxDateS, "exit") == 0) return -1;
        
        if (validBirthdate (minDateS) && validBirthdate (maxDateS)) {
            min = parseDate (minDateS);
            max = parseDate (maxDateS);
            if (compareDate (max, min) > 0) break;
            } 
        attron (A_UNDERLINE);
        mvprintw (heightS/5 + 1, widthS /2 - 13, "Invalid input, try again");
        attroff (A_UNDERLINE);
        refresh();
    }

    // creation of cmd
    CMD* cmd = createEmptyCMD ();
    setCMDQuery (cmd, 4);
    if (!flag) {
        setCMDDateMin (cmd, min);
        setCMDDateMax (cmd, max);
    }
    HistoryManager* h_mngr = getHistoryManager (mngr);
    MusicManager* m_mngr = getMusicManager (mngr);
    ArtistManager* a_mngr = getArtistManager (mngr);

    query4 (cmd, h_mngr, m_mngr, a_mngr, 1);

    readResults (outWin);
    freeCmd (cmd);
    return 0;
}