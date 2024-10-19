#include <query2.h>
#include <parsingCmd.h>
#include <string.h>
#include <utils.h>
#include <artists.h>
#include <musics.h>
#include <stdbool.h>
#include <glib.h>
#include <musicManager.h>
#include <stdlib.h>

typedef struct {
    char* country;
    GHashTable* hashDuration;
    ArtistManager* artistManager;
} FeederData;


void query2(CMD *cmd, EntityManager *mngr) {
    GHashTable *hashDuration = createHash(); // temporary hash table 
    char* country = getCMDCountry(cmd);

    FeederData data = { 
        data.country = country, 
        data.hashDuration = hashDuration, 
        data.artistManager = getArtistManager(mngr) 
        };

    iterateMusic(getMusicManager(mngr), feeder, &data);
    Tuple* hashArray = sortHash (hashDuration);
    if (hashArray == NULL) {
        perror("Sorting Hash error\n");
        deleteHash(hashDuration);
        free(country);
        return;
    }

    int topN = getCMDtopN (cmd);
    int lengthHash = g_hash_table_size (hashDuration);
    int limit;
    if (lengthHash<topN) limit = lengthHash;
    else limit = topN;
    for (int i = limit-1; i>=0; i--) {
        ArtistManager* a_mngr = getArtistManager (mngr);
        Artist* artist = lookupArtistHash (a_mngr, hashArray[i].key);
        Duration dur = secondsInDuration (hashArray[i].duration);
        printf ("%s;%s;%d:%d:%d;%s\n", getArtistName (artist), getArtistTypeString(artist),  // duration format is printing wrong
                                       dur.hours, dur.minutes, dur.seconds,
                                       getArtistCountry(artist));
    }
    
    free (hashArray);
    deleteHash(hashDuration);
    free (country);
    //printf("\n\n\n"); // DEBUG
}


//will feed insertArtistHash
void feeder(gpointer value, gpointer user_data) {
    Music* music = (Music*) value;

    // Extracting data from user_data
    FeederData* data = (FeederData*) user_data;
    char* country = data->country;
    GHashTable* hashDuration = data->hashDuration;
    ArtistManager* a_mngr = data->artistManager;

    // Extracting data from value
    int duration = durationInSeconds(getMusicDuration(music));
    int* ids = getMusicArtistID(music);
    int idsCounter = getMusicArtistIDCount(music);

    getArtistsDiscography(ids, idsCounter, hashDuration, duration, country, a_mngr);
}

//Insert the duration of an artist's discography in the new hashtable, using the id as key
void getArtistsDiscography (int* id, int count, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr) {
    for (int i=0; i<count; i++) {
        
        Artist* artist = lookupArtistHash (a_mngr, id[i]);
        if (artist == NULL) continue;

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

Tuple* sortHash (GHashTable* hash) {
    GHashTableIter iter;
    gpointer key, value;
    int i = 0;

    int lengthHash = g_hash_table_size (hash);
    Tuple* hashArray = malloc (sizeof (Tuple) * lengthHash);
    mallocErrorCheck (hashArray);

    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Tuple data;
        data.key = GPOINTER_TO_INT (key);
        data.duration = GPOINTER_TO_INT (value);

        hashArray[i] = data;
        i++;
    }

    //for (i = 0; i < lengthHash; i++) printf ("before sort: id:%d, duration:%d\n", hashArray[i].key, hashArray[i].duration); // DEBUG

    qsort (hashArray, lengthHash, sizeof(Tuple), compareTuple);

    //for (i = 0; i < lengthHash; i++) printf ("after sort: id:%d, duration:%d\n", hashArray[i].key, hashArray[i].duration); // DEBUG

    return hashArray;
}

int compareTuple(const void* a, const void* b) {
    const Tuple* tupleA = (const Tuple*)a;
    const Tuple* tupleB = (const Tuple*)b;

    if (tupleA->duration < tupleB->duration) return -1;
    if (tupleA->duration > tupleB->duration) return 1;
    return 0;
}


void updateDurationHash(int id, GHashTable* newtable, int duration) {
    gpointer key, value;
    
    if (g_hash_table_lookup_extended(newtable, GINT_TO_POINTER(id), &key, &value)) {
        int newValue = GPOINTER_TO_INT(value);
        newValue += duration;

        g_hash_table_replace(newtable, GINT_TO_POINTER(id), GINT_TO_POINTER(newValue));
    } 
    else g_hash_table_insert(newtable, GINT_TO_POINTER(id), GINT_TO_POINTER(duration));
}

