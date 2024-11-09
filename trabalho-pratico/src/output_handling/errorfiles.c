#include <stdio.h>
#include <musics.h>
#include <users.h>
#include <utils.h>
#include <artists.h>
#include <stdlib.h>
#include <output_handling/errorfiles.h>
#include <output_handling/outputWriter.h>


Output* openErrorOutputUser () {
    Output* output = openOutputFile  ("resultados/users_errors.csv");

    writeErrorFileHandle (output, Users);
    return output;
}

void insertErrorFileUser(UserString *user, Output* output) {
    char* lines[10] = {NULL};
    lines[0] = getUserIDString(user);
    lines[1] = getUserEmailString(user);
    lines[2] = getUserFirstNameString(user);
    lines[3] = getUserLastNameString(user);
    lines[4] = getUserBirthDateString(user);
    lines[5] = getUserCountryString(user);
    lines[6] = getUserSubscriptionTypeString(user);
    lines[7] = getUserLikedMusicsIDString(user);

    setOutput (output, lines, 8);
    writeErrorFile (output);
 
    for (int i = 0; i < 8; i++) free(lines[i]);
}

Output* openErrorOutputArtists () {
    Output* output = openOutputFile ("resultados/artists_errors.csv");

    writeErrorFileHandle (output, Artists);
    return output;
}

void insertErrorFileArtists(ArtistString *artist, Output* output) {
    char* lines[10] = {NULL};
    lines[0] = getArtistIDString(artist);
    lines[1] = getArtistNameString(artist);
    lines[2] = getArtistDescriptionString(artist);
    lines[3] = getArtistRecipePerStreamString(artist);
    lines[4] = getArtistIDConstituentString(artist);
    lines[5] = getArtistCountryString(artist);
    lines[6] = getArtistTypeString(artist);

    setOutput (output, lines, 7);

    writeErrorFile (output);
    
    for (int i = 0; i < 7; i++) free(lines[i]);
}


Output* openErrorOutputMusics (){
    Output* output = openOutputFile ("resultados/musics_errors.csv");

    writeErrorFileHandle (output, Musics);
    return output;
}

void insertErrorFileMusics(MusicString *music, Output* output) {
    char* lines [10] = {NULL};

    lines[0] = getMusicIDString(music);
    lines[1] = getMusicTitleString(music);
    lines[2] = getMusicArtistIDString(music);
    lines[3] = getMusicDurationString(music);
    lines[4] = getMusicGenreString(music);
    lines[5] = getMusicYearString(music);
    lines[6] = getMusicLyricsString(music);

    setOutput (output, lines, 7);

    writeErrorFile (output);
    
    for (int i = 0; i < 7; i++) free(lines[i]);
}