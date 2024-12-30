#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef _ARTISTS_H_
#define _ARTISTS_H_

/**
 * @brief An artist struct.
 */
typedef struct artist Artist;

/**
 * @brief Artist struct where every component is in a string format.
 */
typedef struct artistString ArtistString;


/**
 * @brief Creates an artist struct.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to an artist struct.
 */
Artist* createArtist(char **tokens);

/**
 * @brief Deletes an artist struct and frees its memory.
 *
 * @param artist A pointer to the artist to be destroyed.
 */
void deleteArtist(Artist* artist);


/**
 * @brief Creates an artist struct with parameters in a string format.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to an artist struct with parameters on a string format.
 */
ArtistString* createArtistString(char **tokens);

/**
 * @brief Frees the memory of an artist struct in a string format.
 *
 * @param artist A pointer to the artist to be destroyed.
 */
void deleteArtistString(ArtistString* artist);

/**
 * @brief Creates an artist struct from another, copying its contents.
 *
 * @param artistOG A pointer to the original artist struct.
 * 
 * @return A pointer to the copied artist struct.
 */
Artist* copyArtist(Artist* artistOG);


/* Getters */
/**
 * @brief A getter function that returns the ID of an artist.
 *
 * @param artist A pointer to the artist.
 * 
 * @return ID of the given artist.
 */
int getArtistID(Artist* artist);

/**
 * @brief A getter function that returns the name of an artist.
 *
 * @param artist A pointer to the artist.
 * 
 * @return Name of the given artist.
 */
char* getArtistName(Artist* artist);

/**
 * @brief A getter function that returns the revenue per stream of an artist.
 *
 * @param artist A pointer to the artist.
 * 
 * @return Revenue per stream of the given artist.
 */
double getArtistRecipePerStream(Artist* artist);

/**
 * @brief A getter function that returns the IDs of constituent artists for a group or band.
 *
 * @param artist A pointer to the artist.
 * 
 * @return Pointer to an array of IDs of constituent artists.
 */
const int* getArtistIDConstituent(Artist* artist);

/**
 * @brief A getter function that returns the number of constituent artists for a group or band.
 *
 * @param artist A pointer to the artist.
 * 
 * @return Number of constituent artists in the given group or band.
 */
unsigned int getArtistIDConstituentCounter(Artist* artist);

/**
 * @brief A getter function that returns the country of origin of an artist.
 *
 * @param artist A pointer to the artist.
 * 
 * @return Country of origin of the given artist.
 */
char* getArtistCountry(Artist* artist);

/**
 * @brief A getter function that returns the type of an artist (e.g., solo or band).
 *
 * @param artist A pointer to the artist.
 * 
 * @return Type of the given artist.
 */
int getArtistType(Artist* artist);

/* Getters string*/
/**
 * @brief A getter function that returns the ID of an artist in a string format.
 *
 * @param artist A pointer to the artist in a string format.
 * 
 * @return ID of the given artist in a string format.
 */
char* getArtistIDString(ArtistString* artist);

/**
 * @brief A getter function that returns the name of an artist in a string format.
 *
 * @param artist A pointer to the artist in a string format.
 * 
 * @return Name of the given artist in a string format.
 */
char* getArtistNameString(ArtistString* artist);

/**
 * @brief A getter function that returns the description of an artist in a string format.
 *
 * @param artist A pointer to the artist in a string format.
 * 
 * @return Description of the given artist in a string format.
 */
char* getArtistDescriptionString(ArtistString* artist);

/**
 * @brief A getter function that returns the revenue per stream of an artist in a string format.
 *
 * @param artist A pointer to the artist in a string format.
 * 
 * @return Revenue per stream of the given artist in a string format.
 */
char* getArtistRecipePerStreamString(ArtistString* artist);

/**
 * @brief A getter function that returns the IDs of constituent artists for a group or band in a string format.
 *
 * @param artist A pointer to the artist in a string format.
 * 
 * @return IDs of constituent artists in a string format.
 */
char* getArtistIDConstituentString(ArtistString* artist);

/**
 * @brief A getter function that returns the number of constituent artists for a group or band in a string format.
 *
 * @param artist A pointer to the artist in a string format.
 * 
 * @return Number of constituent artists in a string format.
 */
unsigned int getArtistIDConstituentCounterString(ArtistString* artist);

/**
 * @brief A getter function that returns the country of origin of an artist in a string format.
 *
 * @param artist A pointer to the artist in a string format.
 * 
 * @return Country of origin of the given artist in a string format.
 */
char* getArtistCountryString(ArtistString* artist);

/**
 * @brief A getter function that returns the type of an artist in a string format (e.g., solo or band).
 *
 * @param artist A pointer to the artist in a string format.
 * 
 * @return Type of the given artist in a string format.
 */
char* getArtistTypeString(ArtistString* artist);

#endif  
