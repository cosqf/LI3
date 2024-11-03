#include <stdlib.h>
#include <utils.h>
#include <artists.h>
#include <parsingUtils.h>

typedef struct artist {
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
Artist* createArtist(char **tokens) {
    Artist* artist = malloc(sizeof(Artist));
    if (mallocErrorCheck (artist)) exit (EXIT_FAILURE);

    artist->id = strdup (trimString(tokens[0]));
    artist->name = strdup (trimString(tokens[1]));
    artist->description = strdup (trimString(tokens[2]));
    artist->recipe_per_stream = strdup (trimString(tokens[3]));
    artist->id_constituent = strdup (trimStringWithoutBrackets(tokens[4]));
    artist->id_constituent_counter = IdCounter (tokens[4]);
    artist->country = strdup (trimString(tokens[5]));
    artist->type = strdup (trimString(tokens[6]));
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


void printArtist(const Artist* artist) {
    if (artist == NULL) {
        printf("Artist is NULL\n");
        return;
    }

    printf("ID: %s, Name: %s, Description: %s, Recipe per Stream: %s, Constituent IDs: %s, "
           "Constituent Count: %u, Country: %s, Type: %s\n",
           artist->id ? artist->id : "N/A",
           artist->name ? artist->name : "N/A",
           artist->description ? artist->description : "N/A",
           artist->recipe_per_stream ? artist->recipe_per_stream : "N/A",
           artist->id_constituent ? artist->id_constituent : "N/A",
           artist->id_constituent_counter,
           artist->country ? artist->country : "N/A",
           artist->type ? artist->type : "N/A");
}


// GETTERs

/* Getter for id */
int getArtistID(Artist* artist) {
    return atoi (artist->id + 1);
}
/* Getter for id in string format */
char* getArtistIDString(Artist* artist) {
    return strdup (artist->id);
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

/* Getter for recipe_per_stream in string format */
char* getArtistRecipePerStreamString(Artist* artist) {
    return strdup(artist->recipe_per_stream);
}

/* Getter for id_constituent */
int* getArtistIDConstituent(Artist* artist) {
    return parseIDs (trimString (artist->id_constituent), artist, Artists);
}

/* Getter for id_constituent in string format */
char* getArtistIDConstituentString(Artist* artist) {
    return strdup (artist->id_constituent);
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

/* Getter for type in string format*/
char* getArtistTypeString(Artist* artist) {
    return strdup(artist->type);
}


// SETTERs

/* Setter for id */
void setArtistID(Artist* artist, const char* id) {
    if (artist->id) free(artist->id);
    artist->id = strdup(id);
}

/* Setter for name */
void setArtistName(Artist* artist, const char* name) {
    if (artist->name) free (artist->name);
    artist->name = strdup(name);
}

/* Setter for description */
void setArtistDescription(Artist* artist, const char* description) {
    if (artist->description) free(artist->description);
    artist->description = strdup(description);
}

/* Setter for recipe_per_stream */
void setArtistRecipePerStream(Artist* artist, const char* recipe_per_stream) {
    if (artist->recipe_per_stream) free(artist->recipe_per_stream);
    artist->recipe_per_stream = strdup(recipe_per_stream);
}

/* Setter for id_constituent */
void setArtistIDConstituent(Artist* artist, const char* id_constituent) {
    if (artist->id_constituent) free(artist->id_constituent);
    artist->id_constituent = strdup(id_constituent);
}

/* Setter for id_constituent_counter */
void setArtistIDConstituentCounter(Artist* artist, unsigned int id_constituent_counter) {
    artist->id_constituent_counter = id_constituent_counter;
}

/* Setter for country */
void setArtistCountry(Artist* artist, const char* country) {
    if (artist->country) free(artist->country);
    artist->country = strdup(country);
}

/* Setter for type */
void setArtistType(Artist* artist, const char* type) {
    if (artist->type) free(artist->type);
    artist->type = strdup (type);
}