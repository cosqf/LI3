#include <glib.h>
#include <output_handling/errorfiles.h>
#include <history.h>
#include <validateDatatypes.h>
#include <historyManager.h>
#include <parsing.h>
#include <utils.h>
#include <query4.h>
#include <time.h>

typedef struct historyManager {
    GHashTable *history;
    GTree* historyInWeeks; // will only have the top 10 artists of each week, key: first day of the week, value: array with artists and duration
} HistoryManager;


// tree

gint compareDateGlib(const void* a, const void* b, gpointer user_data) {
    (void) user_data;
    const Date* dateA = (const Date*)a;
    const Date* dateB = (const Date*)b;

    if (dateA->year > dateB->year) return 1; 
    if (dateA->year < dateB->year) return -1;
    if (dateA->month > dateB->month) return 1;
    if (dateA->month < dateB->month) return -1;
    if (dateA->day > dateB->day) return 1;
    if (dateA->day < dateB->day) return -1;

    return 0;
}

void initializeHistoryTree(HistoryManager* mngr ) {
    mngr->historyInWeeks = g_tree_new_full (compareDateGlib, NULL, (GDestroyNotify) free, (GDestroyNotify) freeArtistList);
}

bool historyTreeIsInitialized (HistoryManager* mngr) {
    if (mngr->historyInWeeks) return 1;
    else return 0;
}

void insertInHistoryByWeeks (HistoryManager* mngr, Date firstDayOfWeek, void* top10artistWeek) {
    Date* key = malloc(sizeof(Date));
        if (mallocErrorCheck (key)) return;   
    *key = firstDayOfWeek; // a copy

    g_tree_insert (mngr->historyInWeeks, key, top10artistWeek);
}

void traverseTree(HistoryManager* mngr, gboolean callback(gpointer key, gpointer value, gpointer user_data), gpointer feeder) {
    GTree* tree = mngr->historyInWeeks;
    g_tree_foreach(tree, callback, feeder);
}

// hash 

HistoryManager* initializeHashHistory () {
    HistoryManager* h_mngr = malloc (sizeof (HistoryManager));
    if (h_mngr == NULL) {
        perror("Failed to allocate memory for HistoryManager");
        exit(EXIT_FAILURE); 
    }
    h_mngr->history = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteHistory);
    h_mngr->historyInWeeks = NULL;
    return h_mngr;
}

void insertHistoryHash(HistoryManager *h_mngr, int key, History *history) {
    History* existentHistory = g_hash_table_lookup(h_mngr->history, GINT_TO_POINTER(key));

    if (existentHistory) setNextHistory(history, existentHistory);
    else g_hash_table_insert(h_mngr->history, GINT_TO_POINTER(key), history);
}

void freeHistory (HistoryManager* h_mngr) {
    if(!h_mngr) return;
    g_hash_table_destroy (h_mngr->history);
    if (h_mngr->historyInWeeks) g_tree_destroy(h_mngr->historyInWeeks);
    free (h_mngr);
}

int lengthHistory (HistoryManager* mngr) {
    return g_hash_table_size(mngr->history);
}


// get data

int getDataHistory (char *path, HistoryManager* mngr) {
    Output* output = openErrorOutputHistory ();

    int error = parseFile(path, callbackHistory, mngr, output);

    closeOutputFile (output); 
    
    return error;
}


// creates an historyString according to its tokens and validates them. 
// if valid, its converted to an history and adds to the hashtable using user id as key
void callbackHistory(char **tokens, void *manager, Output *output) {
    HistoryManager* historyManager = (HistoryManager*) manager;
 
    HistoryString* historyS = createHistoryString(tokens);
    if (!validHistory(historyS)) insertErrorFileHistory(historyS, output);
    else {
        History* history = createHistory (tokens);
        insertHistoryHash(historyManager, getHistoryUserId(history), history);
    }
    deleteHistoryString(historyS);
}

int compareTimestamp(const void* a, const void* b) {
    History* historyA = *(History**)a; // need to dereference due to qsort
    History* historyB = *(History**)b;

    Date dateA = (getHistoryTimestamp (historyA)).date;
    Date dateB = (getHistoryTimestamp (historyB)).date;

    int c = compareDate (dateA, dateB);
    
    return c;
}

// Transforms the hash table into a History array and sorts it
int sortHistory (HistoryManager* manager, History*** hashArray) { // hashArray: pointer to an array of History*
    GHashTable* hash = manager->history;
    GHashTableIter iter;
    gpointer key, value;
    int i = 0;

    int lengthHash = g_hash_table_size (hash);
    
    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        History* hist = (History*) value;
        while (hist) {
            if (i >= lengthHash) {
                lengthHash *= 2;
                History** temp = realloc (*hashArray, sizeof(History*) * lengthHash);
                if (mallocErrorCheck (temp)) {
                    free (*hashArray);
                    return -1;
                }
                *hashArray = temp;
            }
            (*hashArray)[i++] = hist;
            hist = getNextHistory (hist);
        }
    }

    qsort (*hashArray, i, sizeof(History*), compareTimestamp);
    return i;
}

void insertInHistoryByWeeks2 (GTree* tree, Date firstDayOfWeek, GHashTable* artist) {
    Date* key = malloc(sizeof(Date));
        if (mallocErrorCheck (key)) return;   
    *key = firstDayOfWeek; // a copy

    g_tree_insert (tree, key, artist);
}

void filterToTree (HistoryManager* mngr, GHashTable* hash) {
    initializeHistoryTree (mngr);
    GHashTableIter iter;
    gpointer key, value;
    printf ("size of hash: %d\n", g_hash_table_size (hash));
    g_hash_table_iter_init(&iter, hash);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        GHashTable* table = (GHashTable*) value;
        int tupleCount = g_hash_table_size (table);
        Tuple* artistsWeek = sortHash (table, compareTuple);

        ArtistList* top10artistWeek = malloc(sizeof(ArtistList));
            if (mallocErrorCheck (top10artistWeek)) {
                free (artistsWeek);
                return;
            }
        int* limitedArray = malloc (sizeof (Tuple) * tupleCount);
            if (mallocErrorCheck (limitedArray)) {
                free (artistsWeek);
                free (top10artistWeek);
                return;
            }
        // get only the top 10 artists
        int limit = (tupleCount < 10) ? tupleCount : 10;
        for (int i = 0; i< limit; i++) limitedArray[i] = artistsWeek [i].key;
        free(artistsWeek);

        top10artistWeek->artistsIds = limitedArray;
        top10artistWeek->count = limit;

        Date* dateKey = (Date*) key;
        Date* dateKeyCopy = malloc(sizeof(Date));
        if (mallocErrorCheck (dateKeyCopy)) {
                free (top10artistWeek);
                return;
            }
        *dateKeyCopy = *dateKey;
        g_tree_insert (mngr->historyInWeeks, dateKeyCopy, top10artistWeek);
    }
}

// Callback function for g_hash_table_foreach
void printKeyValue(gpointer key, gpointer value, gpointer user_data) {
    (void) user_data;
    int id = GPOINTER_TO_INT(key);      // Convert key back to int
    int seconds = GPOINTER_TO_INT(value); // Convert value back to int

    printf("ID: %d, Seconds: %d\n", id, seconds);
}

void printHash(GHashTable* hash) {
    if (!hash) {
        printf("Hash table is NULL.\n");
        return;
    }
    printf("---- Hash Table Contents ----\n");
    g_hash_table_foreach(hash, printKeyValue, NULL);  // Iterate and print each key-value pair
    printf("-----------------------------\n");
}
