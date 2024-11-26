#include <hashtableManager.h>
#include <glib.h>
#include <queryUtils.h>

int compareTuple(const void* a, const void* b) {
    const Tuple* tupleA = (const Tuple*)a;
    const Tuple* tupleB = (const Tuple*)b;

    if (tupleA->duration > tupleB->duration) return -1;  // descending order
    if (tupleA->duration < tupleB->duration) return 1;
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
