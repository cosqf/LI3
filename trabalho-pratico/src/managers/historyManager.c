#include <glib.h>
#include <output_handling/errorfiles.h>
#include <history.h>
#include <validateDatatypes.h>
#include <historyManager.h>
#include <parsing.h>
#include <utils.h>

typedef struct historyManager {
    GHashTable *history;
    GTree* historyInWeeks; // will only have the top 10 artists of each week, key: first day of the week, value: array with artists and duration
} HistoryManager;


void insertHistoryHash (HistoryManager *h_mngr, int key, History *history) {
    g_hash_table_insert(h_mngr->history, GINT_TO_POINTER (key), history);
}

int lengthHistory (HistoryManager* mngr) {
    return g_hash_table_size(mngr->history);
}

// tree

gint compareDateGlib(const void* a, const void* b) {
    const Date* dateA = (const Date*)a;
    const Date* dateB = (const Date*)b;

    if (dateA->year > dateB->year) return -1; 
    if (dateA->year < dateB->year) return 1;
    if (dateA->month > dateB->month) return -1;
    if (dateA->month < dateB->month) return 1;
    if (dateA->day > dateB->day) return -1;
    if (dateA->day < dateB->day) return 1;

    return 0;
}

GTree* initializeHistoryTree() {
    return g_tree_new((GCompareFunc)compareDateGlib);
}

void insertInHistoryWeeks (HistoryManager* mngr, void* top10artistWeek, Date firstDayOfWeek) {
    Date* key = malloc(sizeof(Date));
    *key = firstDayOfWeek; // a copy

    g_tree_insert (mngr->historyInWeeks, key, top10artistWeek);
}

void destroyHistoryWeeks(HistoryManager* mngr) {
    g_tree_destroy(mngr->historyInWeeks);
}

void traverseTreeInRange(HistoryManager* mngr, gboolean callback(gpointer key, gpointer value, gpointer user_data), gpointer feeder) {
    GTree* tree = mngr->historyInWeeks;
    g_tree_foreach(tree, callback, feeder);
}


void getDataHistory (char *path, HistoryManager* mngr) {
    Output* output = openErrorOutputHistory ();

    parseFile(path, callbackHistory, mngr, output);

    closeOutputFile (output); 
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
    History* historyA = (History*) a;
    History* historyB = (History*) b;

    Date dateA = getHistoryTimestamp (historyA);
    Date dateB = getHistoryTimestamp (historyB);

    int c = compareDate (dateA, dateB);

    return c;
}
 
// Transforms the hash table into a History array and sorts it
History** sortHistory (HistoryManager* manager) {
    GHashTable* hash = manager->history;
    GHashTableIter iter;
    gpointer key, value;
    int i = 0;

    int lengthHash = g_hash_table_size (hash);
    History** hashArray = malloc (sizeof (History*) * lengthHash);
    if (mallocErrorCheck (hashArray)) {
        perror ("Malloc error in sortHistory\n");
        return NULL;
    }

    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        hashArray[i] = (History*) value;
        i++;
    }

    qsort (hashArray, lengthHash, sizeof(Tuple), compareTimestamp);

    return hashArray;
}