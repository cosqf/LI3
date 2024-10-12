#include <stdio.h>
#include <musics.h>
#include <users.h>
#include <utils.h>
#include <artists.h>
#include <stdlib.h>
#include <validation.h>


FILE * openErrorFileUser () {
    FILE* fp = fopen ("resultados/users_errors.csv", "w");
    if (!fp) {
        perror ("Error opening Error file");
        exit (1);
    }
    fprintf (fp, "username;email;first_name;last_name;birth_date;country;subscription_type;liked_songs_id\n");
    return fp;
}

void insertErrorFileUser (User *user, FILE *fp) {
    fprintf (fp, "%s;%s;%s;%s;%s;%s;%s;%s\n", 
            getUserNameString(user), 
            getUserEmail(user), 
            getUserFirstName(user), 
            getUserLastName(user), 
            getUserBirthDateString(user), 
            getUserCountry(user), 
            getUserSubscriptionTypeString(user), 
            getUserLikedMusicsIDString(user));
}


FILE * openErrorFileArtists (){
    FILE* fp = fopen ("resultados/artist_errors.csv", "w");
    if (!fp) {
        perror ("Error opening Error file");
        exit (1);
        }
    fprintf (fp, "id;name;description;recipe_per_stream;id_constituent;country;type\n");
    return fp;
}

void insertErrorFileArtists (Artist *artist, FILE *fp) {
    fprintf (fp, "%s;%s;%s;%s;%s;%s;%s\n", getArtistIDString (artist),
                                         getArtistName (artist), 
                                         getArtistDescription (artist),
                                         getArtistRecipePerStreamString(artist),
                                         getArtistIDConstituentString (artist),
                                         getArtistCountry (artist),
                                         getArtistTypeString (artist));
}


FILE * openErrorFileMusics (){
    FILE* fp = fopen ("resultados/music_errors.csv", "w");
    if (!fp) {
        perror ("Error opening Error file");
        exit (1);
        }
    fprintf (fp, "id;title;artist_id;duration;genre;year;lyrics\n");
    return fp;
}

void insertErrorFileMusics (Music *music, FILE *fp) {
    fprintf (fp, "%s;%s;%s;%s;%s;%s;%s\n", getMusicIDString (music),
                                            getMusicTitle (music),
                                            getMusicArtistIDString (music),
                                            getMusicDurationString(music),
                                            getMusicGenre(music),
                                            getMusicYearString(music),
                                            getMusicLyrics(music));
}


//SYNTAX VALIDATION


Duration parseDuration(char* dur){
    Duration duration;

    if (sscanf(dur, "%d:%d:%d", &duration.hours, &duration.minutes, &duration.seconds) != 3) duration.error = 1;
    
    else duration.error = 0;

    return duration;
}
