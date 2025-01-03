#include <stdio.h>

#include <users.h>
#include <musics.h>
#include <artists.h>
#include <history.h>

#include <musicManager.h>
#include <artistManager.h>
#include <albumManager.h>

#ifndef _VALIDATEDATATYPES_H_
#define _VALIDATEDATATYPES_H_

//USERS
/**
 * @brief Validates a user struct by checking if all fields are valid.
 * 
 * @param user Pointer to the user data in string format.
 * @param m_mngr Pointer to the music manager for validating liked music IDs.
 * 
 * @return True if the user is valid, false otherwise.
 */
bool validUser(UserString* user, MusicManager *m_mngr);

/**
 * @brief Validates a user's email address.
 * Ensures the email follows the format "username@email.end", where:
 * - 'username' contains at least one character.
 * - 'email' and 'end' contain valid characters.
 * - 'end' has a length of 2 or 3 characters.
 *
 * @param email Pointer to the email string.
 * 
 * @return True if the email is valid, false otherwise.
 */
bool validEmail(char* email);

/**
 * @brief Validates a user's birthdate.
 * Ensures the birthdate is in the format "yyyy/mm/dd", with valid date values, and not more recent than 09/09/2024.
 *
 * @param bdate Pointer to the birthdate string.
 * 
 * @return True if the birthdate is valid, false otherwise.
 */
bool validBirthdate(char* bdate);

/**
 * @brief Validates a user's subscription type.
 * Checks if the subscription type is either "normal" or "premium".
 *
 * @param subs Pointer to the subscription string.
 * 
 * @return True if the subscription type is valid, false otherwise.
 */
bool validSubscription(char* subs);

/**
 * @brief Validates liked music IDs of a user by checking if they exit in the music manager's hash table.
 *
 * @param liked_musics_id Pointer to the array of liked music IDs.
 * @param liked_musics_count Number of liked music IDs.
 * @param m_mngr Pointer to the music manager for validation.
 * 
 * @return True if all liked music IDs are valid, false otherwise.
 */
bool validLikes(const int* liked_musics_id, int liked_musics_count, MusicManager *m_mngr);


//MUSICS
/**
 * @brief Validates a music struct by checking if all fields are valid.
 *
 * @param music Pointer to the music data in string format.
 * @param a_mngr Pointer to the artist manager for validating artist IDs.
 * @param al_mngr Pointer to the album manager for validating the album ID.
 * 
 * @return True if the music record is valid, false otherwise.
 */
bool validMusic(MusicString* music, ArtistManager *a_mngr, AlbumManager *al_mngr);

/**
 * @brief Validates the duration of a music track.
 * Ensures the duration is in the format "hh:mm:ss" with:
 * - Hours:   0–99
 * - Minutes: 0–59
 * - Seconds: 0–59
 *
 * @param duration Parsed duration structure.
 * 
 * @return True if the duration is valid, false otherwise.
 */
bool validDuration(Duration duration);

/**
 * @brief Validates a music's album ID by checking if it exists in the album manager's hash table.

 * @param id Album ID to validate.
 * @param al_mngr Pointer to the album manager for validation.
 * 
 * @return True if the album ID is valid, false otherwise.
 */
bool validAlbumID(int id, AlbumManager *al_mngr);


//ARTISTS
/**
 * @brief Validates an artist struct by checking if all fields are valid.
 *
 * @param artist Pointer to the artist data in string format.
 * 
 * @return True if the artist is valid, false otherwise.
 */
bool validArtist(ArtistString* artist);

/**
 * @brief Validates the artist's ID constituent.
 *
 * Ensures that an artist of type "individual" has no constituents. 
 *
 * @param type Artist's type.
 * @param constituents Number of constituents.
 * 
 * @return True if the artist's ID constituent is valid, false otherwise.
 */
bool validIdConst(char* type, int constituents);

/**
 * @brief Validates the artist's type by checking if it's either "individual" or "group".

 * @param type Artist's type.

 * @return True if the type is valid, false otherwise.
 */
bool validType(char* type);

//LISTS
/**
 * @brief Validates a list of IDs by ensuring it starts and ends with the proper brackets ("[" and "]").
 * 
 * @param idList String of a list of IDs.
 * 
 * @return True if the list is valid, false otherwise.
 */
bool validList(char* idList);

/**
 * @brief Validates a list of artist IDs, ensuring all the IDs correspond to valid and existing artists.
 *
 * @param id Array of artist IDs.
 * @param n Number of artist IDs in the list.
 * @param a_mngr Pointer to the artist manager.
 * 
 * @return True if all artist IDs are valid, false otherwise.
 */
bool validArtistId(int* id, int n, ArtistManager *a_mngr);

//HISTORY
/**
 * @brief Validates a history entry by checking if the platform type is either "mobile" or "desktop".

 * @param history Pointer to the @c HistoryString.

 * @return True if the platform is valid, false otherwise.
 */
bool validHistory(HistoryString* history);

/**
 * @brief Validates the platform of a history entry, ensuring it's either "mobile" or "desktop".

 * @param platform Platform string.

 * @return True if the platform is valid, false otherwise.
 */
bool validPlatform(char* platform);


//ALBUMS
/**
 * @brief Validates an album entry by checking its artist IDs and format.
 *
 * Ensures that the album's artist IDs are valid and exist in the artist manager, and that the artist ID list is properly formatted.
 *
 * @param album Pointer to the @c AlbumString.
 * @param a_mngr Pointer to the ArtistManager.
 * 
 * @return True if the album is valid, false otherwise.
 */
bool validAlbum(AlbumString* album, ArtistManager* a_mngr);

#endif  