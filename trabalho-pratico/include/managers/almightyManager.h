#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <userManager.h>
#include <artistManager.h>
#include <musicManager.h>
#include <albumManager.h>
#include <historyManager.h>

#ifndef HASHTABLE_MANAGER_H 
#define HASHTABLE_MANAGER_H

/**
 * @brief Structure representing the main manager for all data types.
 */
typedef struct almightyManager AlmightyManager;

/**
 * @brief Allocates memory for an AlmightyManager and initializes all the other managers.
 *
 * @return Pointer to the initialized AlmightyManager.
 */
AlmightyManager* initializeManagers ();

/**
 * @brief Frees all the managers and then itself.
 * 
 * @param mngr A pointer to the AlmightyManager to be freed.
 */
void freeAlmightyManager (AlmightyManager *mngr);

/**
 * @brief Function returns the UserManager from the main manager.
 * 
 * @param mngr A pointer to the main manager.
 * 
 * @return A pointer to the UserManager.
 */
UserManager* getUserManager (AlmightyManager *mngr);

/**
 * @brief Function returns the MusicManager from the main manager.
 * 
 * @param mngr A pointer to the main manager.
 * 
 * @return A pointer to the MusicManager.
 */
MusicManager* getMusicManager (AlmightyManager *mngr);

/**
 * @brief Function returns the ArtistManager from the main manager.
 * 
 * @param mngr A pointer to the main manager.
 * 
 * @return A pointer to the ArtistManager.
 */
ArtistManager* getArtistManager (AlmightyManager *mngr);

/**
 * @brief Function returns the AlbumManager from the main manager.
 * 
 * @param mngr A pointer to the main manager.
 * 
 * @return A pointer to the AlbumManager.
 */
AlbumManager* getAlbumManager (AlmightyManager *mngr);

/**
 * @brief Function returns the HistoryManager from the main manager.
 * 
 * @param mngr A pointer to the main manager.
 * 
 * @return A pointer to the HistoryManager.
 */
HistoryManager* getHistoryManager (AlmightyManager *mngr);
#endif