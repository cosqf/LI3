#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef _ARTISTS_H_
#define _ARTISTS_H_

typedef struct artist Artist;

/* Creator: Initializes the Artist struct with NULL/default values */
Artist* createArtist(char **tokens);

/* Destructor: Frees the memory of an Artist struct */
void deleteArtist(Artist* artist);

void printArtist(const Artist* artist);

/* Getters */
int getArtistID(Artist* artist);
char* getArtistIDString(Artist* artist);
char* getArtistName(Artist* artist);
char* getArtistDescription(Artist* artist);
float getArtistRecipePerStream(Artist* artist);
char* getArtistRecipePerStreamString(Artist* artist);
int* getArtistIDConstituent(Artist* artist);
char* getArtistIDConstituentString(Artist* artist);
unsigned int getArtistIDConstituentCounter(Artist* artist);
char* getArtistCountry(Artist* artist);
int getArtistType(Artist* artist);
char* getArtistTypeString(Artist* artist);

/* Setters */
void setArtistID(Artist* artist, const char* id);
void setArtistName(Artist* artist, const char* name);
void setArtistDescription(Artist* artist, const char* description);
void setArtistRecipePerStream(Artist* artist, const char* recipe_per_stream);
void setArtistIDConstituent(Artist* artist, const char* id_constituent);
void setArtistIDConstituentCounter(Artist* artist, unsigned int id_constituent_counter);
void setArtistCountry(Artist* artist, const char* country);
void setArtistType(Artist* artist, const char* type);

#endif  
