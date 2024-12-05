#include <stdlib.h>
#include <utils.h>
#include <artists.h>
#include <parsingUtils.h>

typedef struct artist {
    int id;                       //– identificador único do artista;
    char* name;                     //– nome do artista;
    double recipe_per_stream;        //– dinheiro auferido de cada vez que uma das músicas do artista é reproduzida;
    int* id_constituent;            //– lista de identificadores únicos dos seus constituintes, no caso de se tratar de um artista coletivo. Este campo pode ser uma lista vazia.
    unsigned int id_constituent_counter;
    char* country;                  //– nacionalidade do artista.
    bool type;                 //– tipo de artista, i.e., individual(0) ou grupo musical(1)
} Artist;

typedef struct artistString {
    char* id;                       //– identificador único do artista;
    char* name;                     //– nome do artista;
    char* description;              //– detalhes do artista;
    char* recipe_per_stream;        //– dinheiro auferido de cada vez que uma das músicas do artista é reproduzida;
    char* id_constituent;            //– lista de identificadores únicos dos seus constituintes, no caso de se tratar de um artista coletivo. Este campo pode ser uma lista vazia.
    unsigned int id_constituent_counter;
    char* country;                  //– nacionalidade do artista.
    char* type;                 //– tipo de artista, i.e., individual(0) ou grupo musical(1)
} ArtistString;



/* Create a new Artist */
Artist* createArtist(char **tokens) {
    Artist* artist = malloc(sizeof(Artist));
    if (mallocErrorCheck (artist)) exit (EXIT_FAILURE);

    int id;
    if (convertToInt (trimString((tokens[0])) + 1, &id)) artist->id = id;
    else exit (EXIT_FAILURE);

    artist->name = strdup (trimString(tokens[1]));
    artist->recipe_per_stream = atof (trimString(tokens[3]));
    artist->id_constituent = parseIDs (trimStringWithoutBrackets(tokens[4]));
    artist->id_constituent_counter = IdCounter (tokens[4]);
    artist->country = strdup (trimString(tokens[5]));

    char* typeString = trimString(tokens[6]);
    if (strcmp (typeString, "individual") == 0) artist->type = 0;
    else if (strcmp (typeString, "group") == 0) artist->type = 1;
    else perror ("Artist type error");
    return artist;
}

/* Destroy an Artist and free all allocated memory */
void deleteArtist(Artist* artist) {
    if (artist) {
        free(artist->name);
        free(artist->id_constituent);
        free(artist->country);
        free(artist);
    }
}

/* Create a new Artist using strings only */
ArtistString* createArtistString (char **tokens) {
    ArtistString* artist = malloc(sizeof(ArtistString));
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
void deleteArtistString (ArtistString* artist) {
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

Artist* copyArtist(Artist* artistOG) {
    if (artistOG == NULL) {
        return NULL;
    }

    Artist* artistCopy = malloc(sizeof(Artist));
    if (!artistCopy) {
        perror("Error allocating memory for Artist");
        return NULL;
    }

    artistCopy->id = artistOG->id;
    artistCopy->recipe_per_stream = artistOG->recipe_per_stream;
    artistCopy->type = artistOG->type;

    // copy the string fields
    artistCopy->name = strdup(artistOG->name);
    if (!artistCopy->name) {
        perror ("Error copying artist name");
        free (artistCopy);
        return NULL;
    }
    artistCopy->country = strdup(artistOG->country);
    if (!artistCopy->country) {
        perror ("Error copying artist country");
        free (artistCopy->name);
        free (artistCopy);
        return NULL;

    }

    // copy the int array
    int arrayCount = artistOG->id_constituent_counter;
    if (artistOG->id_constituent && arrayCount > 0) {
        artistCopy->id_constituent = malloc(arrayCount * sizeof(int));
        if (artistCopy->id_constituent == NULL) {
            perror("Error allocating memory for id_constituent");
            free(artistCopy->name);
            free(artistCopy->country);
            free(artistCopy);
            return NULL;
        }
        memcpy(artistCopy->id_constituent, artistOG->id_constituent, arrayCount * sizeof(int));

    } else artistCopy->id_constituent = NULL;

    artistCopy->id_constituent_counter = arrayCount;

    return artistCopy;
}


// GETTERs

/* Getter for id */
int getArtistID(Artist* artist) {
    return artist->id;
}

/* Getter for name */
char* getArtistName(Artist* artist) {
    return strdup(artist->name);
}

/* Getter for recipe_per_stream */
double getArtistRecipePerStream(Artist* artist) {
    return artist->recipe_per_stream;
}

/* Getter for id_constituent */
const int* getArtistIDConstituent(Artist* artist) {
    return artist->id_constituent;
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
    return artist->type;
}


// GETTERs for string

/* Getter for id in string format */
char* getArtistIDString(ArtistString* artist) {
    return strdup (artist->id);
}

/* Getter for name in string format */
char* getArtistNameString(ArtistString* artist) {
    return strdup(artist->name);
}

/* Getter for description in string format */
char* getArtistDescriptionString(ArtistString* artist) {
    return strdup(artist->description);
}

/* Getter for recipe_per_stream in string format */
char* getArtistRecipePerStreamString(ArtistString* artist) {
    return strdup(artist->recipe_per_stream);
}

/* Getter for id_constituent in string format */
char* getArtistIDConstituentString(ArtistString* artist) {
    return strdup (artist->id_constituent);
}

/* Getter for id_constituent_counter in string format */
unsigned int getArtistIDConstituentCounterString(ArtistString* artist) {
    return artist->id_constituent_counter;
}

/* Getter for country in string format */
char* getArtistCountryString(ArtistString* artist) {
    return strdup(artist->country);
}

/* Getter for type in string format*/
char* getArtistTypeString(ArtistString* artist) {
    return strdup(artist->type);
}