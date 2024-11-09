#include <query2.h>
#include <parsing.h>
#include <string.h>
#include <utils.h>
#include <artists.h>
#include <musics.h>
#include <stdbool.h>
#include <glib.h>
#include <musicManager.h>
#include <stdlib.h>
#include <output_handling/outputWriter.h>

typedef struct {
    char* country;
    GHashTable* hashDuration;
    ArtistManager* artistManager;
} FeederData;


void query2(CMD *cmd, hashtableManager *mngr, int cmdCounter) {
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
    if (lengthHash < topN) limit = lengthHash;
    else limit = topN;
    
    char* filePath = getPathFileToQuery2 (cmdCounter);
    Output* output = openOutputFile (filePath);
    
    if (limit == 0) writeNewLine(output);
    for (int i = 0; i < limit; i++) {
        ArtistManager* a_mngr = getArtistManager (mngr);
        Artist* artist = lookupArtistHash (a_mngr, hashArray[i].key);
        Duration dur = secondsInDuration (hashArray[i].duration);
        printResult (artist, dur, output);
    }
    closeOutputFile (output);
    free (filePath);
    free (hashArray);
    free (country);
    deleteHash(hashDuration);
}


//will feed insertArtistHash
void feeder(gpointer value, gpointer music_data) {
    Music* music = (Music*) value;

    // Extracting data from music_data
    FeederData* data = (FeederData*) music_data;

    char* country_filter = data->country;
    GHashTable* hashDuration = data->hashDuration;
    ArtistManager* a_mngr = data->artistManager;

    // Extracting data from value
    int duration = durationInSeconds (getMusicDuration (music));
    const int* ids = getMusicArtistID (music);
    int idsCounter = getMusicArtistIDCount (music);

    getArtistsDiscography(ids, idsCounter, hashDuration, duration, country_filter, a_mngr);
}

//Insert the duration of an artist's discography in the new hashtable, using the id as key
void getArtistsDiscography (const int* id, int count, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr) {
    for (int i = 0; i < count; i++) {
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
        updateDurationHash (id[i], newtable, duration);
    }
}
// Transforms the hash table into a Tuple array and sorts it
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

    qsort (hashArray, lengthHash, sizeof(Tuple), compareTuple);

    return hashArray;
}

int compareTuple(const void* a, const void* b) {
    const Tuple* tupleA = (const Tuple*)a;
    const Tuple* tupleB = (const Tuple*)b;

    if (tupleA->duration > tupleB->duration) return -1;  // descending order
    if (tupleA->duration < tupleB->duration) return 1;
    return 0;
}


void updateDurationHash(int id, GHashTable* newtable, int duration) {
    gpointer key, value;
    
    // the artist is already in the new table
    if (g_hash_table_lookup_extended (newtable, GINT_TO_POINTER(id), &key, &value)) {
        int newValue = GPOINTER_TO_INT(value) + duration;
        // update duration
        g_hash_table_replace(newtable, GINT_TO_POINTER(id), GINT_TO_POINTER(newValue));
    }
    // it isnt, so we need to add it
    else g_hash_table_insert(newtable, GINT_TO_POINTER(id), GINT_TO_POINTER(duration));
}

void printResult (Artist* artist, Duration dur, Output* output) {
    char* name = getArtistName (artist);
    bool type = getArtistType(artist);
    char* artist_country = getArtistCountry(artist); 
    char* duration = durationInString (dur);

    char typeString[11];
    if (type) strcpy (typeString, "group");
    else strcpy (typeString, "individual");

    char* lines[10] = {NULL};

    lines[0] = name;
    lines[1] = typeString;
    lines[2] = duration;
    lines[3] = artist_country;

    setOutput (output, lines, 4);
    writeQuerys (output);

    free (name);
    free(artist_country);
    free(duration);
}

char* getPathFileToQuery2 (int i) {
    int required_size = 31 + 2 + 1; // characters + number + terminator

    char* fullpath = malloc(required_size);
    if (mallocErrorCheck (fullpath)) exit(EXIT_FAILURE);

    snprintf(fullpath, required_size, "resultados/command%d_output.txt", i);
    
    return fullpath;
}