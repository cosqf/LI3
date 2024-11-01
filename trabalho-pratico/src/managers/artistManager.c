#include <glib.h>
#include <artists.h>
#include <artistManager.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <utils.h>
#include <validation.h>
#include <validateDatatypes.h>

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

void getDataArtist (char* path, ArtistManager* artistManager) {
    char *artistPath = changePath (path, Artists);

    FILE* fileData = openFile (artistPath);
    FILE* fileError = openErrorFileArtists ();
    char str[DEFAULT];
    if (fgets(str, sizeof(str), fileData) == NULL) { // skip header
        perror ("skipping artist header error");
        exit(EXIT_FAILURE);
    }

    while (fgets (str, sizeof (str), fileData) != NULL) {
        char* tokens[7];
        parseLine(str, tokens, ";");

        Artist* artist = createArtist(tokens);
        if (!validArtist(artist)) {
            insertErrorFileArtists(artist, fileError);
            deleteArtist(artist);
        } else insertArtistHash(artistManager, getArtistID(artist), artist);
        
        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        //Artist *myLookup = (Artist *) g_hash_table_lookup(hashArtist, getArtistID (artist));
        //printf("ID: %d, Nome: %s, Descrição: %s\n", getArtistID (myLookup), getArtistName (myLookup), getArtistDescription (myLookup));
      

        //printArtist (artist);
    }
    fclose(fileData);
    fclose (fileError);
    free (artistPath);
}