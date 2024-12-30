#include <album.h>
#include <output_handling/errorfiles.h>

typedef struct almightyManager AlmightyManager;

#ifndef _ALBUMMANAGER_H_
#define _ALBUMMANAGER_H_

/**
 * @brief Structure representing an album manager.
 */
typedef struct albumManager AlbumManager;

/**
 * @brief Inserts an @c Album in a hash table.
 * 
 * @param al_mngr pointer to the album manager, where the hash table is stored.
 * @param key The key to use when storing the album.
 * @param album Pointer to the album to be stored.
 */
void insertAlbumHash (AlbumManager *a_mngr, int key, Album *album);

/**
 * @brief Allocates memory and initializes the album hash table, exiting the program if it fails.
 * 
 * @return A pointer to the initialized album manager, where the Album hash table is stored.
 */
AlbumManager* initializeHashAlbum ();

/**
 * @brief Deletes all the contents of the album hash table and frees the pointer to the album manager.
 * 
 * @param al_mngr Pointer to the album manager.
 */
void freeHashAlbum (AlbumManager* a_mngr);

/**
 * @brief Performs a lookup in the album hash table.
 * 
 * @param al_mngr Pointer to the album manager.
 * @param id The key to perform the lookup with.
 * 
 * @return Returns true if the album exists, false otherwise.
 */
bool isAlbumInHash (AlbumManager *a_mngr, int id);

/**
 * @brief Counts how many albums an artist has made.
 * Iterates through the album hash table and for each album checks if the artist has contributed.
 * 
 * @param artistID The ID of the artist.
 * @param al_mngr A pointer to the album manager.
 * @param count A pointer to an @c int counter, where the number will be stored.
 */
void albumCountArtist(int artistID, AlbumManager* al_mngr, int* count);

/**
 * @brief Parses album dataset and checks for validity, writing to error logs if it fails.
 * 
 * @param path A string with the path to the album dataset.
 * @param mngr The main manager.
 * @return Returns if an error happened (1 for error, 0 for success).
 */
int getDataAlbum (char* path, AlmightyManager* mngr);

/**
 * @brief Callback function used during album parsing.
 * Checks if the tokens received during parsing create a valid artist. 
 * Valid entries are added to the hash table; invalid ones go to error logs.
 * 
 * @param tokens An array of strings with the tokens ot be used.
 * @param manager The main manager to get the data from.
 * @param output The error file structure.
 */
void callbackAlbum(char** tokens, void* manager, Output* output);
#endif