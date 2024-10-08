#include "hashtable.h"

GHashTable *hashUser = NULL;

void initialize_hash_table() { 
    hashUser = g_hash_table_new(g_int_hash, g_int_equal);
}
