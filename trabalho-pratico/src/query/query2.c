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
} FeederData;


void query2(CMD *cmd, hashtableManager *mngr, int cmdCounter) {
    GHashTable *hashDuration = createHash(); // temporary hash table 
    char* country = getCMDCountry(cmd);
    FeederData data = { 
        data.country = country, 
        data.hashDuration = hashDuration, 
        data.artistManager = getArtistManager(mngr) 
        };

    // will iterate the hashtable and get the artists discography
    iterateMusic(getMusicManager(mngr), feeder, &data); 

    Tuple* hashArray = sortHash (hashDuration, compareTuple);
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
        Duration dur = secondsInDuration (hashArray[i].value);
        printResult (cmd, artist, dur, output);
        deleteArtist (artist);
    }
    closeOutputFile (output);
    free (filePath);
    free (hashArray);
    free (country);
    deleteHash(hashDuration);
}


// Will feed getArtistsDiscography
void feeder(gpointer value, gpointer music_data) {
    Music* music = (Music*) value;

    // Extracting data from music_data
    FeederData* data = (FeederData*) music_data;

    char* countryFilter = data->country;
    GHashTable* hashDuration = data->hashDuration;
    ArtistManager* a_mngr = data->artistManager;

    // Extracting data from value
    int duration = durationInSeconds (getMusicDuration (music));
    const int* ids = getMusicArtistID (music);
    int idsCounter = getMusicArtistIDCount (music);

    getArtistsDiscography(ids, idsCounter, hashDuration, duration, countryFilter, a_mngr);
}

// Inserts the duration of an artist's discography in the new hashtable, using the id as key
void getArtistsDiscography (const int* id, int count, GHashTable* newtable, int duration, char* country, ArtistManager *a_mngr) {
    for (int i = 0; i < count; i++) {
        if (country != NULL) {  // country filter is active
            char* countryArtist = lookupArtistCountryHash (a_mngr, id[i]);
            if (strcmp (country, countryArtist) != 0) {
                free (countryArtist);
                continue;
            }
            free (countryArtist);
        }
        updateHash (id[i], newtable, duration);
    }
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

char* getPathFileToQuery2 (int i) {
    int required_size = 31 + 2 + 1; // characters + number + terminator

    char* fullpath = malloc(required_size);
    if (mallocErrorCheck (fullpath)) exit(EXIT_FAILURE);

    snprintf(fullpath, required_size, "resultados/command%d_output.txt", i);
    
    return fullpath;
}