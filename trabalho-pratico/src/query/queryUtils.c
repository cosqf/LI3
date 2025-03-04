#include <almightyManager.h>
#include <glib.h>
#include <queryUtils.h>
#include <utils.h>


int compareTuple(const void* a, const void* b) {
    const Tuple* tupleA = (const Tuple*)a;
    const Tuple* tupleB = (const Tuple*)b;

    if (tupleA->value > tupleB->value) return -1;  // descending order
    if (tupleA->value < tupleB->value) return 1;

    if (tupleA->key > tupleB->key) return 1;  // if the values are the same, compare the ids too
    if (tupleA->key < tupleB->key) return -1;   // smaller id first
    return 0;
}

void updateHash(GHashTable* table, int id, int newValue) {
    gpointer value = g_hash_table_lookup(table, GINT_TO_POINTER(id));
    if (value) {     // the artist is already in the new table
        int updatedValue = GPOINTER_TO_INT(value) + newValue;
        g_hash_table_insert(table, GINT_TO_POINTER(id), GINT_TO_POINTER(updatedValue));    }
    else {// it isnt, so we need to add it
        g_hash_table_insert(table, GINT_TO_POINTER(id), GINT_TO_POINTER(newValue));
    }
}

// Transforms the hash table into a Tuple array and sorts it
Tuple* sortHash (GHashTable* hash, int sorterFunc (const void*, const void*)) {
    GHashTableIter iter;
    gpointer key, value;
    int i = 0;

    int lengthHash = g_hash_table_size (hash);
    if (lengthHash <= 0) return NULL;

    Tuple* hashArray = malloc (sizeof (Tuple) * lengthHash);
    if (mallocErrorCheck (hashArray)) {
        perror ("Malloc error in sortHash\n");
        return NULL;
    }

    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Tuple data;
        data.key = GPOINTER_TO_INT (key);
        data.value = GPOINTER_TO_INT (value);

        hashArray[i] = data;
        i++;
    }

    qsort (hashArray, lengthHash, sizeof(Tuple), sorterFunc);

    return hashArray;
}

char* formatUserID (int id) {
    char* formatted = (char*)malloc(9 * sizeof(char));
    sprintf(formatted, "U%07d", id);
    return formatted;
}

Tuple getBiggestFromHash (GHashTable* table) {
    GHashTableIter iter;
    gpointer key, value;
    int maxValues = 0, maxId = -1;
    g_hash_table_iter_init(&iter, table);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        int values = GPOINTER_TO_INT (value);
        int id = GPOINTER_TO_INT (key);
        if (values > maxValues || (values == maxValues && id < maxId)) {
            maxValues = values;
            maxId = id;
        }
    } 
    Tuple result = {.key = maxId, .value = maxValues};
    return result;
}