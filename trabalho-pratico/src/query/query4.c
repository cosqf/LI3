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
#include <time.h>


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


void getHistoryByWeeks2 (HistoryManager* historyManager, MusicManager* musicManager) {
    // setting up array
    int lengthHash = lengthHistory (historyManager);
    History** array = malloc (sizeof (History*) * lengthHash);
    if (mallocErrorCheck (array)) return;
    int lengthArray = sortHistory(historyManager, &array);
    if (lengthArray <= 0) {
        perror ("Empty history\n");
        return;
    }
    GHashTable* hashWithWeeks = g_hash_table_new_full(dateHashFunc, dateEqualFunc, (GDestroyNotify) free, (GDestroyNotify) deleteHash);

    for (int i = 0; i < lengthArray; i++) {
        History* hist = array[i];
        Date date = (getHistoryTimestamp (hist)).date;
        adjustDateLimits (&date, 0); // get last sunday
        
        int musicId = getHistoryMusicId(hist);
        int* artistIds;
        int artistCount = lookupMusicArtistIDsHash (musicManager, musicId, &artistIds);
        
        for (int j = 0; j < artistCount; j++) {
            Tuple tuple = {.key = artistIds[j], .value = durationInSeconds (getHistoryDuration(hist))};
            updateHashWithWeeks (hashWithWeeks, date, tuple);
        }
        free (artistIds);
    }
    free (array);
    // will create a tree in historyManager with the data from treeWithHashes
    filterToTree (historyManager, hashWithWeeks);

    g_hash_table_destroy (hashWithWeeks);
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
        //initializeHistoryTree(historyManager);
        getHistoryByWeeks2 (historyManager, musicManager); 
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

    // outputting
    char filename[50];
    snprintf (filename, sizeof(filename),"resultados/command%d_output.txt", cmdCounter);
    Output* output = openOutputFile (filename);

    Tuple* array = sortHash (artistsTimeInTop, compareTuple);
 
    if (array == NULL) writeNewLine(output);
    else {
        int artistId = array[0].key;
        int artistCount = array[0].value;

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

    free (array);
    deleteHash (artistsTimeInTop);
}
