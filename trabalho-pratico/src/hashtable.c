#include "hashtable.h"

GHashTable *hashUser = NULL;
GHashTable *hashArtist = NULL;

void initialize_hash_table() { 
    hashUser = g_hash_table_new(g_direct_hash, g_direct_equal);
    hashArtist = g_hash_table_new(g_direct_hash, g_direct_equal);
}
