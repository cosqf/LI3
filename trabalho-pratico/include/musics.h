#include <stdio.h>
#ifndef _MUSICS_H_
#define _MUSICS_H_

typedef struct {
    int hours;     //hh (00-99)
    int minutes;   //mm (00-59)
    int seconds;   //ss (00-59)
    short int error; 
} Duration;

typedef struct Music Music;

Music* createMusic();

void deleteMusic(Music* music);

/* Getters */
int getMusicID(Music* music);
char* getMusicTitle(Music* music);
int* getMusicArtistID(Music* music);
Duration getMusicDuration(Music* music);
char* getMusicGenre(Music* music);
int getMusicYear(Music* music);
char* getMusicLyrics(Music* music);

/* Setters */
void setMusicID(Music* music, const char* id);
void setMusicTitle(Music* music, const char* title);
void setMusicArtistID(Music* music, const char* artist_id);
void setMusicDuration(Music* music, const char* duration);
void setMusicGenre(Music* music, const char* genre);
void setMusicYear(Music* music, const char* year);
void setMusicLyrics(Music* music, const char* lyrics);

#endif  
