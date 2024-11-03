#include <glib.h>
#include <musicManager.h>
#include <musics.h>
#include <artistManager.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <stdlib.h>
#include <utils.h>
#include <validation.h>
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
    m_mngr->music = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteMusic);
    return m_mngr;
}

void freeHashMusic (MusicManager* m_mngr) {
    g_hash_table_destroy (m_mngr->music);
    free (m_mngr);
}

Music* lookupMusicHash (MusicManager *m_mngr, int id) {
    Music* Music = g_hash_table_lookup (m_mngr->music, GINT_TO_POINTER(id));
    return Music;
}

GHashTable* getMusicTable (MusicManager *m_mngr) {
    return m_mngr->music;
}


void iterateMusic(MusicManager* m_mngr, void (*MusicProcessor)(gpointer value, gpointer music_data), gpointer music_data) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, m_mngr->music);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        MusicProcessor(value, music_data);
    }
}

void getDataMusic (char *path, MusicManager *musicManager, ArtistManager *artistManager) {
    char *musicPath = changePath (path, Musics);

    FILE* fileData = openFile (musicPath);
    FILE* fileError = openErrorFileMusics ();

    char str[DEFAULT];
    if (fgets(str, sizeof(str), fileData) == NULL) { // skip header
        perror ("skipping music header error");
        exit(EXIT_FAILURE);
    }
    while (fgets (str, sizeof (str), fileData) != NULL){
        char* tokens[7];
        parseLine(str, tokens, ";");

        Music* music = createMusic(tokens);
        if (!validMusic(music, artistManager)) {
            insertErrorFileMusics(music, fileError);
            deleteMusic(music);
        } else {
            insertMusicHash(musicManager, getMusicID(music), music);
        }

        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        //Music *myLookup = (Music *) g_hash_table_lookup(hashMusic, getMusicID (music));
        //printf("ID: %d, Genero: %s, Titulo: %s\n", getMusicID (myLookup), getMusicGenre (myLookup), getMusicTitle (myLookup));
    
        //printMusic (music);
        //deleteMusic (music);
    }
    fclose(fileData);
    fclose (fileError);
    free (musicPath);
}