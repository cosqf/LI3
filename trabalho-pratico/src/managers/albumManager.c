#include <glib.h>
#include <album.h>
#include <albumManager.h>
#include <parsingUtils.h>
#include <utils.h>
#include <errorfiles.h>
#include <validateDatatypes.h>
#include <outputWriter.h>
#include <parsing.h>

typedef struct albumManager {
    GHashTable *album;
} AlbumManager;


void insertAlbumHash (AlbumManager *a_mngr, int key, Album *album) {
    g_hash_table_insert(a_mngr->album, GINT_TO_POINTER (key), album);
}

AlbumManager* initializeHashAlbum () {
    AlbumManager* a_mngr = malloc (sizeof (AlbumManager));
    if (a_mngr == NULL) {
        perror("Failed to allocate memory for AlbumManager");
        exit(EXIT_FAILURE); 
    }
    a_mngr->album = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteAlbum);
    return a_mngr;
}

void freeHashAlbum (AlbumManager* a_mngr) {
    g_hash_table_destroy (a_mngr->album);
    free (a_mngr);
}

bool isAlbumInHash (AlbumManager *a_mngr, int id) {
    Album* album = g_hash_table_lookup (a_mngr->album, GINT_TO_POINTER(id));
    if (album == NULL) return 0;
    else return 1;
}

void getDataAlbum (char *path, AlbumManager* mngr) {
    Output* output = openErrorOutputAlbums ();

    parseFile(path, callbackAlbum, mngr, output);

    closeOutputFile (output); 
}

// creates an albumString according to its tokens and validates them. 
// if valid, its converted to an album and added to the hashtable
void callbackAlbum(char **tokens, void *manager, Output *output) {
    hashtableManager* mngr = (hashtableManager*) manager;
    AlbumManager* al_mngr = getAlbumManager(mngr);
    ArtistManager* a_mngr = getArtistManager(mngr);
 
    AlbumString* albumS = createAlbumString(tokens);
    if (!validAlbum(albumS, al_mngr, a_mngr)) insertErrorFileAlbums(albumS, output);
    else {
        Album* album = createAlbum (tokens);
        insertAlbumHash(al_mngr, getAlbumID(album), album);
    }
    deleteAlbumString(albumS);

}