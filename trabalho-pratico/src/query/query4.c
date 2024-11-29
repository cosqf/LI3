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

// days functions
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

        weekdayMax = getWeekday(*dateMax);
    }
}


// function to process the top 10 artists for a week, will update history manager with the weekly array of artists
void processWeeklyTop10(GHashTable* topArtistsWeek, HistoryManager* mngr, Date firstDayOfWeek) {
    int lengthWeekHash = g_hash_table_size(topArtistsWeek);
    int limit = (lengthWeekHash < 10) ? lengthWeekHash : 10;
    if (limit == 0) return ;

    Tuple* artistsWeek = sortHash(topArtistsWeek, compareTuple);  // sorting artists by play duration

    ArtistList* top10artistWeek = malloc(sizeof(ArtistList));
        if (mallocErrorCheck (top10artistWeek)) {
            free (artistsWeek);
            return;
        }
    Tuple* limitedArray = malloc (sizeof (Tuple) * limit);
        if (mallocErrorCheck (limitedArray)) {
            free (artistsWeek);
            free (top10artistWeek);
            return;
        }

    for (int i = 0; i< limit; i++) limitedArray[i] = artistsWeek [i];
    free(artistsWeek);

    top10artistWeek->artistsIds = limitedArray;
    top10artistWeek->count = limit;
    insertInHistoryByWeeks (mngr, top10artistWeek, firstDayOfWeek);
}

// main function to create the tree
void getHistoryByWeeks (HistoryManager* historyManager, MusicManager* musicManager) {
    History** array = sortHistory(historyManager);  // sort history by timestamp
    int lengthArray = lengthHistory (historyManager);
    if (lengthArray == 0) {
        free(array);
        return;
    }
    GHashTable* topArtistsWeek = createHash();  // temporary hash table for weekly artist stats

    bool isFirstSunday = 1; // check for the first time during the week that is sunday
    Date firstDayOfWeek = (getHistoryTimestamp (array[0])).date;
    short int weekday = getWeekday (firstDayOfWeek);

    for (int i = 0; i < lengthArray; i++) {
        History* history = array[i];
        Date date = (getHistoryTimestamp(history)).date;
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
        Music* music = lookupMusicHash (musicManager, musicId);
        const int* artistIds = getMusicArtistID(music);
        int artistCount = getMusicArtistIDCount(music);

        for (int j = 0; j < artistCount; j++) {
            updateHash(artistIds[j], topArtistsWeek, durationInSeconds (getHistoryDuration(history)));
        }

        deleteMusic(music); 
    }

    // handling the last week
    processWeeklyTop10(topArtistsWeek, historyManager, firstDayOfWeek);
    
    deleteHash(topArtistsWeek);
    free(array);
}

typedef struct {
    Date minDay;
    Date maxDay;
    GHashTable* table;
    bool isFilterOn;
} feederHistory;

gboolean callbackHistoryQuery4 (gpointer key, gpointer value, gpointer dataFeed) { // key: date, value: artistlist
    Date* date = (Date*)key;
    feederHistory* data = (feederHistory*) dataFeed;

    Date minDate = data->minDay;
    Date maxDate = data->maxDay;
    GHashTable* artistsTimeInTop = data->table;
    bool filter = data->isFilterOn;

    if (filter) {
        if (compareDate(maxDate, *date) < 0) return TRUE; // stops search early  

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



void query4 (CMD* cmd, HistoryManager* historyManager, MusicManager* musicManager, ArtistManager* artistManager, int cmdCounter) {
    Date minDay = getCMDdateMin (cmd);
    Date maxDay = getCMDdateMax (cmd);
    GHashTable* artistsTimeInTop = createHash(); // will store the artists with the number of times they were on the top 10

    if (!historyTreeIsInitialized (historyManager)) { // will get all the top artists in each week
        initializeHistoryTree(historyManager);
        getHistoryByWeeks (historyManager, musicManager); 
    }
    bool isFilterOn = ! (minDay.year == 0);
    if (isFilterOn) adjustDateLimits (&minDay, &maxDay);
    feederHistory data = {.maxDay = maxDay, 
                          .minDay = minDay,
                          .table = artistsTimeInTop,
                          .isFilterOn = isFilterOn
                          };

    traverseTreeInRange(historyManager, callbackHistoryQuery4, &data); // traverse tree according to the dates, pass the nodes to the hash

    Tuple* array = sortHash (artistsTimeInTop, compareTuple);
    int artistId = array[0].key;
    int artistCount = array[0].value;


    // outputting
    char filename[50];
    snprintf (filename, sizeof(filename),"resultados/command%d_output.txt", cmdCounter);
    Output* output = openOutputFile (filename);
    bool type = getArtistTypeHash (artistId, artistManager);

    char* lines [3] = {NULL};
    char idString[15], typeString[15], artistCountString[15];
    snprintf (idString, sizeof(idString), "A%07d", artistId);
    if (type) strcpy (typeString, "group");
    else strcpy (typeString, "individual");
    snprintf (artistCountString, sizeof(artistCountString), "%d", artistCount);
    
    lines[0] = idString;
    lines[1] = typeString;
    lines[2] = artistCountString;

    setOutput (output, lines, 3);
    writeQuerys (output, cmd);

    free (array);
    deleteHash (artistsTimeInTop);
}