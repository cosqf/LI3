#include <ncurses.h>
#include <panel.h>
#include <utils.h>
#include <parsing.h>

#include <interactive.h>
#include <interactive_queries.h>
#include <interactive_utils.h>

int loadMainPage () {
    int widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);

    attron (A_BOLD | A_UNDERLINE);
    mvprintw ((int) (heightS/6), (int) (widthS/2) - 5, "Main Menu");
    refresh();
    attroff (A_BOLD | A_UNDERLINE);
    WINDOW* win = newWindowWithBorder((int)(heightS / 2), (int)(widthS / 1.5), (int)(heightS / 6) + 3, (int)(widthS / 6));
    if (!win) {
        perror ("Error creating window");
        return -1;
    }
    int widthW, heightW;
    getmaxyx(win, heightW, widthW);
    bool flag = false;
    while (true) {
        printHighlightedText(win, (int) (heightW / 3), (int) (widthW / 2) - 2, "Start", !flag);
        printHighlightedText(win, (int) (heightW * 2 / 3), (int) (widthW / 2) - 2, "Leave", flag);
        wrefresh(win);  
        int key = getch ();
        if (key == KEY_UP || key == KEY_DOWN) flag = ! flag;
        else if (key == 10 || key == KEY_RIGHT) { // key 10 is enter
            clear();
            delwin(win);
            if (flag) return -1;
            else return 0;
        } else if (key == 27) { // ESC to exit
            delwin(win);
            return -1;
        }
    }
}

int gettingData (WINDOW* win, hashtableManager* mngr) {
    int widthS, heightS, widthW, heightW;;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(win, heightW, widthW);
    echo();
    mvprintw((int) heightS/6, (int) widthS/2 -16, "Insert the path to the dataset");
    mvprintw (heightS-1, 1, "Type \"exit\" to leave");
    refresh();

    char path[38];
    while (true) {
        curs_set(1);
        wmove(win, (int)(heightW / 8), (int)(widthW / 10));
        wgetnstr(win, path, 36);
        if (strcmp (path, "exit")  == 0) {
            delwin (win);
            return -1;
        }
        curs_set(0);

        move ((int)heightS / 6, 0);
        clrtoeol();
        attron (A_BLINK);
        mvprintw((int)heightS / 6, (int)widthS / 2 - 7, "Getting data...");
        attroff(A_BLINK);
        move(0, 0);
        refresh();
        
        if (getData(path, mngr)) {
            mvprintw((int)heightS / 6, (int)widthS / 2 - 11, "Invalid path, try again");
            refresh();
            mvwprintw (win, (int)(heightW / 8), (int)(widthW / 8) , "                                     ");
            wrefresh(win);
            memset(path, 0, sizeof(path));
        } else break;
    }
    noecho();
    return 0;
}

int gettingQuery (WINDOW* win) {
    int widthS, heightS, widthW, heightW;;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(win, heightW, widthW);

    mvprintw((int) heightS/6, (int) widthS/2 -18, "Insert the query you want to execute");
    refresh();

    int highlighted = 1;
    while (true) {
        wmove(win, 3, 2);
        wrefresh(win);
        for (int i = 1; i<7; i++) {
            char queryStr[9];
            snprintf(queryStr, sizeof(queryStr), "Query %d", i);
            printHighlightedText(win, (int) (heightW *i/7), (int) (widthW/2) - 3, queryStr, highlighted == i);
        }

        wrefresh(win);  
        int key = getch ();
        if (key == KEY_UP){
            highlighted--;
            if (highlighted == 0) highlighted = 6;
        }
        else if (key == KEY_DOWN){
            highlighted++;
            if (highlighted == 7) highlighted = 1;
        }
        else if (key == 10 || key == KEY_RIGHT) { // key 10 is enter
            clear();
            return highlighted;
        } else if (key == 27) { // ESC to exit
            return -1;
        }
    }
}
/**@brief Runs the interactive program.*/
int main () {
    initscr();
    noecho(); cbreak(); keypad(stdscr, TRUE); curs_set(0);
    int widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);
    if (widthS < 60 || heightS < 14) {
        printw ("The window size is too small to load the page!");
        getch();
        endwin();
        return -1;
    }
    FILE* file = freopen("/dev/null", "w", stderr); //redirecting stderr to prevent perror messages from showing
    (void) file;

    // Loading
    int mainPageChoice = loadMainPage();
    if (mainPageChoice == -1) {
        clear();
        endwin();
        return 0;
    }
    
    WINDOW* win1 = newWindowWithBorder ((int) (heightS/1.5), (int) (widthS/1.5), (int) (heightS/6)+2, (int) (widthS/6));

    // Fetching data
    hashtableManager* mngr = initializeHash ();
    int paths = gettingData (win1, mngr);
    if (paths == -1) {
        clear ();
        delwin (win1);
        endwin();
        return 0;
    }
    delwin (win1);


    // Queries loop
    while (true) { 
        WINDOW* win2 = newWindowWithBorder ((int) (heightS/1.5), (int) (widthS/1.5), (int) (heightS/6)+2, (int) (widthS/6));
        wrefresh (win2);
        mvprintw (heightS-1, 1, "                               ");
        mvprintw (heightS-1, 1, "Hit \"Esc\" to leave");
        refresh ();
        int query = gettingQuery (win2);
        if (query == -1) {
            clear ();
            delwin (win2);
            endwin ();
            return 0;
        }
        clear();
        delwin (win2);

        WINDOW* inWin  = newWindowWithBorder((int) (heightS / 8)+1, (int) (widthS / 1.3), (int) (heightS / 5), (int) (widthS * 0.3/(1.3*2)));
        WINDOW* outWin = newWindowWithBorder((int) (heightS / 1.6)-1, (int) (widthS / 1.3), (int) (heightS /5 + heightS /8 +1), (int) (widthS * 0.3/(1.3*2)));

        echo();
        int repeat = 0;
        switch (query){
        case 1:
            repeat = loadQ1 (inWin, outWin, mngr);
            break;
        case 2:
            repeat = loadQ2 (inWin, mngr);
            break;
        case 3: 
            repeat = loadQ3 (inWin, outWin, mngr);
            break;
        case 4:
            repeat = loadQ4 (inWin, outWin, mngr);
            break;
        case 5:
            repeat = loadQ5 (inWin, mngr);
            break;
        case 6:
            break;
        default:
            perror ("Starting query error");
            break;
        }
        noecho();
        clear();
        delwin (inWin);
        delwin (outWin);
        if (repeat == -1) break;
    }
    endwin ();
    return 0;
}