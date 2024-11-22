#include <musics.h>
#include <utils.h>
#include <parsingUtils.h>
#include <output_handling/errorfiles.h>
#include <stdlib.h>

typedef struct music {
    int id;                         //– identificador único da música;
    int* artist_id;                 //– lista de identificadores dos autores da música;
    unsigned int artist_id_count;
    unsigned int album_id;          //– identificador único do álbum ao qual a música pertence;
    Duration duration;              //– tempo de duração;
    Genre genre;                    //– género da música;
} Music;

typedef struct musicString {
    char* id;                   //– identificador único da música;
    char* title;                //– nome da música;
    char* artist_id;            //– lista de identificadores dos autores da música;
    unsigned int artist_id_count;
    char* album_id;             //– identificador único do álbum ao qual a música pertence;
    char* duration;             //– tempo de duração;
    char* genre;                //– género da música;
    char* year;                 //– ano de lançamento;
    char* lyrics;               //– letra da música.
} MusicString;


/* Creator function for Music */
Music* createMusic(char** tokens) {
    Music* music = malloc (sizeof(Music));
    if (mallocErrorCheck (music)) exit (EXIT_FAILURE);

    int id, album_id;
    if (convertToInt (trimString((tokens[0])) + 1, &id)) music->id = id;
    else exit (EXIT_FAILURE);

    music->artist_id = parseIDs (trimStringWithoutBrackets(tokens[2]));
    music->artist_id_count = IdCounter (tokens[2]);
    if (convertToInt (trimString((tokens[3])) + 1, &album_id)) music->album_id = album_id;
    else exit (EXIT_FAILURE);
    music->duration = parseDuration (trimString(tokens[4]));
    music->genre = getGenre (trimString(tokens[5]));
    
    return music;
}

/* Destructor function for Music */
void deleteMusic(Music* music) {
    if (music == NULL) return;

    free(music->artist_id);
    free(music);
}

/* Creator function for Music */
MusicString* createMusicString (char** tokens) {
    MusicString* music = malloc(sizeof(MusicString));
    if (mallocErrorCheck (music)) exit (EXIT_FAILURE);

    music->id = strdup (trimString(tokens[0]));
    music->title = strdup (trimString(tokens[1]));
    music->artist_id = strdup (trimStringWithoutBrackets(tokens[2]));
    music->artist_id_count = IdCounter (tokens[2]);
    music->album_id = strdup(trimString(tokens[3]));
    music->duration = strdup (trimString(tokens[4]));
    music->genre = strdup (trimString(tokens[5]));
    music->year = strdup (trimString(tokens[6]));
    music->lyrics = strdup (trimString(tokens[7]));
    
    return music;
}

/* Destructor function for Music */
void deleteMusicString (MusicString* music) {
    if (music == NULL) return;

    free(music->id);
    free(music->title);
    free(music->artist_id);
    free(music->duration);
    free(music->album_id);
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

Music* copyMusic (Music* musicOg) {   // needs work
    Music* music = malloc (sizeof (Music));
    if (!music) {
        perror ("Error copying user");
        return NULL;
    }
    music->id = musicOg->id;
    //music->title = strdup (musicOg->title);
    music->artist_id = musicOg->artist_id;
    music->artist_id_count = musicOg->artist_id_count;
    music->album_id = musicOg->album_id;
    music->duration = musicOg-> duration;
    music->genre = musicOg-> genre;
    //music->year = musicOg->year;

    return music;
}

// GETTERs

/* Getter for id */
int getMusicID(Music* music) {
    return music->id;
}

/* Getter for title */
// char* getMusicTitle(Music* music) {
//     return strdup(music->title);
// }

/* Getter for artist's ID */
const int* getMusicArtistID(Music* music) {
    return music->artist_id;
}

/* Getter for artist's ID count */
int getMusicArtistIDCount (Music* music) {
    return music->artist_id_count;
}

/* Getter for album ID*/
int getMusicAlbumID (Music* music) {
    return music->album_id;
}

/* Getter for song's duration */
Duration getMusicDuration(Music* music) {
    return music->duration;
}

/* Getter for genre */
Genre getMusicGenre(Music* music) {
    return music->genre;
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

/* Getter for album ID in string format*/
char* getMusicAlbumIDString (MusicString* music) {
    return strdup (music->album_id);
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