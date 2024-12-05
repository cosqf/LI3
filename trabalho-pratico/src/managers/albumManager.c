#include <glib.h>
#include <album.h>
#include <albumManager.h>
#include <parsingUtils.h>
#include <utils.h>
#include <errorfiles.h>
#include <validateDatatypes.h>
#include <outputWriter.h>
#include <parsing.h>
#include <query1.h>

typedef struct albumManager {
    GHashTable *album;
} AlbumManager;


void insertAlbumHash (AlbumManager *al_mngr, int key, Album *album) {
    g_hash_table_insert(al_mngr->album, GINT_TO_POINTER (key), album);
}

AlbumManager* initializeHashAlbum () {
    AlbumManager* al_mngr = malloc (sizeof (AlbumManager));
    if (al_mngr == NULL) {
        perror("Failed to allocate memory for AlbumManager");
        exit(EXIT_FAILURE); 
    }
    al_mngr->album = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteAlbum);
    return al_mngr;
}

void freeHashAlbum (AlbumManager* al_mngr) {
    g_hash_table_destroy (al_mngr->album);
    free (al_mngr);
}

bool isAlbumInHash (AlbumManager *al_mngr, int id) {
    Album* album = g_hash_table_lookup (al_mngr->album, GINT_TO_POINTER(id));
    if (album == NULL) return 0;
    else return 1;
}

void albumCountArtist(int artistID, AlbumManager* al_mngr, int* count) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, al_mngr->album);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        int artistCount = getAlbumArtistIdCount(value);
        int* artistIDList = getAlbumArtistId(value);

        if (isArtistInList(artistIDList, artistID, artistCount)) (*count)++;
    }
}

int getDataAlbum (char* path, hashtableManager* mngr) {
    Output* output = openErrorOutputAlbum ();
    int error = parseFile(path, callbackAlbum, mngr, output);
    closeOutputFile (output); 
    return error;
}

// creates an albumString according to its tokens and validates them. 
// if valid, its converted to an album and added to the hashtable
void callbackAlbum(char** tokens, void* manager, Output* output) {
    hashtableManager* mngr = (hashtableManager*) manager;
    AlbumManager* al_mngr = getAlbumManager(mngr);
    ArtistManager* a_mngr = getArtistManager(mngr);
 
    AlbumString* albumS = createAlbumString(tokens);
    if (!validAlbum(albumS, a_mngr)) insertErrorFileAlbum(albumS, output);
    else {
        Album* album = createAlbum (tokens);
        insertAlbumHash(al_mngr, getAlbumId(album), album);
    }
    deleteAlbumString(albumS);

}
