#include <musics.h>
#include <parsingUtils.h>
#include <validation.h>

typedef struct {
    char* id;              //– identificador único da música;
    char* title;         //– nome da música;
    char* artist_id;     //– lista de identificadores dos autores da música;
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
    free(music->id);
    music->id = strdup(id);
}

void setMusicTitle(Music* music, const char* title) {
    free(music->title);
    music->title = strdup(title);
}

void setMusicArtistID(Music* music, const char* artist_id) {
    free(music->artist_id);
    music->artist_id = strdup(artist_id);
}

void setMusicDuration(Music* music, const char* duration) {
    free(music->duration);
    music->duration = strdup(duration);
}

void setMusicGenre(Music* music, const char* genre) {
    free(music->genre);
    music->genre = strdup(genre);
}

void setMusicYear(Music* music, const char* year) {
    free(music->year);
    music->year = strdup(year);
}

void setMusicLyrics(Music* music, const char* lyrics) {
    free(music->lyrics);
    music->lyrics = strdup(lyrics);
}