#include <stdio.h>
#include <musics.h>
#include <users.h>
#include <utils.h>
#include <artists.h>
#include <stdlib.h>
#include <errorfiles.h>
#include <outputWriter.h>


FILE * openErrorFileUser () {
    FILE* fp = fopen ("resultados/users_errors.csv", "w");
    if (!fp) {
        perror ("Error opening Error file");
        exit (1);
    }
    writeErrorsUsersHeader (fp);
    return fp;
}

void insertErrorFileUser(UserString *user, FILE *fp) {
    char* username = getUserIDString(user);
    char* email = getUserEmailString(user);
    char* firstName = getUserFirstNameString(user);
    char* lastName = getUserLastNameString(user);
    char* birthDate = getUserBirthDateString(user);
    char* country = getUserCountryString(user);
    char* subscriptionType = getUserSubscriptionTypeString(user);
    char* likedMusicsID = getUserLikedMusicsIDString(user);

    writeErrorsUsersContent (fp, username, email, firstName, lastName, birthDate, country, subscriptionType, likedMusicsID);

    free(username);
    free(email);
    free(firstName);
    free(lastName);
    free(birthDate);
    free(country);
    free(subscriptionType);
    free(likedMusicsID);
}

FILE * openErrorFileArtists (){
    FILE* fp = fopen ("resultados/artists_errors.csv", "w");
    if (!fp) {
        perror ("Error opening Error file");
        exit (1);
        }
    writeErrorsArtistsHeader(fp);
    return fp;
}

void insertErrorFileArtists (ArtistString *artist, FILE *fp) {
    char* id = getArtistIDString(artist);
    char* name = getArtistNameString(artist);
    char* description = getArtistDescriptionString(artist);
    char* recipePerStream = getArtistRecipePerStreamString(artist);
    char* idConstituent = getArtistIDConstituentString(artist);
    char* country = getArtistCountryString(artist);
    char* type = getArtistTypeString(artist);

    writeErrorsArtistsContent(fp, id, name, description, recipePerStream, idConstituent, country, type);

    free(id);
    free(name);
    free(description);
    free(recipePerStream);
    free(idConstituent);
    free(country);
    free(type);
}


FILE * openErrorFileMusics (){
    FILE* fp = fopen ("resultados/musics_errors.csv", "w");
    if (!fp) {
        perror ("Error opening Error file");
        exit (1);
        }
    writeErrorsMusicsHeader (fp);
    return fp;
}

void insertErrorFileMusics(MusicString *music, FILE *fp) {
    char* id = getMusicIDString(music);
    char* title = getMusicTitleString(music);
    char* artistID = getMusicArtistIDString(music);
    char* duration = getMusicDurationString(music);
    char* genre = getMusicGenreString(music);
    char* year = getMusicYearString(music);
    char* lyrics = getMusicLyricsString(music);

    writeErrorsMusicsContent (fp, id, title, artistID, duration, genre, year, lyrics);

    free(id);
    free(title);
    free(artistID);
    free(duration);
    free(genre);
    free(year);
    free(lyrics);
}