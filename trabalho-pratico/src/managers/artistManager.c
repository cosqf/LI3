#include <glib.h>
#include <artists.h>
#include <artistManager.h>
#include <parsingUtils.h>
#include <utils.h>
#include <output_handling/errorfiles.h>
#include <validateDatatypes.h>
#include <parsing.h>

typedef struct artistManager {
    GHashTable *artist;
} ArtistManager;


void insertArtistHash (ArtistManager *a_mngr, int key, Artist *artist) {
    g_hash_table_insert(a_mngr->artist, GINT_TO_POINTER (key), artist);
}

ArtistManager* initializeArtistManager () {
    ArtistManager* a_mngr = malloc (sizeof (ArtistManager));
    if (a_mngr == NULL) {
        perror("Failed to allocate memory for ArtistManager");
        exit(EXIT_FAILURE); 
    }
    a_mngr->artist = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteArtist);
    return a_mngr;
} //g_int instead of g_hash

void freeArtistManager (ArtistManager* a_mngr) {
    g_hash_table_destroy (a_mngr->artist);
    free (a_mngr);
}

Artist* lookupArtistHash (ArtistManager *a_mngr, int id) {
    Artist* artist = g_hash_table_lookup (a_mngr->artist, GINT_TO_POINTER(id));
    return copyArtist (artist);
}

char* lookupArtistCountryHash (ArtistManager *a_mngr, int id) {
    Artist* artist = g_hash_table_lookup (a_mngr->artist, GINT_TO_POINTER(id));
    return getArtistCountry (artist);
}

bool isArtistInHash (ArtistManager *a_mngr, int id) {
    Artist* artist = g_hash_table_lookup (a_mngr->artist, GINT_TO_POINTER(id));
    if (artist == NULL) return 0;
    else return 1;
}

bool isArtistInList (const int* ids, int artistID, int length) {
    for(int i = 0; i < length; i++) {
        if (ids[i] == artistID) return true;
    }
    return false;
}

bool getArtistTypeHash (int id, ArtistManager* mngr) {
    Artist* artist = g_hash_table_lookup (mngr->artist, GINT_TO_POINTER(id));
    if (artist == NULL) return 0;
    return getArtistType (artist);
}

int getDataArtist (char *path, ArtistManager* mngr) {
    Output* output = openErrorOutputArtists ();

    int error = parseFile(path, callbackArtist, mngr, output);
    
    closeOutputFile (output); 

    return error;
}

// creates an artistString according to its tokens and validates them. 
// if valid, its converted to an artist and added to the hashtable
void callbackArtist(char **tokens, void *manager, Output *output) {
    ArtistManager* artistManager = (ArtistManager*) manager;
 
    ArtistString* artistS = createArtistString(tokens);
    if (!validArtist(artistS)) insertErrorFileArtists(artistS, output);
    else {
        Artist* artist = createArtist (tokens);
        insertArtistHash(artistManager, getArtistID(artist), artist);
    }
    deleteArtistString(artistS);

}