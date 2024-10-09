#include <parsingUtils.h>
#include <validation.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <parsingMusic.h>


MusicRaw* fetchDataM (char *str, MusicRaw *music) {
   if (!str || !music) return NULL; 

    char *token = NULL;

    // Parsing the user ID
    token = trimString(strsep(&str, ";"));
    if (token) music->id = strdup(token);
    else {
        perror ("Id parsing error");
        return NULL;
    }   

    // Parsing title
    token = strsep(&str, ";");
    if (token) music->title = strdup(trimString(token));
    else {
        perror("Title parsing error");
        return NULL;
    }

    // Parsing the ID constituents
    token = strsep(&str, ";");
    if (token) music->artist_id = strdup((trimString(token)));
    else {
        perror("ID constituents parsing error");
        return NULL;
    }

    // Parsing the duration
    token = strsep(&str, ";");
    if (token) music->duration = strdup (trimString(token));
    else {
        perror("Duration parsing error");
        return NULL;
    }

    // Parsing the genre
    token = strsep(&str, ";");
    if (token) music->genre = strdup(trimString(token));
    else {
        perror("Genre parsing error");
        return NULL;
    }

    // Parsing the year
    token = strsep(&str, ";");
    if (token) music->year = strdup(trimString(token));
    else {
        perror("Year parsing error");
        return NULL;
    }

    // Parsing lyrics
    token = strsep(&str, ";");
    if (token) music->lyrics = strdup(trimString(token));
    else {
        perror("Lyrics parsing error");
        return NULL;
    }

    return music;
}

Music* parseDataM (Music *music, MusicRaw *raw) {
    
    music->id = atoi (raw->id + 1);

    music->title = strdup (raw->title);

    music->artist_id = parseIDs (raw->artist_id, music, Musics);

    music->duration = parseDuration (raw->duration);
    if (music->duration.error == 1) return NULL;

    music->genre = strdup (raw->genre);

    music->year = atoi (raw->year);

    music->lyrics = strdup (raw->lyrics);

    return music;
}