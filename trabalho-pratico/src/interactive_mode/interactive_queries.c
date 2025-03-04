#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>
#include <panel.h>

#include <interactive.h>
#include <interactive_queries.h>
#include <interactive_utils.h>
#include <validateDatatypes.h>
#include <almightyManager.h>

#include <query1.h>
#include <query2.h>
#include <query3.h>
#include <query4.h>
#include <query5.h>
#include <query6.h>

int loadQ1 (WINDOW* inWin, WINDOW* outWin, AlmightyManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);

    mvprintw ((int) (heightS/5)-2, (int) (widthS /2) - 14, "Input the artist or user ID"); 
    refresh();
    char idString[9];
    int id = getIdFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 8), idString, 1);
    if (id == -1) return -1;

    move ((int) (heightS/5)-2, 0);
    clrtoeol ();

    //creation of cmd
    CMD* cmd = createEmptyCMD ();
    setCMDQuery (cmd, 1);
    setCMDEntity (cmd, idString[0]);
    setCMDId (cmd, id);

    query1 (cmd, mngr, 1);
    printResults (outWin);

    freeCmd (cmd);
    return 0;
}


int loadQ2 (WINDOW* inWin, AlmightyManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);
    int num;

    mvprintw ((int) heightS/5-2, (int) (widthS /2) - 14, "Input the number of artists"); 
    refresh();
    num = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 8), 9, 0, 99999999);
    if (num == -1) return -1;


    // clearing the messages
    move ((int) heightS/5-2, 0);
    clrtoeol ();
    
    mvprintw ((int) (heightS/5)-2-1, (int) (widthS /2) - 14, "Input the country filter"); 
    mvprintw ((int) (heightS/5)-2, (int) (widthS/2) -18, "To have no filter, just hit \"Enter\"");
    refresh();
    char country[maxSize];
    getStringFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 4),  country, maxSize-1);
    mvprintw (heightS, widthS, "%s", country);
    noecho();

    // creation of cmd
    CMD* cmd = createEmptyCMD ();
    setCMDQuery (cmd, 2);
    setCMDTopN (cmd, num);
    if (country[0] != '\0') setCMDCountry (cmd, country);

    query2 (cmd, mngr, 1);

    // cleaning the exit message
    move (heightS -1, 0);
    clrtoeol ();
    
    readResultsScrollable((int) (heightS / 1.6)-2, (int) (widthS / 1.3)-2, (int) (heightS /5 + heightS /8 +1)+1, (int) (widthS * 0.3/(1.3*2))+1); // same as outwin but slightly smaller

    freeCmd (cmd);
    return 0;
}

int loadQ3 (WINDOW* inWin, WINDOW* outWin, AlmightyManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);

    int minAge, maxAge;
    while (true) {
        mvprintw ((int) (heightS/5)-2,(int) (widthS / 2) - 11, "Input the minimum age"); 
        refresh();
        minAge = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 4), 3, 0, 200);
        if (minAge == -1) return -1;

        mvprintw ((int) (heightS/5)-2,(int) (widthS / 2) - 11, "Input the maximum age"); 
        refresh();
        maxAge = getNumberFromInput (inWin,(int)(heightW1 / 2), (int)(widthW1 *3 / 4), 3, 0, 200);
        if (maxAge == -1) return -1;

        if (maxAge >= minAge) break;
        mvwprintw(inWin, (int)(heightW1 / 2), (int)(widthW1 / 4), "         ");
        mvwprintw(inWin, (int)(heightW1 / 2), (int)(widthW1 *3 / 4), "         ");
        mvprintw (heightS/5-2 + 1, widthS /2 - 13, "Invalid input, try again");
        wrefresh(inWin);
    }
    move ((int) (heightS/5)-2, 0);
    clrtoeol ();

    // creation of cmd
    CMD* cmd = createEmptyCMD ();
    setCMDQuery (cmd, 3);
    setCMDAgeMin (cmd, minAge);
    setCMDAgeMax (cmd, maxAge);

    UserManager* u_mngr = getUserManager (mngr);
    MusicManager* m_mngr = getMusicManager (mngr);

    attron (A_BLINK);
    mvprintw ((int)(heightS / 8) -1, (int) (widthS / 2) - 6, "Running...");
    attroff(A_BLINK);
    refresh ();

    query3 (cmd, u_mngr, m_mngr, 1);

    move ((int)(heightS / 8) -1, (int) (widthS / 2) - 6);
    clrtoeol();
    refresh();

    printResults (outWin);

    freeCmd (cmd);
    return 0;
}

