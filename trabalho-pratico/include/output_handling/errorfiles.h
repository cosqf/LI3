#include <users.h>
#include <artists.h>
#include <musics.h>
#include <history.h>
#include <album.h>
#include <stdlib.h>
#include "output_handling/outputWriter.h"

#ifndef _ERRORFILES_H_
#define _ERRORFILES_H_

/**
 * @brief Opens an @c Output file with the path to the users error file and writes the error handle.
 * 
 * @return A pointer to the @c Output struct.
 */
Output* openErrorOutputUser ();

/**
 * @brief Opens an @c Output file with the path to the artists error file and writes the error handle.
 * 
 * @return A pointer to the @c Output struct.
 */
Output* openErrorOutputArtists ();

/**
 * @brief Opens an @c Output file with the path to the musics error file and writes the error handle.
 * 
 * @return A pointer to the @c Output struct.
 */
Output* openErrorOutputMusics ();

/**
 * @brief Opens an @c Output file with the path to the historys error file and writes the error handle.
 * 
 * @return A pointer to the @c Output struct.
 */
Output* openErrorOutputHistory ();

/**
 * @brief Opens an @c Output file with the path to the albums error file and writes the error handle.
 * 
 * @return A pointer to the @c Output struct.
 */
Output* openErrorOutputAlbum ();

/**
 * @brief Writes the data from an @c UserString in its correspondent the error file.
 * Fetches the data from the user, in an @c UserString format, and writes it to the error file.
 * @param userS A pointer to the user to be writen.
 * @param output A pointer to the Output struct, where the error file is stored.
 */
void insertErrorFileUser(UserString *user, Output* output);

/**
 * @brief Writes the data from an @c ArtistString in its correspondent the error file.
 * Fetches the data from the artist, in an @c ArtistString format, and writes it to the error file.
 * @param artistS A pointer to the artist to be writen.
 * @param output A pointer to the Output struct, where the error file is stored.
 */
void insertErrorFileArtists(ArtistString *artist, Output* output);

/**
 * @brief Writes the data from an @c MusicString in its correspondent the error file.
 * Fetches the data from the music, in an @c MusicString format, and writes it to the error file.
 * @param musicS A pointer to the music to be writen.
 * @param output A pointer to the Output struct, where the error file is stored.
 */
void insertErrorFileMusics(MusicString *music, Output* output);

/**
 * @brief Writes the data from an @c HistoryString in its correspondent the error file.
 * Fetches the data from the history, in an @c HistoryString format, and writes it to the error file.
 * @param historyS A pointer to the history to be writen.
 * @param output A pointer to the Output struct, where the error file is stored.
 */
void insertErrorFileHistory(HistoryString *historyS, Output* output);

/**
 * @brief Writes the data from an @c AlbumString in its correspondent the error file.
 * Fetches the data from the album, in an @c AlbumString format, and writes it to the error file.
 * @param albumS A pointer to the album to be writen.
 * @param output A pointer to the Output struct, where the error file is stored.
 */
void insertErrorFileAlbum(AlbumString *albumS, Output* output);

#endif