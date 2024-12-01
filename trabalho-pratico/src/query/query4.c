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



void adjustDateLimits(Date *date, bool flag) { // will subtract the days till the beggining of the week and add till the end of the week depending on flag
    if (!date) {
        perror ("Error adjusting the date limits");
        return;
    }
    short int weekday = getWeekday (*date);
    if (flag == 0) {
        while (weekday != 0) { // subtract till sunday
            date->day--;

            if (date->day < 1) {
                date->month--;
                if (date->month < 1) {
                    date->month = 12;
                    date->year--;
                }
                date->day = getDaysInMonth(date->month, date->year);
            }

            weekday = getWeekday(*date);
        }

    }
    else {
        while (weekday != 6) { // add till saturday
            date->day++;

            if (date->day > getDaysInMonth (date->month, date->year)) {
                date->month++;
                if (date->month > 12) {
                    date->month = 1;
                    date->year++;
                }
                date->day = 1;
            }

            weekday = getWeekday(*date);
        }
    }
}
void freeArtistList (ArtistList* list) {
    free(list->artistsIds);
    free (list);
}


// function to process the top 10 artists for a week, will update history manager with the weekly array of artists
void processWeeklyTop10(GHashTable* topArtistsWeek, HistoryManager* mngr, Date firstDayOfWeek) {
    int lengthWeekHash = g_hash_table_size(topArtistsWeek);
    int limit = (lengthWeekHash < 10) ? lengthWeekHash : 10;
    if (limit == 0) return;

    Tuple* artistsWeek = sortHash(topArtistsWeek, compareTuple);  // sorting artists by play duration

    ArtistList* top10artistWeek = malloc(sizeof(ArtistList));
        if (mallocErrorCheck (top10artistWeek)) {
            free (artistsWeek);
            return;
        }
    int* limitedArray = malloc (sizeof (int) * limit);
        if (mallocErrorCheck (limitedArray)) {
            free (artistsWeek);
            free (top10artistWeek);
            return;
        }

    for (int i = 0; i< limit; i++) limitedArray[i] = artistsWeek [i].key;
    free(artistsWeek);

    top10artistWeek->artistsIds = limitedArray;
    top10artistWeek->count = limit;
    insertInHistoryByWeeks (mngr, firstDayOfWeek, top10artistWeek);
}

// main function to create the tree
void getHistoryByWeeks (HistoryManager* historyManager, MusicManager* musicManager) {
    // setting up array
    int lengthHash = lengthHistory (historyManager);
    History** array = malloc (sizeof (History*) * lengthHash);
    if (mallocErrorCheck (array)) return;

    int lengthArray = sortHistory(historyManager, &array);  // sort history by timestamp
    
    if (lengthArray == 0) {
        free(array);
        return;
    }
    GHashTable* topArtistsWeek = createHash();  // temporary hash table for weekly artist stats

    Date firstDayOfWeek = (getHistoryTimestamp (array[0])).date;
    short int weekday = getWeekday (firstDayOfWeek);
    if (weekday != 0) adjustDateLimits (&firstDayOfWeek, 0); // subtract until last sunday

    for (int i = 0; i < lengthArray; i++) {
        History* history = array[i];
        Date date = (getHistoryTimestamp(history)).date;
        weekday = getWeekday (date);

        // if its a new week process the previous weeks top 10 artists
        if (weekday == 0 && (daysDiff (date, firstDayOfWeek) >= 7)) {
            processWeeklyTop10(topArtistsWeek, historyManager, firstDayOfWeek);
            g_hash_table_remove_all(topArtistsWeek);  // clean the hash table for reuse
            firstDayOfWeek = date;
        }
        // adds all artists in the weekly hash table 
        int musicId = getHistoryMusicId(history);
        Music* music = lookupMusicHash (musicManager, musicId);
        const int* artistIds = getMusicArtistID(music);
        int artistCount = getMusicArtistIDCount(music);

        for (int j = 0; j < artistCount; j++) {
            updateHash(topArtistsWeek, artistIds[j], durationInSeconds (getHistoryDuration(history)));
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
    ArtistList* list = value;
    bool filter = data->isFilterOn;

    if (filter) {
        if (compareDate(*date, maxDate) > 0) return TRUE; // stops search early  

        if (compareDate(*date, minDate) >= 0) {
            for (int i = 0; i < list->count; i++) {
                int artistId = list->artistsIds[i];
                updateHash (artistsTimeInTop, artistId, 1);
            }
            //printf ("\n\nprinting list for date: %d/%d/%d\n", date->day,date->month,date->year);
            //for (int i = 0; i< list->count; i++) printf ("artist %d with %d, ",list->artistsIds[i].key, list->artistsIds[i].value);
        }

    }
    else {      
            for (int i = 0; i < list->count; i++) {
                int artistId = list->artistsIds[i];
                updateHash (artistsTimeInTop, artistId, 1);
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
    if (isFilterOn) {
        adjustDateLimits (&minDay, 0);
        adjustDateLimits (&maxDay, 1);
    }
    feederHistory data = {.maxDay = maxDay, 
                          .minDay = minDay,
                          .table = artistsTimeInTop,
                          .isFilterOn = isFilterOn
                          };

    traverseTree(historyManager, callbackHistoryQuery4, &data); // traverse tree according to the dates, pass the nodes to the hash

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
    closeOutputFile (output);

    free (array);
    deleteHash (artistsTimeInTop);
}