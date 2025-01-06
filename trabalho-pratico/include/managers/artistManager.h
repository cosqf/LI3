#include <artists.h>
#include <glib.h>
#include <output_handling/errorfiles.h>

#ifndef _ARTISTMANAGER_H_
#define _ARTISTMANAGER_H_

/**
 * @brief Structure representing an artist manager.
 */
typedef struct artistManager ArtistManager;

/**
 * @brief Inserts an @c Artist in a hash table.
 *
 * @param a_mngr Pointer to the artist manager, where the hash table is stored.
 * @param key The key to use when storing the artist.
 * @param artist Pointer to the artist to be stored.
 */
void insertArtistHash (ArtistManager *a_mngr, int key, Artist *artist);

/**
 * @brief Allocates memory and initializes the artist hash table, exiting the program if it fails.
 *
 * @return A pointer to the initialized artist manager, where the Artist hash table is stored.
 */
ArtistManager* initializeArtistManager ();

/**
 * @brief Deletes all the contents of the artist hash table and frees the pointer to the artist manager.
 *
 * @param a_mngr Pointer to the artist manager.
 */
void freeArtistManager (ArtistManager* a_mngr);

/**
 * @brief Performs a lookup in the artist hash table.
 *
 * @param a_mngr Pointer to the artist manager.
 * @param id The key to perform the lookup with.
 *
 * @return Pointer to the Artist if found, or NULL if not found.
 */
Artist* lookupArtistHash (ArtistManager *a_mngr, int id);

/**
 * @brief Checks if an artist is in the hash table.
 *
 * @param a_mngr Pointer to the artist manager.
 * @param id The key to perform the lookup with.
 *
 * @return Returns true if the artist exists, false otherwise.
 */
bool isArtistInHash (ArtistManager *a_mngr, int id);

/**
 * @brief Checks if an artist ID is present in a list.
 *
 * @param ids Pointer to an array of artist IDs.
 * @param artistID The ID of the artist to check.
 * @param length The length of the ID array.
 *
 * @return Returns true if the artist ID is in the list, false otherwise.
 */
bool isArtistInList (const int* ids, int artistID, int length);

/**
 * @brief Looks up an artist's country by ID.
 *
 * @param a_mngr Pointer to the artist manager.
 * @param id The ID of the artist.
 *
 * @return Returns a string containing the artist's country, or NULL if not found.
 */
char* lookupArtistCountryHash (ArtistManager *a_mngr, int id);

/**
 * @brief Parses artist dataset and checks for validity, writing to error logs if it fails.
 *
 * @param path A string with the path to the artist dataset.
 * @param mngr The artist manager.
 *
 * @return Returns 1 for error, 0 for success.
 */
int getDataArtist (char *path, ArtistManager* mngr);

/**
 * @brief Gets the artist type from the hash table.
 *
 * @param id The ID of the artist.
 * @param mngr The artist manager.
 *
 * @return Returns true if the artist type is valid, false otherwise.
 */
bool getArtistTypeHash (int id, ArtistManager* mngr);

/**
 * @brief Callback function used during artist parsing.
 * Checks if the tokens received during parsing create a valid artist. 
 * Valid entries are added to the hash table; invalid ones go to error logs.
 *
 * @param tokens An array of strings with the tokens to be used.
 * @param manager The artist manager.
 * @param output The error file structure.
 */
void callbackArtist(char **tokens, void *manager, Output *output);

#endif