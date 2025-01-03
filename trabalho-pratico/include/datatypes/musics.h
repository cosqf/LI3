#include <stdio.h>
#include <string.h>
#include <parsingUtils.h>

#ifndef _MUSICS_H_
#define _MUSICS_H_

/**
 * @brief All the genres of music allowed.
 */
typedef enum {
    GENRE_METAL,
    GENRE_REGGAE,
    GENRE_JAZZ,
    GENRE_HIPHOP,
    GENRE_CLASSICAL,
    GENRE_ROCK,
    GENRE_BLUES,
    GENRE_COUNTRY,
    GENRE_POP,
    GENRE_ELECTRONIC
} Genre;

/**
 * @brief A music struct.
 */
typedef struct music Music;

/**
 * @brief Music struct where every component is in a string format.
 */
typedef struct musicString MusicString;

/**
 * @brief Creates a music struct.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to a music struct.
 */
Music* createMusic (char** tokens);

/**
 * @brief Deletes a music struct and frees its memory.
 *
 * @param music A pointer to the music struct to be deleted.
 */
void deleteMusic (Music* music);

/**
 * @brief Creates a music struct in string format.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to a music string struct.
 */
MusicString* createMusicString (char** tokens);

/**
 * @brief Deletes a music string struct and frees its memory.
 *
 * @param music A pointer to the music string struct to be deleted.
 */
void deleteMusicString (MusicString* music); 

/**
 * @brief Retrieves a genre from a string representation.
 *
 * @param genre A string representing the genre.
 * 
 * @return The corresponding genre enum value.
 */
Genre getGenre (const char *genre);




const char* genreToString(Genre genre);





/**
 * @brief Creates a music struct from another, copying its contents.
 *
 * @param musicOg A pointer to the original music struct.
 * 
 * @return A pointer to the copied music struct.
 */
Music* copyMusic (Music* musicOg);


/* Getters */
/**
 * @brief A getter function that returns the ID of a music entry.
 *
 * @param music A pointer to the music struct.
 * 
 * @return ID of the given music entry.
 */
int getMusicID(Music* music);

/**
 * @brief A getter function that returns the artist IDs of a music entry.
 *
 * @param music A pointer to the music struct.
 * 
 * @return Pointer to an array of artist IDs for the given music entry.
 */
const int* getMusicArtistID(Music* music);

/**
 * @brief A getter function that returns the number of artists for a music entry.
 *
 * @param music A pointer to the music struct.
 * 
 * @return Count of artists associated with the given music entry.
 */
int getMusicArtistIDCount (Music* music);

/**
 * @brief A getter function that returns the album ID of a music entry.
 *
 * @param music A pointer to the music struct.
 * 
 * @return Album ID of the given music entry.
 */
int getMusicAlbumID (Music* music);

/**
 * @brief A getter function that returns the duration of a music entry.
 *
 * @param music A pointer to the music struct.
 * 
 * @return Duration of the given music entry.
 */
Duration getMusicDuration(Music* music);

/**
 * @brief A getter function that returns the genre of a music entry.
 *
 * @param music A pointer to the music struct.
 * 
 * @return Genre of the given music entry.
 */
Genre getMusicGenre(Music* music);



/* Getters string */
/**
 * @brief A getter function that returns the ID of a music entry in string format.
 *
 * @param music A pointer to the music string struct.
 * 
 * @return ID of the given music entry in string format.
 */
char* getMusicIDString(MusicString* music);

/**
 * @brief A getter function that returns the title of a music entry in string format.
 *
 * @param music A pointer to the music string struct.
 * 
 * @return Title of the given music entry in string format.
 */
char* getMusicTitleString (MusicString* music);

/**
 * @brief A getter function that returns the artist IDs of a music entry in string format.
 *
 * @param music A pointer to the music string struct.
 * 
 * @return Artist IDs of the given music entry in string format.
 */
char* getMusicArtistIDString(MusicString* music);

/**
 * @brief A getter function that returns the number of artists for a music entry in string format.
 *
 * @param music A pointer to the music string struct.
 * 
 * @return Count of artists associated with the given music entry.
 */
int getMusicArtistIDCountString (MusicString* music);

/**
 * @brief A getter function that returns the album ID of a music entry in string format.
 *
 * @param music A pointer to the music string struct.
 * 
 * @return Album ID of the given music entry in string format.
 */
char* getMusicAlbumIDString (MusicString* music);

/**
 * @brief A getter function that returns the duration of a music entry in string format.
 *
 * @param music A pointer to the music string struct.
 * 
 * @return Duration of the given music entry in string format.
 */
char* getMusicDurationString(MusicString* music);

/**
 * @brief A getter function that returns the genre of a music entry in string format.
 *
 * @param music A pointer to the music string struct.
 * 
 * @return Genre of the given music entry in string format.
 */
char* getMusicGenreString(MusicString* music);

/**
 * @brief A getter function that returns the release year of a music entry in string format.
 *
 * @param music A pointer to the music string struct.
 * 
 * @return Release year of the given music entry in string format.
 */
char* getMusicYearString(MusicString* music);

/**
 * @brief A getter function that returns the lyrics of a music entry in string format.
 *
 * @param music A pointer to the music string struct.
 * 
 * @return Lyrics of the given music entry in string format.
 */
char* getMusicLyricsString(MusicString* music);

#endif  
