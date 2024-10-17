#include <query2.h>
#include <parsingCmd.h>
#include <string.h>
#include <utils.h>
#include <artists.h>
#include <musics.h>
#include <stdbool.h>
#include <glib.h>
#include <musicManager.h>


void query2(CMD *cmd, EntityManager *mngr) {
//    printf ("Starting query2\n"); // DEBUG
    GHashTable *hashDuration = createHash(); // temporary hash table 
    char* country = getCMDCountry(cmd);
//    printf ("HT created\n"); // DEBUG

    FeederData data = { 
        data.country = country, 
        data.hashDuration = hashDuration, 
        data.artistManager = getArtistManager(mngr) 
        };

    iterateMusic(getMusicManager(mngr), feeder, &data);

   
    deleteHash(hashDuration);
    free (country);
}

/*
    g_hash_table_iter_init(&iter, getMusicManager (mngr));

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        // Reading from Music Hash
        

//        printf ("Read from music hash. duration: %ds, %d number of ids, ids: ", duration, idsCounter); // DEBUG

//        for (int i=0; i<idsCounter && ids[i]; i++) printf ("%d; ", ids[i]); // DEBUG
//        printf ("\n"); // DEBUG

        
        

//        printf ("Artist inserted in the table.\n"); // DEBUG
        
        free (ids);

//        print_hash_table (hashDuration); // DEBUG
//        printf ("End loop\n\n"); // DEBUG
    }    
*/

//will feed insertArtistHash
void feeder(gpointer value, gpointer user_data) {
    Music* music = (Music*) value;

    // Extract data from user_data
    FeederData* data = (FeederData*) user_data;
    char* country = data->country;
    GHashTable* hashDuration = data->hashDuration;
    ArtistManager* a_mngr = data->artistManager;

    int duration = durationInSeconds(getMusicDuration(music));
    int* ids = getMusicArtistID(music);
    int idsCounter = getMusicArtistIDCount(music);

    getArtistsDiscography(ids, idsCounter, hashDuration, duration, country, a_mngr);
}

//Insert the duration of an artist's discography in the new hashtable, using the id as key
void getArtistsDiscography (int* id, int count, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr) {
    for (int i=0; i<count; i++) {
        
        Artist* artist = lookupArtistHash (a_mngr, id[i]);    // ERROR. READING MUSIC FILE INSTEAD FOR SOME REASON
        if (artist == NULL) continue;

        //printArtist (artist); // DEBUG
        if (country!= NULL) {  // country filter is active
            char* countryArtist = getArtistCountry (artist);
            if (strcmp (country, countryArtist) != 0) {
                free (countryArtist);
                continue;
            }
            free (countryArtist);
        }

        if (checkIfAlreadyInHashTable (id[i], newtable)) updateDurationHash (id[i], newtable, duration);
        
        else insertHash (newtable, id[i], duration);       
    }
}



void updateDurationHash (int id, GHashTable* newtable, int duration) {
    int value = GPOINTER_TO_INT (g_hash_table_lookup(newtable, GINT_TO_POINTER(id)));
    value += duration;
    g_hash_table_insert (newtable, GINT_TO_POINTER(id), GINT_TO_POINTER(value));
}
