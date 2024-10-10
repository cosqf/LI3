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
    fprintf (fp, "username;email;first_name;last_name;birth_date;country;subscription_type;liked_songs_id");
    return fp;
}

void insertErrorFileUser (User *user, FILE *fp) {
    fprintf (fp, "%s;%s;%s;%s;%s;%s;%s;%s", 
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
    fprintf (fp, "id;name;description;recipe_per_stream;id_constituent;country;type");
    return fp;
}

void insertErrorFileArtists (Artist *artist, FILE *fp) {
    fprintf (fp, "%s;%s;%s;%s;%s;%s;%s", getArtistIDString (artist),
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
    fprintf (fp, "id;title;artist_id;duration;genre;year;lyrics");
    return fp;
}

void insertErrorFileMusics (Music *music, FILE *fp) {
    fprintf (fp, "%s;%s;%s;%s;%s;%s;%s", getMusicIDString (music),
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

    else if(duration.hours < 0 || duration.hours > 99 || duration.minutes < 0 || duration.minutes > 59 || duration.seconds < 0 || duration.seconds > 59) duration.error = 1;
    
    else duration.error = 0;
    return duration;
}



//LOGIC VALIDATION

/*
• Utilizadores:
– O campo liked_musics_id de um utilizador, deverá conter apenas mú-
sicas existentes e válidas.
*/
int valid_likes(int* liked_musics_id, int liked_musics_count){
    for(int i = 0; i < liked_musics_count; i++){
        
    }
}
//


/*
• Músicas:
– O campo artist_id de uma música, deverá corresponder a um artista
existente e válido.
*/
int valid_artistid(){

}


/*
• Artistas:
– O campo id_constituent de um artista individual não poderá ter ele-
mentos.
*/
int valid_idconst(){

}