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
#include <queryUtils.h>
#include <output_handling/outputWriter.h>

typedef struct {
    char* country;
    GHashTable* hashDuration;
    ArtistManager* artistManager;
    Tuple* top10Sorted;
} FeederData;


void query2(CMD *cmd, AlmightyManager *mngr, int cmdCounter) {
    GHashTable *hashDuration = createHash(); // temporary hash table 
    char* country = getCMDCountry(cmd);
    Tuple top10Sorted[10];
    for (int i = 0; i<10; i++) top10Sorted[i].key = -1, top10Sorted[i].value = 0;

    FeederData data = { 
        data.country = country, 
        data.hashDuration = hashDuration, 
        data.artistManager = getArtistManager(mngr),
        data.top10Sorted = top10Sorted
        };

    iterateMusic(getMusicManager(mngr), feeder, &data); 

    int topN = getCMDtopN (cmd);
    int lengthHash = g_hash_table_size (hashDuration);
    int limit = lengthHash < topN ? lengthHash : topN;

    char filePath[50];
    snprintf (filePath, sizeof(filePath),"resultados/command%d_output.txt", cmdCounter);
    Output* output = openOutputFile (filePath);
    
    if (limit == 0) writeNewLine(output);
    for (int i = 0; i < limit; i++) {
        if (top10Sorted[i].key == -1) break;
        ArtistManager* a_mngr = getArtistManager (mngr);
        Artist* artist = lookupArtistHash (a_mngr, top10Sorted[i].key);
        Duration dur = secondsInDuration (top10Sorted[i].value);
        printResult (cmd, artist, dur, output);
        deleteArtist (artist);
    }
    closeOutputFile (output);
    free (country);
    deleteHash(hashDuration);
}


// Will feed getArtistsDiscography
void feeder(gpointer key, gpointer value, gpointer music_data) {
    (void) key;
    Music* music = (Music*) value;

    // Extracting data from music_data
    FeederData* data = (FeederData*) music_data;

    char* countryFilter = data->country;
    GHashTable* hashDuration = data->hashDuration;
    ArtistManager* a_mngr = data->artistManager;
    Tuple* top10Sorted = data->top10Sorted;
    int minDuration = 0;
    // Extracting data from value
    int duration = durationInSeconds (getMusicDuration (music));
    const int* ids = getMusicArtistID (music);
    int idsCounter = getMusicArtistIDCount (music);
    for (int i = 0; i<idsCounter; i++) {
        getArtistsDiscography(ids[i], hashDuration, duration, countryFilter, a_mngr, top10Sorted, &minDuration);
    }
}

void updateSortedArray(GHashTable* table, int id, Tuple* top10Sorted, int* minDuration) {
    int duration = GPOINTER_TO_INT (g_hash_table_lookup(table, GINT_TO_POINTER(id)));
    if (duration < *minDuration) return; //early exit

    for (int i = 0; i < 10; i++) {
        if (top10Sorted[i].key == id) {     // check if the id already exists and update
            top10Sorted[i].value = duration;
            
            for (int j = i; j > 0 &&                                         //resorting
                          (top10Sorted[j-1].value < top10Sorted[j].value ||
                          (top10Sorted[j-1].value == top10Sorted[j].value && 
                          top10Sorted[j-1].key > top10Sorted[j].key)); j--) {
                Tuple temp = top10Sorted[j];
                top10Sorted[j] = top10Sorted[j-1];
                top10Sorted[j-1] = temp;
            }
            *minDuration = top10Sorted[9].value;
            return;
        }
    }
    for (int i = 0; i<10; i++){
        // check if the duration is bigger
        if (top10Sorted[i].value < duration || 
            (top10Sorted[i].value == duration && top10Sorted[i].key > id)) {
            for (int j = 9; j > i; j--) top10Sorted[j] = top10Sorted[j-1]; // shift elements
            top10Sorted[i].key = id;
            top10Sorted[i].value = duration;
            *minDuration = top10Sorted[9].value;
            return;
        }
    }
}


// Inserts the duration of an artist's discography in the new hashtable, using the id as key
void getArtistsDiscography (int id, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr, Tuple* top10Sorted, int* minDuration) {
    if (country != NULL) {  // country filter is active
        char* countryArtist = lookupArtistCountryHash (a_mngr, id);
        if (strcmp (country, countryArtist) != 0) {
            free (countryArtist);
            return;
        }
        free (countryArtist);
    }
    updateHash (newtable, id, duration);
    updateSortedArray (newtable, id, top10Sorted, minDuration);
}

void printResult (CMD* cmd, Artist* artist, Duration dur, Output* output) {
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
    writeQuerys (output, cmd);

    free (name);
    free(artist_country);
    free(duration);
}