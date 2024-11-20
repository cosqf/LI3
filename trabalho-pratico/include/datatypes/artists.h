#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef _ARTISTS_H_
#define _ARTISTS_H_

typedef struct artist Artist;
typedef struct artistString ArtistString;


/* Creator: Initializes the Artist struct with NULL/default values */
Artist* createArtist(char **tokens);

/* Destructor: Frees the memory of an Artist struct */
void deleteArtist(Artist* artist);


/* Creator: Initializes the Artist struct with NULL/default values */
ArtistString* createArtistString(char **tokens);

/* Destructor: Frees the memory of an Artist struct */
void deleteArtistString(ArtistString* artist);

Artist* copyArtist(Artist* artistOG);


/* Getters */
int getArtistID(Artist* artist);
char* getArtistName(Artist* artist);
char* getArtistDescription(Artist* artist);
float getArtistRecipePerStream(Artist* artist);
const int* getArtistIDConstituent(Artist* artist);
unsigned int getArtistIDConstituentCounter(Artist* artist);
char* getArtistCountry(Artist* artist);
int getArtistType(Artist* artist);

char* getArtistIDString(ArtistString* artist);
char* getArtistNameString(ArtistString* artist);
char* getArtistDescriptionString(ArtistString* artist);
char* getArtistRecipePerStreamString(ArtistString* artist);
char* getArtistIDConstituentString(ArtistString* artist);
unsigned int getArtistIDConstituentCounterString(ArtistString* artist);
char* getArtistCountryString(ArtistString* artist);
char* getArtistTypeString(ArtistString* artist);

#endif  
