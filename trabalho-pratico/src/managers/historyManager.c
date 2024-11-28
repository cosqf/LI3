#include <glib.h>
#include <output_handling/errorfiles.h>
#include <history.h>
#include <validateDatatypes.h>
#include <historyManager.h>
#include <parsing.h>

typedef struct historyManager {
    GHashTable *history;
    GHashTable** query4;
} HistoryManager;


void insertHistoryHash (HistoryManager *h_mngr, int key, History *history) {
    g_hash_table_insert(h_mngr->history, GINT_TO_POINTER (key), history);
}

HistoryManager* initializeHashHistory () {
    HistoryManager* h_mngr = malloc (sizeof (HistoryManager));
    if (h_mngr == NULL) {
        perror("Failed to allocate memory for HistoryManager");
        exit(EXIT_FAILURE); 
    }
    h_mngr->history = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteHistory);
    return h_mngr;
}

void freeHashHistory (HistoryManager* h_mngr) {
    g_hash_table_destroy (h_mngr->history);
    free (h_mngr);
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