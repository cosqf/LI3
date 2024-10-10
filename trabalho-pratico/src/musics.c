#include <musics.h>
#include <parsingUtils.h>
#include <validation.h>
#include <stdlib.h>


typedef struct music {
    char* id;              //– identificador único da música;
    char* title;         //– nome da música;
    char* artist_id;     //– lista de identificadores dos autores da música;
    unsigned int artist_id_count;
    char* duration;   //– tempo de duração;
    char* genre;         //– género da música;
    char* year;            //– ano de lançamento;
    char* lyrics;        //– letra da música.
} Music;


/* Creator function for Music: Initializes all fields to NULL or default values */
Music* createMusic() {
    Music* music = (Music*)malloc(sizeof(Music));
    
    if (music == NULL) {
        return NULL;
    }
    music->id = NULL;
    music->title = NULL;
    music->artist_id = NULL;
    music->artist_id_count = 0;
    music->duration = NULL;
    music->genre = NULL;
    music->year = NULL;
    music->lyrics = NULL;
    
    return music;
}

/* Destructor function for Music */
void deleteMusic(Music* music) {
    if (music == NULL) {
        return;
    }

    free(music->id);
    free(music->title);
    free(music->artist_id);
    free(music->duration);
    free(music->genre);
    free(music->year);
    free(music->lyrics);
    free(music);
}


void printMusic(const Music* music) {
    if (music == NULL) {
        printf("Music is NULL\n");
        return;
    }

    printf("ID: %s, Title: %s, Artists: %s, Duration: %s, Genre: %s, Year: %s\n",
           music->id ? music->id : "N/A",
           music->title ? music->title : "N/A",
           music->artist_id ? music->artist_id : "N/A",
           music->duration ? music->duration : "N/A",
           music->genre ? music->genre : "N/A",
           music->year ? music->year : "N/A");
}

// GETTERs

int getMusicID(Music* music) {
    return atoi (music->id + 1);
}

char* getMusicTitle(Music* music) {
    return strdup(music->title);
}

int* getMusicArtistID(Music* music) {
    return parseIDs (music->id, music, Musics);
}

int getMusicArtistIDCount (Music* music) {
    return music->artist_id_count;
}

Duration getMusicDuration(Music* music) {
    return parseDuration (music->duration);
}

char* getMusicGenre(Music* music) {
    return strdup(music->genre);
}

int getMusicYear(Music* music) {
    return atoi(music->year);
}

char* getMusicLyrics(Music* music) {
    return strdup(music->lyrics);
}

// SETTERs

void setMusicID(Music* music, const char* id) {
    if (music->id) free(music->id);
    music->id = strdup(id);
}

void setMusicTitle(Music* music, const char* title) {
    if (music->title) free(music->title);
    music->title = strdup(title);
}

void setMusicArtistID(Music* music, const char* artist_id) {
    if (music->artist_id) free(music->artist_id);
    music->artist_id = strdup(artist_id);
}

void setMusicDuration(Music* music, const char* duration) {
    if (music->duration) free(music->duration);
    music->duration = strdup(duration);
}

void setMusicGenre(Music* music, const char* genre) {
    if (music->genre) free(music->genre);
    music->genre = strdup(genre);
}

void setMusicYear(Music* music, const char* year) {
    if (music->year) free(music->year);
    music->year = strdup(year);
}

void setMusicLyrics(Music* music, const char* lyrics) {
    if (music->lyrics) free(music->lyrics);
    music->lyrics = strdup(lyrics);
}

void setMusicArtistIDCount (Music* music, int x) {
    music->artist_id_count = x;
}