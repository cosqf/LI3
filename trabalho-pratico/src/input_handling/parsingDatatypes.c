#include <parsingUtils.h>
#include <validation.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <artists.h>
#include <users.h>
#include <validateDatatypes.h>
#include <parsingDatatypes.h>

User * fetchDataU (char *str, User *user) {
    if (!str || !user) return NULL;

    char *token = NULL;

    // Fetching the ID
    token = trimString(strsep(&str, ";"));
    if (token) setUserID (user, trimString(token));
    else perror ("Id fetching error");

    // Fetching the email
    token = trimString(strsep(&str, ";"));
    if (token) setUserEmail (user, trimString(token));
    else perror ("Email fetching error");

    // Fetching first name
    token = trimString(strsep(&str, ";"));
    if (token) setUserFirstName (user, trimString(token));
    else perror ("First name fetching error");

    // Fetching last name
    token = trimString(strsep(&str, ";"));
    if (token) setUserLastName (user, trimString(token));
    else perror ("Last name fetching error");

    // Fetching birth date
    token = trimString(strsep(&str, ";"));
    if (token) setUserBirthDate(user, trimString(token));
    else perror ("Birth date fetching error");

    // Fetching country
    token = trimString(strsep(&str, ";"));
    if (token) setUserCountry (user, trimString(token));
    else perror ("Country fetching error");

    // Fetching subscription type
    token = trimString(strsep(&str, ";"));
    if (token) setUserSubscriptionType (user, trimString(token));
    else perror ("Subscription type fetching error");

    // Fetching liked musics ID
    token = trimStringWithoutBrackets(strsep(&str, ";"));
    if (token) setUserLikedMusicsID (user, trimStringWithoutBrackets(token));
    else perror ("liked musics ID fetching error");

    return user;
}

Artist* fetchDataA (char *str, Artist *artist) {
    if (!str || !artist) return NULL; 

    char *token = NULL;

    // Fetching the ID
    token = trimString(strsep(&str, ";"));
    if (token) setArtistID (artist, trimString(token));
    else {
        perror ("Id parsing error");
        return NULL;
    }

    // Fetching the name
    token = strsep(&str, ";");
    if (token) setArtistName (artist, trimString(token));
    else {
        perror("Name parsing error");
        return NULL;
    }

    // Fetching the description
    token = strsep(&str, ";");
    if (token) setArtistDescription (artist, trimString(token));
    else {
        perror("Description parsing error");
        return NULL;
    }

    // Fetching recipe per stream
    token = strsep(&str, ";");
    if (token) setArtistRecipePerStream (artist, trimString(token));
    else {
        perror("Recipe parsing error");
        return NULL;
    }

    // Fetching the ID constituents
    token = strsep(&str, ";");
    if (token) setArtistIDConstituent (artist, trimStringWithoutBrackets(token));
    else {
        perror("ID constituents parsing error");
        return NULL;
    }

    // Setting the ID constituents counter
    char* ids = getArtistIDConstituentString (artist);
    setArtistIDConstituentCounter(artist, IdCounter(ids));
    free (ids);
    // Fetching the country
    token = strsep(&str, ";");
    if (token) setArtistCountry (artist, trimString(token));
    else {
        perror("Country parsing error");
        return NULL;
    }

    // Fetching the type
    token = strsep(&str, ";");
    if (token) setArtistType (artist, trimString(token));
    else {
        perror("Type parsing error");
        return NULL;
    }

   return artist;
}

Music* fetchDataM (char *str, Music *music) {
   if (!str || !music) return NULL; 

    char *token = NULL;

    // Parsing the user ID
    token = trimString(strsep(&str, ";"));
    if (token) setMusicID (music, trimString(token));
    else {
        perror ("Id parsing error");
        return NULL;
    }   

    // Parsing title
    token = strsep(&str, ";");
    if (token) setMusicTitle (music, trimString(token));
    else {
        perror("Title parsing error");
        return NULL;
    }

    // Parsing the ID constituents
    token = strsep(&str, ";");
    if (token) setMusicArtistID (music, trimStringWithoutBrackets(token));
    else {
        perror("ID constituents parsing error");
        return NULL;
    }

    // Setting the music's artists' ID counter
    char* ids = getMusicArtistIDString(music);
    setMusicArtistIDCount(music, IdCounter(ids));
    free (ids);

    // Parsing the duration
    token = strsep(&str, ";");
    if (token) setMusicDuration (music, trimString(token));
    else {
        perror("Duration parsing error");
        return NULL;
    }

    // Parsing the genre
    token = strsep(&str, ";");
    if (token) setMusicGenre (music, trimString(token));
    else {
        perror("Genre parsing error");
        return NULL;
    }

    // Parsing the year
    token = strsep(&str, ";");
    if (token) setMusicYear (music, trimString(token));
    else {
        perror("Year parsing error");
        return NULL;
    }

    // Parsing lyrics
    token = strsep(&str, ";");
    if (token) setMusicLyrics (music, trimString(token));
    else {
        perror("Lyrics parsing error");
        return NULL;
    }

    return music;
}
