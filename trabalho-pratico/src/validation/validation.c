#include <stdio.h>
#include <musics.h>
#include <users.h>
#include <utils.h>
#include <artists.h>
#include <stdlib.h>
#include <validation.h>
#include <outputWriter.h>


FILE * openErrorFileUser () {
    FILE* fp = fopen ("resultados/users_errors.csv", "w");
    if (!fp) {
        perror ("Error opening Error file");
        exit (1);
    }
    fprintf (fp, "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"\n");
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
    fprintf (fp, "\"id\";\"title\";\"artist_id\";\"duration\";\"genre\";\"year\";\"lyrics\"\n");
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

    fprintf(fp, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n", id, title, artistID, duration, genre, year, lyrics);

    free(id);
    free(title);
    free(artistID);
    free(duration);
    free(genre);
    free(year);
    free(lyrics);
}


//SYNTAX VALIDATION


Duration parseDuration(char* dur) {
    Duration duration = {0, 0, 0, 0};

    if (strlen(dur) > 8) {
        duration.error = 1;
        return duration;
    }

    if (sscanf(dur, "%d:%d:%d", &duration.hours, &duration.minutes, &duration.seconds) != 3) duration.error = 1;

    return duration;
}
//
//FILE * openResultFileArtists (){
//    FILE* fp = fopen ("resultados/artists.csv", "w");
//    if (!fp) {
//        perror ("Error opening Error file");
//        exit (1);
//        }
//    fprintf (fp, "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"\n");
//    return fp;
//}
//
//
//FILE * openResultsFileMusics (){
//    FILE* fp = fopen ("resultados/musics.csv", "w");
//    if (!fp) {
//        perror ("Error opening Error file");
//        exit (1);
//        }
//    fprintf (fp, "\"id\";\"title\";\"artist_id\";\"duration\";\"genre\";\"year\";\"lyrics\"\n");
//    return fp;
//}
//
//FILE * openResultFileUsers (){
//    FILE* fp = fopen ("resultados/users.csv", "w");
//    if (!fp) {
//        perror ("Error opening Error file");
//        exit (1);
//    }
//    fprintf (fp, "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\"\n");
//    return fp;
//}
//
//