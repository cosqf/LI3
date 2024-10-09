#include <stdlib.h>
#include <utils.h>
#include <artists.h>
#include <parsingUtils.h>

typedef struct {
    char* id;                       //– identificador único do artista;
    char* name;                     //– nome do artista;
    char* description;              //– detalhes do artista;
    char* recipe_per_stream;        //– dinheiro auferido de cada vez que uma das músicas do artista é reproduzida;
    char* id_constituent;            //– lista de identificadores únicos dos seus constituintes, no caso de se tratar de um artista coletivo. Este campo pode ser uma lista vazia.
    unsigned int id_constituent_counter;
    char* country;                  //– nacionalidade do artista.
    char* type;                 //– tipo de artista, i.e., individual(0) ou grupo musical(1)
} Artist;


/* Create a new Artist */
Artist* createArtist() {
    Artist* artist = malloc(sizeof(Artist));
    if (mallocErrorCheck (artist)) exit (EXIT_FAILURE);
    artist->id = NULL;
    artist->name = NULL;
    artist->description = NULL;
    artist->recipe_per_stream = NULL;
    artist->id_constituent = NULL;
    artist->country = NULL;
    artist->type = NULL;
    artist->id_constituent_counter = 0;
    return artist;
}

/* Destroy an Artist and free all allocated memory */
void deleteArtist(Artist* artist) {
    if (artist) {
        free(artist->id);
        free(artist->name);
        free(artist->description);
        free(artist->recipe_per_stream);
        free(artist->id_constituent);
        free(artist->country);
        free(artist->type);
        free(artist);
    }
}

// GETTERs

/* Getter for id */
int getArtistID(Artist* artist) {
    return atoi (artist->id + 1);
}

/* Getter for name */
char* getArtistName(Artist* artist) {
    return strdup(artist->name);
}

/* Getter for description */
char* getArtistDescription(Artist* artist) {
    return strdup(artist->description);
}

/* Getter for recipe_per_stream */
float getArtistRecipePerStream(Artist* artist) {
    return atof(artist->recipe_per_stream);
}

/* Getter for id_constituent */
int* getArtistIDConstituent(Artist* artist) {
    return parseIDs (artist->id_constituent, artist, Artists);
}

/* Getter for id_constituent_counter */
unsigned int getArtistIDConstituentCounter(Artist* artist) {
    return artist->id_constituent_counter;
}

/* Getter for country */
char* getArtistCountry(Artist* artist) {
    return strdup(artist->country);
}

/* Getter for type */
int getArtistType(Artist* artist) {
    return atoi(artist->type);
}


// SETTERs

/* Setter for id */
void setArtistID(Artist* artist, const char* id) {
    free(artist->id);
    artist->id = strdup(id);
}

/* Setter for name */
void setArtistName(Artist* artist, const char* name) {
    free(artist->name);
    artist->name = strdup(name);
}

/* Setter for description */
void setArtistDescription(Artist* artist, const char* description) {
    free(artist->description);
    artist->description = strdup(description);
}

/* Setter for recipe_per_stream */
void setArtistRecipePerStream(Artist* artist, const char* recipe_per_stream) {
    free(artist->recipe_per_stream);
    artist->recipe_per_stream = strdup(recipe_per_stream);
}

/* Setter for id_constituent */
void setArtistIDConstituent(Artist* artist, const char* id_constituent) {
    free(artist->id_constituent);
    artist->id_constituent = strdup(id_constituent);
}

/* Setter for id_constituent_counter */
void setArtistIDConstituentCounter(Artist* artist, unsigned int id_constituent_counter) {
    artist->id_constituent_counter = id_constituent_counter;
}

/* Setter for country */
void setArtistCountry(Artist* artist, const char* country) {
    free(artist->country);
    artist->country = strdup(country);
}

/* Setter for type */
void setArtistType(Artist* artist, const char* type) {
    free(artist->type);
    artist->type = strdup(type);
}