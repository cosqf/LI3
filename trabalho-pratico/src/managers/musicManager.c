#include <glib.h>
#include <musicManager.h>
#include <musics.h>
#include <artistManager.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <stdlib.h>
#include <utils.h>
#include <output_handling/errorfiles.h>
#include <validateDatatypes.h>

//mudar nomes

typedef struct musicManager {
    GHashTable *music;
} MusicManager;

void insertMusicHash (MusicManager *m_mngr, int key, Music *Music) {
    g_hash_table_insert(m_mngr->music, GINT_TO_POINTER (key), Music);
}

MusicManager* initializeMusicManager () {
    MusicManager* m_mngr = malloc (sizeof (MusicManager));
    if (m_mngr == NULL) {
        perror("Failed to allocate memory for MusicManager");
        exit(EXIT_FAILURE); 
    }
    m_mngr->music = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify) deleteMusic);
    return m_mngr;
}

void freeMusicManager (MusicManager* m_mngr) {
    g_hash_table_destroy (m_mngr->music);
    free (m_mngr);
}

bool isMusicInHash (MusicManager *m_mngr, int id) {
    Music* music = g_hash_table_lookup (m_mngr->music, GINT_TO_POINTER(id));
    if (music == NULL) return 0;
    else return 1;
}

Genre lookupMusicGenreHash (MusicManager *m_mngr, int id) {
    Music* music = g_hash_table_lookup (m_mngr->music, GINT_TO_POINTER(id));
    return getMusicGenre (music);
}

Music* lookupMusicHash (MusicManager *m_mngr, int id) {
    Music* music = g_hash_table_lookup (m_mngr->music, GINT_TO_POINTER(id));
    if (music == NULL) return NULL;
    return copyMusic (music);
}
// receives a pointer to an array, copies the artist ids to it and returns the counter
int lookupMusicArtistIDsHash (MusicManager* mngr, int id, int** artistIds) {
    Music* music = g_hash_table_lookup (mngr->music, GINT_TO_POINTER(id));
    if (music == NULL) return -1;
    int idCounter = getMusicArtistIDCount (music);
    const int* ids = getMusicArtistID (music);
    *artistIds = malloc (sizeof (int) * idCounter);
    memcpy (*artistIds, ids, idCounter * (sizeof (int)));
    return idCounter;
}

void iterateMusic(MusicManager* m_mngr, void (*MusicProcessor)(gpointer, gpointer, gpointer), gpointer music_data) {
    g_hash_table_foreach(m_mngr->music, (GHFunc) MusicProcessor, music_data);
}


int getDataMusic (char *path, AlmightyManager* mngr) {
    Output* output = openErrorOutputMusics ();

    int error = parseFile(path, callbackMusic, mngr, output);

    closeOutputFile (output);
    if (error) return 1;
    else return 0;
}

// creates a musicString according to its tokens and validates them. 
// if valid, its converted to a music and added to the hashtable
void callbackMusic (char** tokens, void* manager, Output* output) { // receives entity manager
    AlmightyManager* mngr = (AlmightyManager*) manager;
    MusicManager* music_mngr = getMusicManager (mngr);
    ArtistManager* artist_mngr = getArtistManager (mngr);
    AlbumManager* album_mngr = getAlbumManager (mngr);

    MusicString* musicS = createMusicString (tokens);
    if (!validMusic(musicS, artist_mngr, album_mngr)) insertErrorFileMusics(musicS, output);
    else {
        Music* music = createMusic (tokens);
        insertMusicHash(music_mngr, getMusicID(music), music);
    }
    deleteMusicString (musicS);
}