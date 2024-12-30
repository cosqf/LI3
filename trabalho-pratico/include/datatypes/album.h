#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef _ALBUM_H_
#define _ALBUM_H_
/**
 * @brief An album struct.
 */
typedef struct album Album;

/**
 * @brief Album struct but every component is in a string format.
 */
typedef struct albumString AlbumString;

/**
 * @brief Creates an album struct.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to an album struct.
 */
Album* createAlbum(char** tokens);

/**
 * @brief Deletes an album struct and frees its memory.
 *
 * @param album A pointer to the album to be destroyed.
 */
void deleteAlbum (Album* album);

/**
 * @brief Creates an album struct with parameters on a string format.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to an album struct with parameters on a string format.
 */
AlbumString* createAlbumString (char** tokens);

/**
 * @brief Deletes an album struct with parameters on a string format.
 *
 * @param album A pointer to the album to be destroyed.
 */
void deleteAlbumString (AlbumString* album);

/* Getters */
/**
 * @brief A getter function that returns an album ID.
 *
 * @param album A pointer to the album.
 * 
 * @return ID of the given album.
 */
int getAlbumId(Album* album);

/**
 * @brief A getter function that returns the IDs of the artists of an album.
 *
 * @param album A pointer to the album.
 * 
 * @return Array of the IDs of the artists of the given album.
 */
int* getAlbumArtistId(Album* album);

/**
 * @brief A getter function that returns how many artists made an album.
 *
 * @param album A pointer to the album.
 * 
 * @return Number of artists of the given album.
 */
unsigned int getAlbumArtistIdCount(Album* album);

/* Getters string*/
/**
 * @brief A getter function that returns the ID of an album in a string format.
 *
 * @param album A pointer to the album in a string format.
 * 
 * @return ID of the given album in a string format.
 */
char* getAlbumIdString (AlbumString* album);

/**
 * @brief A getter function that returns the title of an album in a string format.
 *
 * @param album A pointer to the album in a string format.
 * 
 * @return String of the title of the album.
 */
char* getAlbumTitleString (AlbumString* album);

/**
 * @brief A getter function that returns the ID of the artists of an album in a string format.
 *
 * @param album A pointer to the album in a string format.
 * 
 * @return ID of the given album in a string format.
 */
char* getAlbumArtistIdString (AlbumString* album);

/**
 * @brief A getter function that returns how many artists made an album in a string format.
 *
 * @param album A pointer to the album in string format.
 * 
 * @return Number of artists of the given album.
 */
unsigned int getAlbumArtistIdCountString (AlbumString* album);

/**
 * @brief A getter function that returns the year of an album in a string format.
 *
 * @param album A pointer to the album in a string format.
 * 
 * @return Year of the given album in a string format.
 */
char* getAlbumYearString (AlbumString* album);

/**
 * @brief A getter function that returns the producers of an album in a string format.
 *
 * @param album A pointer to the album in a string format.
 * 
 * @return The producers of the given album in a string format.
 */
char* getAlbumProducerString (AlbumString* album);

#endif