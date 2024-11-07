#include <stdio.h>
#include <string.h>

#ifndef _MUSICS_H_
#define _MUSICS_H_

typedef struct {
    int hours;     //hh (00-99)
    int minutes;   //mm (00-59)
    int seconds;   //ss (00-59)
    short int error; 
} Duration;

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

typedef struct music Music;

typedef struct musicString MusicString;


Music* createMusic (char** tokens);

void deleteMusic (Music* music);

MusicString* createMusicString (char** tokens);

void deleteMusicString (MusicString* music); 

Genre getGenre (const char *genre);


/* Getters */
int getMusicID(Music* music);
char* getMusicTitle(Music* music);
int* getMusicArtistID(Music* music);
Duration getMusicDuration(Music* music);
Genre getMusicGenre(Music* music);
int getMusicYear(Music* music);
char* getMusicLyrics(Music* music);
int getMusicArtistIDCount (Music* music);

/* Getters string */
char* getMusicIDString(MusicString* music);
char* getMusicTitleString (MusicString* music);
char* getMusicArtistIDString(MusicString* music);
int getMusicArtistIDCountString (MusicString* music);
char* getMusicDurationString(MusicString* music);
char* getMusicGenreString(MusicString* music);
char* getMusicYearString(MusicString* music);
char* getMusicLyricsString(MusicString* music);

#endif  
