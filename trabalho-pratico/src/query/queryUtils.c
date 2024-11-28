#include <hashtableManager.h>
#include <glib.h>
#include <queryUtils.h>
#include <utils.h>


int compareTuple(const void* a, const void* b) {
    const Tuple* tupleA = (const Tuple*)a;
    const Tuple* tupleB = (const Tuple*)b;

    if (tupleA->value > tupleB->value) return -1;  // descending order
    if (tupleA->value < tupleB->value) return 1;
    return 0;
}

void updateHash(int id, GHashTable* newtable, int newValue) {
    gpointer key, value;
    
    // the artist is already in the new table
    if (g_hash_table_lookup_extended (newtable, GINT_TO_POINTER(id), &key, &value)) {
        int updatedValue = GPOINTER_TO_INT(value) + newValue;
        // update newValue
        g_hash_table_replace(newtable, GINT_TO_POINTER(id), GINT_TO_POINTER(updatedValue));
    }
    // it isnt, so we need to add it
    else g_hash_table_insert(newtable, GINT_TO_POINTER(id), GINT_TO_POINTER(newValue));
}

// Transforms the hash table into a Tuple array and sorts it
Tuple* sortHash (GHashTable* hash, int sorterFunc (const void*, const void*)) {
    GHashTableIter iter;
    gpointer key, value;
    int i = 0;

    int lengthHash = g_hash_table_size (hash);
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
