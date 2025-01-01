#include <glib.h>
#include <output_handling/errorfiles.h>
#include <history.h>
#include <validateDatatypes.h>
#include <historyManager.h>
#include <parsing.h>
#include <utils.h>
#include <query4.h>
#include <query1.h>

#include <time.h>

typedef struct historyManager {
    GHashTable *historyByUser;
    GHashTable *historyByMusic;
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
    h_mngr->historyByUser = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteHistory);
    h_mngr->historyByMusic = g_hash_table_new(g_direct_hash, g_direct_equal);
    h_mngr->historyInWeeks = NULL;
    return h_mngr;
}

void insertHistoryHashByUser(GHashTable *hashtable, int userID, History *history) {
    History* existentHistory = g_hash_table_lookup(hashtable, GINT_TO_POINTER(userID));

    if (existentHistory) setNextHistoryByUser(history, existentHistory);
    
    else g_hash_table_insert(hashtable, GINT_TO_POINTER(userID), history);
}

void insertHistoryHashByMusic(GHashTable *hashtable, int musicID, History *history) {
    History* existentHistory = g_hash_table_lookup(hashtable, GINT_TO_POINTER(musicID));

    if (existentHistory) setNextHistoryByMusic(history, existentHistory);
    
    else g_hash_table_insert(hashtable, GINT_TO_POINTER(musicID), history);
}


void freeHistory (HistoryManager* h_mngr) {
    if(!h_mngr) return;

    g_hash_table_steal_all (h_mngr->historyByMusic);
    g_hash_table_destroy (h_mngr->historyByMusic);
    g_hash_table_destroy (h_mngr->historyByUser);

    if (h_mngr->historyInWeeks) g_tree_destroy(h_mngr->historyInWeeks);
    free (h_mngr);
}

int lengthHistory (HistoryManager* mngr) {
    return g_hash_table_size(mngr->historyByUser);
}

void traverseHistorybyMusic(HistoryManager* mngr, void (callback)(gpointer key, gpointer value, gpointer query_data), gpointer data) {
    GHashTable* historyByMusic = mngr->historyByMusic;
    g_hash_table_foreach(historyByMusic, callback, data);
}

void traverseHistorybyUser(HistoryManager* mngr, void (callback)(gpointer key, gpointer value, gpointer query_data), gpointer data) {
    GHashTable* historyByUser = mngr->historyByUser;
    g_hash_table_foreach(historyByUser, callback, data);
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
        insertHistoryHashByUser(historyManager->historyByUser, getHistoryUserId(history), history);
        insertHistoryHashByMusic(historyManager->historyByMusic, getHistoryMusicId(history), history);
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

// Transforms the hash table into a History array 
int transformHistory (HistoryManager* manager, History*** hashArray) { // hashArray: pointer to an array of History*
    GHashTable* hash = manager->historyByUser;
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
            hist = getNextHistoryByUser (hist);
        }
    }
    return i;
}

void createAndSortTree (HistoryManager* manager, void (processHistory) (History*, MusicManager*, GHashTable*), MusicManager* m_mngr) {
    GHashTable* hashWithWeeks = g_hash_table_new_full(dateHashFunc, dateEqualFunc, (GDestroyNotify) free, (GDestroyNotify) deleteHash);

    //iterate through history
    GHashTable* hash = manager->historyByUser;
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        History* hist = (History*) value;
        while (hist) {
            processHistory (hist, m_mngr, hashWithWeeks);
            hist = getNextHistoryByUser (hist);
        }
    }

    filterToTree (manager, hashWithWeeks);
    g_hash_table_destroy (hashWithWeeks);
}

// will create a tree in historyManager with the data from treeWithHashes
void filterToTree (HistoryManager* mngr, GHashTable* hash) {
    initializeHistoryTree (mngr);
    GHashTableIter iter;
    gpointer key, value;
    
    g_hash_table_iter_init(&iter, hash);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        GHashTable* table = (GHashTable*) value;
        int tupleCount = g_hash_table_size (table);
        int limit = (tupleCount < 10) ? tupleCount : 10;

        Tuple* artistsWeek = sortHash (table, compareTuple);

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
        // get only the top 10 artists
        for (int i = 0; i< limit; i++) limitedArray[i] = artistsWeek [i].key;
        free(artistsWeek);

        top10artistWeek->artistsIds = limitedArray;
        top10artistWeek->count = limit;

        Date* dateKeyCopy = malloc(sizeof(Date));
        if (mallocErrorCheck (dateKeyCopy)) {
            freeArtistList (top10artistWeek);
            return;
        }
        *dateKeyCopy = *(Date*) key;
        g_tree_insert (mngr->historyInWeeks, dateKeyCopy, top10artistWeek);
    }
}
