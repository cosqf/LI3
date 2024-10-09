#include <parsingUtils.h>
#include <validation.h>
#include <artists.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <parsingArtist.h>

ArtistRaw* fetchDataA (char *str, ArtistRaw *artist) {
    if (!str || !artist) return NULL; 

    char *token = NULL;

    // Fetching the ID
    token = trimString(strsep(&str, ";"));
    if (token) artist->id = strdup(token);
    else {
        perror ("Id parsing error");
        return NULL;
    }

    // Fetching the name
    token = strsep(&str, ";");
    if (token) artist->name = strdup(trimString(token));
    else {
        perror("Name parsing error");
        return NULL;
    }

    // Fetching the description
    token = strsep(&str, ";");
    if (token) artist->description = strdup(trimString(token));
    else {
        perror("Description parsing error");
        return NULL;
    }

    // Fetching recipe per stream
    token = strsep(&str, ";");
    if (token) artist->recipe_per_stream = strdup(trimString(token));
    else {
        perror("Recipe parsing error");
        return NULL;
    }


    // Fetching the ID constituents
    token = strsep(&str, ";");
    if (token) artist->id_constituent = strdup(trimString(token));
    if (artist->id_constituent == NULL) {
        perror("ID constituents parsing error");
        return NULL;
    }

    // Fetching the country
    token = strsep(&str, ";");
    if (token) artist->country = strdup(trimString(token));
    else {
        perror("Country parsing error");
        return NULL;
    }

    // Fetching the type
    token = strsep(&str, ";");
    if (token) artist->type = strdup(trimString(token));
    else {
        perror("Type parsing error");
        return NULL;
    }

   return artist;

}
Artist* parseDataA (Artist *artist, ArtistRaw *raw) {

    artist->id = atoi (raw->id + 1);

    artist->name = strdup (raw->name);

    artist->description = strdup (raw->description);

    artist->recipe_per_stream = atof (raw->recipe_per_stream);

    artist->id_constituent = parseIDs (raw->id_constituent, artist, Artists);   // VERIFICACAO ERRADA, FIX

    artist->country = strdup (raw->country);

    artist->type = atoi (raw->type);

    return artist;
}
