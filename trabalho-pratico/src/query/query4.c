#include <glib.h>
#include <history.h>
#include <musicManager.h>
#include <cmd.h>
#include <utils.h>
#include <queryUtils.h>
#include <parsingUtils.h>

// vvv this will go somewhere else
typedef struct historyManager {
    History** array;
    int length;
    GHashTable* history;
} HistoryManager;


void outputtingQuery4 (int id) { // .....
    char* filepath;
    Output* output = openOutputFile (filepath);
}

int compareTimestamp(const void* a, const void* b) {
    History* historyA = (History*) a;
    History* historyB = (History*) b;

    Date dateA = getHistoryTimestamp (historyA);
    Date dateB = getHistoryTimestamp (historyB);

    int c = compareDate (dateA, dateB);

    return c;
}

short int getWeekday (Date date) { // gotten from wikipedia, sunday == 0
    return ((date.day += date.month < 3 ? date.year-- : 
            date.year - 2, 23 * date.month/9 + date.day + 4 + date.year/4- date.year/100 + date.year/400)%7);
}

int getDaysInMonth(int month, int year) {
    switch (month) {
        case 4: case 6: case 9: case 11: return 30; // april, june, september, november
        case 2: // february
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return 29; // leap year
            return 28;
        default: return 31; // january, march, may, july, august, october, december
    }
}


void adjustDateLimits(Date *dateMin, Date *dateMax) { // will subtract the days till the beggining of the week and add till the end of the week
    if (!dateMin || !dateMax) {
        perror ("Error adjusting the date limits");
        return;
    }

    short int weekdayMin = getWeekday(*dateMin);

    while (weekdayMin != 0) { // subtract till sunday
        dateMin->day--;

        if (dateMin->day < 1) {
            dateMin->month--;
            if (dateMin->month < 1) {
                dateMin->month = 12;
                dateMin->year--;
            }
            dateMin->day = getDaysInMonth(dateMin->month, dateMin->year);
        }

        weekdayMin = getWeekday(*dateMin);
    }

    short int weekdayMax = getWeekday(*dateMax);

    while (weekdayMax != 6) { // add till saturday
        dateMax->day++;

        if (dateMax->day > getDaysInMonth (dateMax->month, dateMax->year)) {
            dateMax->month++;
            if (dateMax->month > 12) {
                dateMax->month = 1;
                dateMax->year++;
            }
            dateMax->day = 1;
        }

        weekdayMin = getWeekday(*dateMax);
    }
}


void query4 (CMD* cmd, hashtableManager* mngr) {
    // takes historymanager from mngr vvv
    HistoryManager* historyManager;
    Date minDay, maxDay; // gets from cmd
    adjustDateLimits (&minDay, &maxDay);

    // assuming array vvvv
    History** array = historyManager->array;
    int lengthArray = historyManager->length;
    qsort (array, lengthArray, sizeof(History*), compareTimestamp);

    GHashTable* topArtistsTotal = createHash(); // will store the artists with the number of times they were on the top 10
    GHashTable* topArtistsWeek = createHash(); // temporary hash table, will store the artists of each week

    bool isFirstSunday = 0; // check for the first time during the week that is sunday
    for (int i = 0; i< lengthArray; i++) {
        Date date = getHistoryTimestamp(array [i]);
        if (compareDate (minDay, date) < 0 || compareDate (maxDay, date) > 0 ) continue; // filter

        short int weekday  = getWeekday (date);
        // when it becomes sunday itll add the top 10 from the week table to the total table and then reset the week hash table
        if (weekday == 0 && isFirstSunday) {  
            int lengthWeekHash =  g_hash_table_size (topArtistsWeek);
            Tuple* artistsWeek = sortHash (topArtistsWeek);          // organized tuple array
            for (int j = 0; j < 10 && j < lengthWeekHash ; j++) {
                updateHash (artistsWeek[j].key, topArtistsTotal, 1);
            }
            g_hash_table_remove_all (topArtistsWeek);
            isFirstSunday = 0;
        }
        else { // adds all artists in the weekly hash table 
            int musicId = getHistoryMusicId (array[i]);
            Music* music = lookupMusicHash (getMusicManager (mngr), musicId);
            const int* artistsIds = getMusicArtistID (music);
            int artistCount = getMusicArtistIDCount (music);

            for (int j = 0; j < artistCount; j++) {
                updateHash (artistsIds[j], topArtistsWeek, durationInSeconds (getHistoryDuration (array[i])));
            }
            deleteMusic (music);
            isFirstSunday = 1;
        }
    }
    deleteHash (topArtistsWeek);

    Tuple* topArtists = sortHash (topArtistsTotal);

    deleteHash (topArtistsTotal);
    outputtingQuery4 (topArtists[0].key);
}
