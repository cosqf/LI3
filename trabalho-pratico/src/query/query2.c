#include <query2.h>
#include <parsingCmd.h>
#include <string.h>
#include <utils.h>
#include <artists.h>
#include <musics.h>
#include <stdbool.h>

/*
// printing functions for debugging purposes only: 
void print_hash_table_item(gpointer key, gpointer value, gpointer user_data) {
    int int_key = GPOINTER_TO_INT(key);  
    int int_value = GPOINTER_TO_INT(value); 

    printf("Key: %d, Value: %d\n", int_key, int_value);
}

void print_hash_table(GHashTable *hash_table) {
    printf("Hash table contents:\n");

    g_hash_table_foreach(hash_table, print_hash_table_item, NULL);
}

void query2(CMD *cmd) {
//    printf ("Starting query2\n"); // DEBUG
    GHashTable *hashDuration = g_hash_table_new (g_direct_hash, g_direct_equal); // temporary hash table 
    GHashTableIter iter;
    gpointer key, value;
    char* country = getCMDCountry(cmd);

//    printf ("HT created\n"); // DEBUG
    g_hash_table_iter_init(&iter, hashMusic);
//    printf ("Initializing iteration\n"); // DEBUG

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        // Reading from Music Hash
        Music* music = (Music*) value;
        int duration = durationInSeconds(getMusicDuration (music));
        int* ids = getMusicArtistID (music);
        int idsCounter = getMusicArtistIDCount (music);

//        printf ("Read from music hash. duration: %ds, %d number of ids, ids: ", duration, idsCounter); // DEBUG

//        for (int i=0; i<idsCounter && ids[i]; i++) printf ("%d; ", ids[i]); // DEBUG
//        printf ("\n"); // DEBUG

        //Insert the duration of an artist's discography in the new hashtable, using the id as key
        insertArtistsHash (ids, idsCounter, hashDuration, duration, country);

//        printf ("Artist inserted in the table.\n"); // DEBUG
        
        free (ids);

//        print_hash_table (hashDuration); // DEBUG
//        printf ("End loop\n\n"); // DEBUG
    }       
    g_hash_table_destroy(hashDuration);
    free (country);
}



void insertArtistsHash (int* id, int count, GHashTable* newtable, int duration, char* country) {
    for (int i=0; i<count; i++) {
        Artist* artist = g_hash_table_lookup (hashArtist, GINT_TO_POINTER(id[i]));    // ERROR. READING MUSIC FILE INSTEAD FOR SOME REASON
        if (artist == NULL) continue;

        printArtist (artist);
        if (country!= NULL) {  // country filter is active
            char* countryArtist = getArtistCountry (artist);
            if (strcmp (country, countryArtist) != 0) {
                free (countryArtist);
                continue;
            }
            free (countryArtist);
        }

        if (checkIfAlreadyInHashTable (id[i], newtable)) updateDurationHash (id[i], newtable, duration);

        else g_hash_table_insert (newtable, GINT_TO_POINTER(id[i]), GINT_TO_POINTER(duration));       
    }
}



void updateDurationHash (int id, GHashTable* newtable, int duration) {
    int value = GPOINTER_TO_INT (g_hash_table_lookup(newtable, GINT_TO_POINTER(id)));
    value += duration;
    g_hash_table_insert (newtable, GINT_TO_POINTER(id), GINT_TO_POINTER(value));
}
*/