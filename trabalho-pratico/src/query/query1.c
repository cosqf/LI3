#include <stdlib.h>
#include <query1.h>
#include <parsing.h>
#include <userManager.h>
#include <users.h>
#include <stdio.h>
#include <output_handling/outputWriter.h>


void query1(CMD* cmd, UserManager *u_mngr, ArtistManager *a_mngr, int counter) {
    char filename[50];  // buffer for the formatted file name

    // Format the filename with the counter value
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", counter);

    Output* output = openOutputFile (filename);

    int ID = getCMDId(cmd);
    User* user = lookupUserHash(u_mngr, ID);

    if (user) {
        userinfo(cmd, user, output);
    } else {
        Artist* artist = lookupArtistHash(a_mngr, ID);

        if (artist) {
            artistinfo(cmd, artist, output);
        } else {
            writeNewLine(output);
            deleteArtist(artist);
            deleteUser(user);
        }

    }

    closeOutputFile(output);
}


void userinfo (CMD* cmd, User* user, Output* file) {
    char* lines[5] = {NULL};

    lines[0] = getUserEmail(user);
    lines[1] = getUserFirstName(user);
    lines[2] = getUserLastName(user);

    // Formatting the age as a string
    static char ageString[4]; // max age: 3 digits + \0
    snprintf(ageString, sizeof(ageString), "%d", getUserAge(user));
    lines[3] = ageString;
    
    lines[4] = getUserCountry(user);

    setOutput(file, lines, 5);

    writeQuerys(file, cmd);

    free(lines[0]);
    free(lines[1]);
    free(lines[2]);
    free(lines[4]);

    deleteUser(user);
}


void artistinfo (CMD* cmd, Artist* artist, Output* file) {
    char* lines[5] = {NULL};

    lines[0] = getArtistName(artist);
    
    if(getArtistType(artist)) lines[1] = "group";
    else lines[1] = "individual";

    lines[2] = getArtistCountry(artist);

    lines[3] = "2"; //num_albums_individual
    
    lines[4] = "3"; //total_recipe

    setOutput(file, lines, 5);

    writeQuerys(file, cmd);

    free(lines[0]);
    free(lines[1]);
    free(lines[2]);
    free(lines[4]);

    deleteArtist(artist);
}
