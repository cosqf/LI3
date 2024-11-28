#include <query4.h>
#include <glib.h>
#include <history.h>
#include <musicManager.h>
#include <historyManager.h>
#include <hashtableManager.h>
#include <cmd.h>
#include <utils.h>
#include <queryUtils.h>
#include <parsingUtils.h>
#include <utils.h>


void outputtingQuery4 (int id) { // .....
    // char* filepath;
    // Output* output = openOutputFile (filepath);
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

// function to process the top 10 artists for a week, will update history manager with the weekly array of artists
void processWeeklyTop10(GHashTable* topArtistsWeek, HistoryManager* mngr, Date firstDayOfWeek) {
    int lengthWeekHash = g_hash_table_size(topArtistsWeek);
    int limit = (lengthWeekHash < 10) ? lengthWeekHash : 10;

    Tuple* artistsWeek = sortHash(topArtistsWeek, compareTuple);  // sorting artists by play duration
    ArtistList* top10artistWeek = malloc(sizeof(ArtistList) * limit);
    top10artistWeek->artistsIds = artistsWeek;
    top10artistWeek->count = limit;
    insertInHistoryWeeks (mngr, top10artistWeek, firstDayOfWeek);
    free(artistsWeek);
}


void getHistoryByWeeks (hashtableManager* mngr) {
    HistoryManager* historyManager = getHistoryManager (mngr);
    History** array = sortHistory(historyManager);  // Sort history by timestamp
    int lengthArray = lengthHistory (historyManager);

    GHashTable* topArtistsWeek = createHash();  // temporary hash table for weekly artist stats
    bool isFirstSunday = 0; // check for the first time during the week that is sunday
    Date firstDayOfWeek = getHistoryTimestamp (array[0]);
    short int weekday = getWeekday (firstDayOfWeek);
    for (int i = 0; i < lengthArray; i++) {
        History* history = array[i];
        Date date = getHistoryTimestamp(history);
        weekday = getWeekday (date);

        // if its a new week process the previous weeks top 10 artists
        if (weekday == 0 && isFirstSunday) {
            processWeeklyTop10(topArtistsWeek, historyManager, firstDayOfWeek);
            g_hash_table_remove_all(topArtistsWeek);  // clean the hash table for reuse
            firstDayOfWeek = date;
            isFirstSunday = 0;
        }
        if (weekday != 0) isFirstSunday = 1;

        // adds all artists in the weekly hash table 
        int musicId = getHistoryMusicId(history);
        Music* music = lookupMusicHash(getMusicManager(mngr), musicId);
        const int* artistIds = getMusicArtistID(music);
        int artistCount = getMusicArtistIDCount(music);

        for (int j = 0; j < artistCount; j++) {
            updateHash(artistIds[j], topArtistsWeek, durationInSeconds (getHistoryDuration(history)));
        }

        deleteMusic(music); 
    }

    // handling the last week in case it ends early
    if (weekday != 0) processWeeklyTop10(topArtistsWeek, historyManager, firstDayOfWeek);
    deleteHash(topArtistsWeek);
    free(array);
}

typedef struct {
    Date minDay;
    Date maxDay;
    GHashTable* table;
    bool isFilterOn;
} feederHistory;

gboolean callbackHistoryQuery4 (gpointer key, gpointer value, gpointer dataFed) {
    Date* date = (Date*)key;
    feederHistory* data = (feederHistory*) dataFed;

    Date minDate = data->minDay;
    Date maxDate = data->maxDay;
    GHashTable* artistsTimeInTop = data->table;
    bool filter = data->isFilterOn;

    if (filter) {
        if (compareDate(maxDate, *date) < 0) return TRUE;  

        if (compareDate(minDate, *date) >= 0) {
            ArtistList* list = value;
            
            for (int i = 0; i < list->count; i++) {
                int artistId = list->artistsIds[i].key;
                updateHash (artistId, artistsTimeInTop, 1);
            }
        }
    }
    else {
        ArtistList* list = value;
            
            for (int i = 0; i < list->count; i++) {
                int artistId = list->artistsIds[i].key;
                updateHash (artistId, artistsTimeInTop, 1);
            }
    }
    return FALSE; 
}



void query4 (CMD* cmd, hashtableManager* mngr) {
    HistoryManager* historyManager = getHistoryManager (mngr);
    Date minDay = getCMDdateMin (cmd);
    Date maxDay = getCMDdateMax (cmd);
    GHashTable* artistsTimeInTop = createHash(); // will store the artists with the number of times they were on the top 10

    getHistoryByWeeks (mngr); 
    bool isFilterOn = ! (minDay.year == 0);
    if (isFilterOn) adjustDateLimits (&minDay, &maxDay);
    feederHistory data = {.maxDay = maxDay, 
                          .minDay = minDay,
                          .table = artistsTimeInTop,
                          .isFilterOn = isFilterOn
                          };

    traverseTreeInRange(historyManager, callbackHistoryQuery4, &data);

    Tuple* array = sortHash (artistsTimeInTop, compareTuple);
    outputtingQuery4 (array[0].key);

    free (array);
    deleteHash (artistsTimeInTop);
}

/*
void query4 (CMD* cmd, hashtableManager* mngr) {
    HistoryManager* historyManager = getHistoryManager (mngr);
    Date minDay = getCMDdateMin (cmd);
    Date maxDay = getCMDdateMax (cmd);
    adjustDateLimits (&minDay, &maxDay);

    // assuming array vvvv
    History* array = historyManager->array;
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
*/