int loadQ4 (WINDOW* inWin, WINDOW* outWin, AlmightyManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);
    
    bool flag = false; // filter
    mvprintw ((int) (heightS/5)-2,(int) (widthS / 2) -4, "Query 4");

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
    Date min, max;
    while (!flag) {
        mvwprintw (inWin,(int)(heightW1 / 2), (int)(widthW1 / 4) -5, "                         ");
        mvwprintw (inWin,(int)(heightW1 / 2), (int)(widthW1 / 4) -5, "YYYY/MM/DD");
        mvwprintw (inWin, (int)(heightW1 / 2), (int)(widthW1 *3 / 4) -5, "YYYY/MM/DD");
        wrefresh(inWin);

        // getting the min date
        mvprintw ((int) (heightS/5)-2,(int) (widthS / 2) - 22, "Input the minimum date following the format"); 
        refresh();
        int yearMin = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 4 - 5), 4, 1900, 2024);
        if (yearMin == -1) return -1;
        int monthMin = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 4), 2, 1, 12);
        if (monthMin == -1) return -1;
        int dayMin = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 4 + 3), 4, 1, 31);
        if (monthMin == -1) return -1;

        // getting the max date
        mvprintw ((int) (heightS/5)-2,(int) (widthS / 2) - 22, "Input the maximum date following the format"); 
        refresh();
        int yearMax = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 *3 / 4 - 5), 4, 1900, 2024);
        if (yearMax == -1) return -1;
        int monthMax = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 *3 / 4), 2, 1, 12);
        if (monthMax == -1) return -1;
        int dayMax = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 *3 / 4 + 3), 4, 1, 31);
        if (dayMax == -1) return -1;

        min.day = dayMin, min.month = monthMin, min.year = yearMin;
        max.day = dayMax, max.month = monthMax, max.year = yearMax;
        
        if (compareDate (max, min) > 0) break;
        
        attron (A_UNDERLINE);
        mvprintw (heightS/5-2 - 1, widthS /2 - 13, "Invalid input, try again");
        attroff (A_UNDERLINE);
        refresh();
    }
    move ((int) (heightS/5)-2, 0);
    clrtoeol ();

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

    attron (A_BLINK);
    mvprintw ((int)(heightS / 8) -1, (int) (widthS / 2) - 6, "Running...");
    attroff(A_BLINK);
    refresh ();

    query4 (cmd, h_mngr, m_mngr, a_mngr, 1);

    move ((int)(heightS / 8) -1, (int) (widthS / 2) - 6);
    clrtoeol();
    refresh();

    printResults (outWin);
    freeCmd (cmd);
    return 0;
}

int loadQ5 (WINDOW* inWin, AlmightyManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);

    mvprintw (heightS/5-2, widthS /2 - 9, "Input the user ID"); 
    refresh();
    char idString [10];
    int id = getIdFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 8), idString, 0);
    if (id == -1) return -1;

    mvprintw ((int) heightS/5-2, (int) (widthS /2) - 18, "Input the number of recommendations"); 
    refresh();
    int num = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 * 3 / 4), 9, 0, 99999999);
    if (num == -1) return -1;
    noecho();

    move ((int) (heightS/5)-2, 0);
    clrtoeol ();

    // creation of cmd
    CMD* cmd = createEmptyCMD ();
    setCMDQuery (cmd, 5);
    setCMDId (cmd, id);
    setCMDNoUsers (cmd, num);

    HistoryManager* h_mngr = getHistoryManager (mngr);
    MusicManager* m_mngr = getMusicManager (mngr);
    UserManager* u_mngr = getUserManager (mngr);

    attron (A_BLINK);
    mvprintw ((int)(heightS / 8) -1, (int) (widthS / 2) - 6, "Running...");
    attroff(A_BLINK);
    refresh ();

    query5 (cmd, h_mngr, m_mngr, u_mngr, 1);

    move ((int)(heightS / 8) -1, (int) (widthS / 2) - 6);
    clrtoeol();
    refresh();

    // cleaning the exit message
    move (heightS -1, 0);
    clrtoeol ();
    
    readResultsScrollable((int) (heightS / 1.6)-2, (int) (widthS / 1.3)-2, (int) (heightS /5 + heightS /8 +1)+1, (int) (widthS * 0.3/(1.3*2))+1); // same as outwin but slightly smaller
    
    freeCmd (cmd);
    return 0;
}

int loadQ6 (WINDOW* inWin, AlmightyManager* mngr) {
    int widthS, heightS, widthW1, heightW1;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(inWin, heightW1, widthW1);

    mvprintw (heightS/5-2, widthS /2 - 9, "Input the user ID"); 
    refresh();
    char idString[9];
    int id = getIdFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 / 4) - 4, idString, 0);
    if (id == -1) return -1;

    mvprintw (heightS/5-2, widthS /2 - 9, "                     "); 
    mvprintw ((int) heightS/5-2, (int) (widthS /2) - 8, "Input the year"); 
    refresh();
    int year = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 /2) - 2, 4, 1900, 2024);
    if (year == -1) return -1;

    mvprintw ((int) heightS/5-2, (int) (widthS /2) - 14, "Input the number of artists"); 
    refresh();
    int noArtists = getNumberFromInput (inWin, (int)(heightW1 / 2), (int)(widthW1 * 3 / 4) - 1, 4, 0, 99999999);
    if (noArtists == -1) return -1;


    // creation of cmd
    CMD* cmd = createEmptyCMD ();
    setCMDQuery (cmd, 6);
    setCMDId (cmd, id);
    setCMDYear (cmd, year);
    setCMDNArtists (cmd, noArtists);

    HistoryManager* h_mngr = getHistoryManager (mngr);
    MusicManager* m_mngr = getMusicManager (mngr);

    move ((int) heightS/5-2, 0);
    clrtoeol();
    attron (A_BLINK);
    mvprintw ((int)(heightS / 8) -1, (int) (widthS / 2) - 6, "Running...");
    attroff(A_BLINK);
    refresh ();

    query6 (cmd, h_mngr, m_mngr, 1);

    move ((int)(heightS / 8) -1, (int) (widthS / 2) - 6);
    clrtoeol();
    refresh();

    // cleaning the exit message
    move (heightS -1, 0);
    clrtoeol ();
    
    readResultsScrollable((int) (heightS / 1.6)-2, (int) (widthS / 1.3)-2, (int) (heightS /5 + heightS /8 +1)+1, (int) (widthS * 0.3/(1.3*2))+1); // same as outwin but slightly smaller
    
    freeCmd (cmd);
    return 0;
    return 0;
}