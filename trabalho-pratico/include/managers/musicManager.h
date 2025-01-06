#include <musics.h>
#include <glib.h>
#include <output_handling/errorfiles.h>

typedef struct almightyManager AlmightyManager;

#ifndef _MUSICMANAGER_H_
#define _MUSICMANAGER_H_

/**
 * @brief Structure representing a music manager.
 */
typedef struct musicManager MusicManager;

/**
 * @brief Inserts a @c Music into the hash table.
 *
 * @param a_mngr Pointer to the music manager, where the hash table is stored.
 * @param key The key used to store the music record.
 * @param Music Pointer to the music record to be stored.
 */
void insertMusicHash (MusicManager *a_mngr, int key, Music *Music);

/**
 * @brief Allocates memory and initializes the music hash table, exiting the program if it fails.
 *
 * @return A pointer to the initialized music manager, where the hash table is stored.
 */
MusicManager* initializeMusicManager ();

/**
 * @brief Deletes all the contents of the music hash table and frees the pointer to the music manager.
 *
 * @param a_mngr Pointer to the music manager.
 */
void freeMusicManager (MusicManager* a_mngr);

/**
 * @brief Checks if a music record is present in the hash table.
 *
 * @param m_mngr Pointer to the music manager.
 * @param id The key to perform the lookup with.
 *
 * @return Returns true if the music record exists, false otherwise.
 */
bool isMusicInHash (MusicManager *m_mngr, int id);

/**
 * @brief Looks up a music record in the hash table by ID.
 *
 * @param m_mngr Pointer to the music manager.
 * @param id The key to perform the lookup with.
 *
 * @return Pointer to the Music record if found, or NULL if not found.
 */
Music* lookupMusicHash (MusicManager *m_mngr, int id);

/**
 * @brief Looks up the genre of a music record by ID.
 *
 * @param m_mngr Pointer to the music manager.
 * @param id The ID of the music record.
 *
 * @return The genre associated with the music record, or a default value if not found.
 */
Genre lookupMusicGenreHash (MusicManager *m_mngr, int id);

/**
 * @brief Retrieves the artist IDs associated with a music record.
 *
 * @param mngr Pointer to the music manager.
 * @param id The ID of the music record.
 * @param artistIds Pointer to the array of artist IDs to be populated.
 *
 * @return The number of artist IDs found, or -1 if an error occurs.
 */
int lookupMusicArtistIDsHash (MusicManager* mngr, int id, int** artistIds);

/**
 * @brief Iterates through all entries in the music hash table and processes each entry using a callback function.
 *
 * @param m_mngr Pointer to the music manager.
 * @param MusicProcessor Callback function to process each music record.
 * @param music_data Pointer to additional data passed to the callback function.
 */
void iterateMusic(MusicManager* m_mngr, void (*MusicProcessor)(gpointer key, gpointer value, gpointer music_data), gpointer music_data);

/**
 * @brief Parses music dataset and checks for validity, writing to error logs if it fails.
 *
 * @param path A string with the path to the music dataset.
 * @param mngr Pointer to the manager containing the music data.
 *
 * @return Returns 1 for error, 0 for success.
 */
int getDataMusic (char *path, AlmightyManager* mngr);

/**
 * @brief Callback function used during music parsing.
 * Checks if the tokens received during parsing create a valid music record.
 * Valid entries are added to the hash table; invalid ones go to error logs.
 *
 * @param tokens An array of strings with the tokens to be used.
 * @param manager The music manager.
 * @param output The error file structure.
 */
void callbackMusic (char** tokens, void* manager, Output* output);

#endif