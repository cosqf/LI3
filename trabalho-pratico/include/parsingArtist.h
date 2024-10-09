#include <artists.h>
#ifndef _PARSINGARTIST_H_
#define _PARSINGARTIST_H_


// Parses artist
Artist* parseDataA (Artist *artist, ArtistRaw *raw); 

 // fetches data from the artist file
ArtistRaw* fetchDataA (char *str, ArtistRaw *artist);

#endif