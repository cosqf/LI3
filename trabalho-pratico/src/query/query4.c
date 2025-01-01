#include <query4.h>
#include <glib.h>
#include <history.h>
#include <musicManager.h>
#include <historyManager.h>
#include <artistManager.h>
#include <cmd.h>
#include <utils.h>
#include <queryUtils.h>
#include <parsingUtils.h>
#include <utils.h>

void adjustDateLimits(Date *date) { // will subtract the days till the beggining of the week
    if (!date) {
        perror ("Error adjusting the date limits");
        return;
    }
    short int weekday = getWeekday (*date);
    while (weekday != 1) { // subtract till sunday
        date->day--;

        if (date->day < 1) {
            date->month --;
            if (date->month < 1) {
                date->month = 12;
                date->year --;
            }
            date->day = getDaysInMonth (date->month, date->year);
        }
        weekday = getWeekday(*date);
    }
}

void freeArtistList (ArtistList* list) {
    free(list->artistsIds);
    free (list);
}

guint dateHashFunc(gconstpointer key) {
    const Date* date = (const Date*) key;
    return (guint)(date->year * 10000 + date->month * 100 + date->day);
}

gboolean dateEqualFunc(gconstpointer a, gconstpointer b) {
    const Date* date1 = (const Date*) a;
    const Date* date2 = (const Date*) b;
    return (date1->year == date2->year &&
            date1->month == date2->month &&
            date1->day == date2->day);
}

void sortHistoryByWeek (History* history, MusicManager* musicManager, GHashTable* hashWithWeeks) {
    Date date = (getHistoryTimestamp (history)).date;
    adjustDateLimits (&date); // get last sunday
    
    int musicId = getHistoryMusicId(history);
    int* artistIds;
    int artistCount = lookupMusicArtistIDsHash (musicManager, musicId, &artistIds);
    for (int j = 0; j < artistCount; j++) {
        Tuple tuple = {.key = artistIds[j], .value = durationInSeconds (getHistoryDuration(history))};
        updateHashWithWeeks (hashWithWeeks, date, tuple);
    }
    free (artistIds);
}

void updateHashWithWeeks (GHashTable* bigTable, Date date, Tuple tuple) {
    GHashTable* weekTable = (GHashTable*) g_hash_table_lookup (bigTable, &date);
    if (weekTable) {
        updateHash(weekTable, tuple.key, tuple.value);
    } else {
        weekTable = createHash();
        insertHash(weekTable, tuple.key, tuple.value);

        Date* dateKey = malloc(sizeof(Date));
        if (mallocErrorCheck (dateKey)) return;
        *dateKey = date;
        g_hash_table_insert(bigTable, dateKey, weekTable);
    }
}


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
    if (!historyTreeIsInitialized (historyManager)) { // will get all the top artists in each week
        createAndSortTree (historyManager, sortHistoryByWeek,  musicManager);
        //printGTree(historyManager);
    }
    GHashTable* artistsTimeInTop = createHash(); // will store the artists with the number of values they were on the top 10

    bool isFilterOn = (minDay.year != 0);
    if (isFilterOn) adjustDateLimits (&minDay);

    feederHistory data = {.maxDay = maxDay, 
                          .minDay = minDay,
                          .table = artistsTimeInTop,
                          .isFilterOn = isFilterOn
                          };

    traverseTree(historyManager, callbackHistoryQuery4, &data); // traverse tree according to the dates, pass the nodes to the hash

    // outputting
    char filename[50];
    snprintf (filename, sizeof(filename),"resultados/command%d_output.txt", cmdCounter);
    Output* output = openOutputFile (filename);

    Tuple biggestArtist = getBiggestFromHash (artistsTimeInTop);
 
    if (biggestArtist.key == -1) writeNewLine(output);
    else {
        int artistId = biggestArtist.key;
        int artistCount = biggestArtist.value;

        char* lines [3] = {NULL};
        char idString[15], typeString[15], artistCountString[15];

        bool type = getArtistTypeHash (artistId, artistManager);
        snprintf (idString, sizeof(idString), "A%07d", artistId);
        if (type) strcpy (typeString, "group");
        else strcpy (typeString, "individual");
        snprintf (artistCountString, sizeof(artistCountString), "%d", artistCount);
        
        lines[0] = idString;
        lines[1] = typeString;
        lines[2] = artistCountString;

        setOutput (output, lines, 3);
        writeQuerys (output, cmd);
    }
    closeOutputFile (output);

    deleteHash (artistsTimeInTop);
}
