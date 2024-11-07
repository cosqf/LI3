#include <glib.h>
#include <artists.h>
#include <artistManager.h>
#include <parsingUtils.h>
#include <utils.h>
#include <validation.h>
#include <validateDatatypes.h>
#include <parsing.h>

typedef struct artistManager {
    GHashTable *artist;
} ArtistManager;


void insertArtistHash (ArtistManager *a_mngr, int key, Artist *artist) {
    g_hash_table_insert(a_mngr->artist, GINT_TO_POINTER (key), artist);
}

ArtistManager* initializeHashArtist () {
    ArtistManager* a_mngr = malloc (sizeof (ArtistManager));
    if (a_mngr == NULL) {
        perror("Failed to allocate memory for ArtistManager");
        exit(EXIT_FAILURE); 
    }
    a_mngr->artist = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteArtist);
    return a_mngr;
}

void freeHashArtist (ArtistManager* a_mngr) {
    g_hash_table_destroy (a_mngr->artist);
    free (a_mngr);
}

Artist* lookupArtistHash (ArtistManager *a_mngr, int id) {
    Artist* artist = g_hash_table_lookup (a_mngr->artist, GINT_TO_POINTER(id));
    return artist;
}

GHashTable* getArtistTable (ArtistManager *a_mngr) {
    return a_mngr->artist;
}


void getDataArtist (char *path, ArtistManager* mngr) {
    FILE *errorFileArtist = openErrorFileArtists();

    parseFile(path, callbackArtist, mngr, errorFileArtist);

    fclose(errorFileArtist); 
}

void callbackArtist(char **tokens, void *manager, FILE *errorFile) {
    ArtistManager* artistManager = (ArtistManager*) manager;
 
    ArtistString* artistS = createArtistString(tokens);
    if (!validArtist(artistS)) insertErrorFileArtists(artistS, errorFile);
    else {
        Artist* artist = createArtist (tokens);
        insertArtistHash(artistManager, getArtistID(artist), artist);
    }
    deleteArtistString(artistS);

}