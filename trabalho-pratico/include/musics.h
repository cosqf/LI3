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

typedef struct music Music;

Music* createMusic();

void deleteMusic(Music* music);

void printMusic(const Music* music);

/* Getters */
int getMusicID(Music* music);
char* getMusicIDString(Music* music);
char* getMusicTitle(Music* music);
int* getMusicArtistID(Music* music);
char* getMusicArtistIDString(Music* music);
Duration getMusicDuration(Music* music);
char* getMusicDurationString(Music* music);
char* getMusicGenre(Music* music);
int getMusicYear(Music* music);
char* getMusicYearString(Music* music);
char* getMusicLyrics(Music* music);
int getMusicArtistIDCount (Music* music);

/* Setters */
void setMusicID(Music* music, const char* id);
void setMusicTitle(Music* music, const char* title);
void setMusicArtistID(Music* music, const char* artist_id);
void setMusicDuration(Music* music, const char* duration);
void setMusicGenre(Music* music, const char* genre);
void setMusicYear(Music* music, const char* year);
void setMusicLyrics(Music* music, const char* lyrics);
void setMusicArtistIDCount (Music* music, int x);

#endif  
