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

typedef struct musicManager {
    GHashTable *music;
} MusicManager;

void insertMusicHash (MusicManager *m_mngr, int key, Music *Music) {
    g_hash_table_insert(m_mngr->music, GINT_TO_POINTER (key), Music);
}

MusicManager* initializeHashMusic () {
    MusicManager* m_mngr = malloc (sizeof (MusicManager));
    if (m_mngr == NULL) {
        perror("Failed to allocate memory for MusicManager");
        exit(EXIT_FAILURE); 
    }
    m_mngr->music = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify) deleteMusic);
    return m_mngr;
}

void freeHashMusic (MusicManager* m_mngr) {
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

void iterateMusic(MusicManager* m_mngr, void (*MusicProcessor)(gpointer value, gpointer music_data), gpointer music_data) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, m_mngr->music);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        MusicProcessor(value, music_data);
    }
}


int getDataMusic (char *path, hashtableManager* mngr) {
    Output* output = openErrorOutputMusics ();

    int error = parseFile(path, callbackMusic, mngr, output);

    closeOutputFile (output);
    if (error) return 1;
    else return 0;
}

// creates a musicString according to its tokens and validates them. 
// if valid, its converted to a music and added to the hashtable
void callbackMusic (char** tokens, void* manager, Output* output) { // receives entity manager
    hashtableManager* mngr = (hashtableManager*) manager;
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