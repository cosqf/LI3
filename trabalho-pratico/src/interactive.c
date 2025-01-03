#include <ncurses.h>
#include <panel.h>
#include <utils.h>
#include <parsing.h>

#include <interactive.h>
#include <interactive_queries.h>
#include <interactive_utils.h>
#include <unistd.h>

void loadGreeting () {
    int widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);

    loadDotAnimation ();

    char** title = getAllLines ("images/title.txt", heightS, widthS);
    if (title == NULL) return;

    int size = strlen (title[0]) -1;
    int posy = (int) (heightS/8);
    int posx = (int) (widthS/2 - size/2);
    for (int i = 0; i< LINES_TITLE; i++) {        
        for (int j= 0; j < widthS; j++) {
            if (j<posx || j> posx + size) mvaddch (posy+i, j, ' ');
            else mvaddch (posy+i, j, title[i][j-posx]);
            refresh ();
            usleep (1000);
        }
        usleep (80000);
    }
    for (int i = 0; i < LINES_TITLE; i++) free(title[i]);
    free(title);

}

void loadBye () {
    int widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);

    char** bye1 = getAllLines ("images/bye1.txt", heightS, widthS);
    if (bye1 == NULL) return;
    char** bye2 = getAllLines ("images/bye2.txt", heightS, widthS);
    if (bye2 == NULL){
        free (bye1);
        return;
    }
    clear();
    int size = strlen (bye1[0]) -1;
    int posy = (int) (heightS - LINES_BYE);
    int posx = (int) (widthS-size);
    for (int times = 0; times <3; times++) {
        if (times != 0) usleep (500000);
        for (int i = 0; i < LINES_BYE; i++) mvaddstr (posy+i, posx, bye1[i]); 
        refresh ();
        usleep (500000);
        clear ();
        for (int i = 0; i < LINES_BYE; i++) mvaddstr (posy+i, posx, bye2[i]); 
        refresh ();
    }

    loadDotAnimation();

    for (int i = 0; i < LINES_BYE; i++) {
        free (bye1[i]);
        free (bye2[i]);
    }
    free (bye1);
    free (bye2);
}

int loadMainPage () {
    int widthS, heightS;
    getmaxyx(stdscr, heightS, widthS);

    WINDOW* win = newWindowWithBorder((int)((heightS / 2)), (int)(widthS / 1.5), (int)(heightS / 8) + 7, (int)(widthS / 6));
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

int gettingData (WINDOW* win, AlmightyManager* mngr) {
    int widthS, heightS, widthW, heightW;;
    getmaxyx(stdscr, heightS, widthS);
    getmaxyx(win, heightW, widthW);
    echo();
    mvprintw((int) heightS/6, (int) widthS/2 -16, "Insert the path to the dataset");
    mvprintw (heightS-1, 1, "Type \"exit\" to leave");
    refresh();

    char path[38];
    char pathDefault[] = "small/dataset/sem_erros/";
    while (true) {
        curs_set(1);
        wmove(win, (int)(heightW / 8), (int)(widthW / 10));
        wgetnstr(win, path, 37);
        if (strcmp (path, "exit")  == 0) {
            delwin (win);
            return -1;
        }
        curs_set(0);

        move ((int)heightS / 6, 0);
        clrtoeol();
        attron (A_BLINK);
        mvprintw((int)heightS / 6, (int)widthS / 2 - 8, "Getting data...");
        attroff(A_BLINK);
        refresh();

        if (getData(path, mngr) && getData(pathDefault, mngr)) {
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
    if (widthS < 65 || heightS < 15) {
        printw ("The window size is too small to load the page!");
        getch();
        endwin();
        return -1;
    }
    FILE* file = freopen("/dev/null", "w", stderr); //redirecting stderr to prevent perror messages from showing
    (void) file;

    // Loading
    loadGreeting();
    int mainPageChoice = loadMainPage();
    if (mainPageChoice == -1) {
        loadBye ();
        endwin();
        return 0;
    }
    
    WINDOW* win1 = newWindowWithBorder ((int) (heightS/1.5), (int) (widthS/1.5), (int) (heightS/6)+2, (int) (widthS/6));

    // Fetching data
    AlmightyManager* mngr = initializeHash ();
    int paths = gettingData (win1, mngr);
    if (paths == -1) {
        clear ();
        delwin (win1);
        loadBye();
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
            break;
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
            break;
        }
        noecho();
        clear();
        delwin (inWin);
        delwin (outWin);
        if (repeat == -1) break;
    }
    freeHash (mngr);
    clear ();
    loadBye ();
    endwin ();
    return 0;
}