#include <musics.h>
#include <utils.h>
#include <parsingUtils.h>
#include <validation.h>
#include <stdlib.h>

typedef struct music {
    int id;              //– identificador único da música;
    char* title;         //– nome da música;
    int* artist_id;     //– lista de identificadores dos autores da música;
    unsigned int artist_id_count;
    Duration duration;   //– tempo de duração;
    Genre genre;         //– género da música;
    short int year;            //– ano de lançamento;
    char* lyrics;        //– letra da música.
} Music;

typedef struct musicString {
    char* id;              //– identificador único da música;
    char* title;         //– nome da música;
    char* artist_id;     //– lista de identificadores dos autores da música;
    unsigned int artist_id_count;
    char* duration;   //– tempo de duração;
    char* genre;         //– género da música;
    char* year;            //– ano de lançamento;
    char* lyrics;        //– letra da música.
} MusicString;


/* Creator function for Music */
Music* createMusic(char** tokens) {
    Music* music = (Music*) malloc (sizeof(Music));
    if (mallocErrorCheck (music)) exit (EXIT_FAILURE);

    music->id = atoi (trimString(tokens[0]) + 1);
    music->title = strdup (trimString(tokens[1]));
    music->artist_id = parseIDs (trimStringWithoutBrackets(tokens[2]));
    music->artist_id_count = IdCounter (tokens[2]);
    music->duration = parseDuration (trimString(tokens[3]));
    music->genre = getGenre (trimString(tokens[4]));
    music->year = atoi (trimString(tokens[5]));
    music->lyrics = strdup (trimString(tokens[6]));
    
    return music;
}

/* Destructor function for Music */
void deleteMusic(Music* music) {
    if (music == NULL) {
        return;
    }

    free(music->title);
    free(music->artist_id);
    free(music->lyrics);
    free(music);
}

/* Creator function for Music */
MusicString* createMusicString (char** tokens) {
    MusicString* music = (MusicString*) malloc(sizeof(MusicString));
    if (mallocErrorCheck (music)) exit (EXIT_FAILURE);

    music->id = strdup (trimString(tokens[0]));
    music->title = strdup (trimString(tokens[1]));
    music->artist_id = strdup (trimStringWithoutBrackets(tokens[2]));
    music->artist_id_count = IdCounter (tokens[2]);
    music->duration = strdup (trimString(tokens[3]));
    music->genre = strdup (trimString(tokens[4]));
    music->year = strdup (trimString(tokens[5]));
    music->lyrics = strdup (trimString(tokens[6]));
    
    return music;
}

/* Destructor function for Music */
void deleteMusicString (MusicString* music) {
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

Genre getGenre(const char *genre) {
    if (strcmp(genre, "Metal") == 0) return GENRE_METAL;
    if (strcmp(genre, "Reggae") == 0) return GENRE_REGGAE;
    if (strcmp(genre, "Jazz") == 0) return GENRE_JAZZ;
    if (strcmp(genre, "Hip Hop") == 0) return GENRE_HIPHOP;
    if (strcmp(genre, "Classical") == 0) return GENRE_CLASSICAL;
    if (strcmp(genre, "Rock") == 0) return GENRE_ROCK;
    if (strcmp(genre, "Blues") == 0) return GENRE_BLUES;
    if (strcmp(genre, "Country") == 0) return GENRE_COUNTRY;
    if (strcmp(genre, "Pop") == 0) return GENRE_POP;
    if (strcmp(genre, "Electronic") == 0) return GENRE_ELECTRONIC;
    return -1; // Invalid genre
}

// GETTERs

/* Getter for id */
int getMusicID(Music* music) {
    return music->id;
}

/* Getter for title */
char* getMusicTitle(Music* music) {
    return strdup(music->title);
}

/* Getter for artist's ID */
int* getMusicArtistID(Music* music) {
    return music->artist_id;
}

/* Getter for artist's ID count */
int getMusicArtistIDCount (Music* music) {
    return music->artist_id_count;
}

/* Getter for song's duration */
Duration getMusicDuration(Music* music) {
    return music->duration;
}

/* Getter for genre */
Genre getMusicGenre(Music* music) {
    return music->genre;
}

/* Getter for year */
int getMusicYear(Music* music) {
    return music->year;
}

/* Getter for lyrics */
char* getMusicLyrics(Music* music) {
    return strdup(music->lyrics);
}


// GETTERs STRING

/* Getter for id in string format */
char* getMusicIDString (MusicString* music) {
    return strdup (music->id);
}

/* Getter for title in string format */
char* getMusicTitleString (MusicString* music) {
    return strdup(music->title);
}

/* Getter for artist's ID  in string format */
char* getMusicArtistIDString(MusicString* music) {
    return strdup (music->artist_id);
}

/* Getter for artist's ID count in string format */
int getMusicArtistIDCountString (MusicString* music) {
    return music->artist_id_count;
}

/* Getter for song's duration in string format */
char* getMusicDurationString(MusicString* music) {
    return strdup (music->duration);
}

/* Getter for genre in string format */
char* getMusicGenreString(MusicString* music) {
    return strdup(music->genre);
}

/* Getter for year in string format */
char* getMusicYearString(MusicString* music) {
    return strdup(music->year);
}

/* Getter for lyrics in string format */
char* getMusicLyricsString(MusicString* music) {
    return strdup(music->lyrics);
}