#include <album.h>
#include <utils.h>
#include <parsingUtils.h>
#include <output_handling/errorfiles.h>
#include <stdlib.h>

typedef struct album {
    int id;                         //– identificador único do álbum;
    int* artist_id;                 //– lista de identificadores únicos dos artistas que lançaram o álbum;
    unsigned int artist_id_count;
} Album;

typedef struct albumString {
    char* id;                   //– identificador único do álbum;
    char* title;                //– título do álbum;
    char* artist_id;            //– lista de identificadores únicos dos artistas que lançaram o álbum;
    unsigned int artist_id_count;
    char* year;                 //– ano de lançamento;
    char* producers;            //– lista de produtores.
} AlbumString;


Album* createAlbum(char** tokens) {
    Album* album = malloc (sizeof(Album));
    if (mallocErrorCheck (album)) exit (EXIT_FAILURE);

    int id;
    if (convertToInt (trimString((tokens[0])) + 2, &id)) album->id = id;
    else exit (EXIT_FAILURE);

    album->artist_id = parseIDs (trimStringWithoutBrackets(tokens[2]));
    album->artist_id_count = IdCounter (tokens[2]);
    
    return album;
}

void deleteAlbum (Album* album) {
    if (album == NULL) return;
    
    free (album->artist_id);
    free (album);
}

// GETTERs

// Getter for the id field
int getAlbumId(Album* album) {
    return album->id;
}

// Getter for the artist_id field
int* getAlbumArtistId(Album* album) {
    return album->artist_id;
}

// Getter for the artist_id_count field
unsigned int getAlbumArtistIdCount(Album* album) {
    return album->artist_id_count;
}


// STRING

AlbumString* createAlbumString (char** tokens) {
    AlbumString* album = malloc(sizeof(AlbumString));
    if (mallocErrorCheck (album)) exit (EXIT_FAILURE);

    album->id = strdup (trimString(tokens[0]));
    album->title = strdup (trimString(tokens[1]));
    album->artist_id = strdup (trimStringWithoutBrackets(tokens[2]));
    album->artist_id_count = IdCounter (tokens[2]);
    album->year = strdup (trimString(tokens[3]));
    album->producers = strdup(trimStringWithoutBrackets(tokens[4]));
    return album;
}

void deleteAlbumString (AlbumString* album) {
    if (album == NULL) return;

    free(album->id);
    free(album->title);
    free(album->artist_id);
    free(album->year);
    free(album->producers);
    free(album);
}

// Getter for the id field
char* getAlbumIdString (AlbumString* album) {
    return strdup (album->id);
}

// Getter for the title field
char* getAlbumTitleString (AlbumString* album) {
    return strdup (album->title);
}

// Getter for the artist_id field
char* getAlbumArtistIdString (AlbumString* album) {
    return strdup (album->artist_id);
}

// Getter for the artist_id_count field
unsigned int getAlbumArtistIdCountString (AlbumString* album) {
    return album->artist_id_count;
}

// Getter for the year field
char* getAlbumYearString (AlbumString* album) {
    return strdup (album->year);
}

// Getter for the producer field
char* getAlbumProducerString (AlbumString* album) {
    return strdup (album->producers);
}
