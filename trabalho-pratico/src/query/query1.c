#include <stdlib.h>
#include <query1.h>
#include <parsing.h>
#include <userManager.h>
#include <musicManager.h>
#include <artistManager.h>
#include <users.h>
#include <utils.h>
#include <stdio.h>
#include <output_handling/outputWriter.h>


void query1(CMD* cmd, AlmightyManager* mngr, int counter) {
    char filename[50];  // buffer for the formatted file name

    // Format the filename with the counter value
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", counter);

    Output* output = openOutputFile (filename);

    char entity = getCMDentity(cmd);
    int ID = getCMDId(cmd);

    if (entity == 'A') {
        ArtistManager* a_mngr = getArtistManager(mngr);
        Artist* artist = lookupArtistHash(a_mngr, ID);
        if (!artist) writeNewLine(output);
        else artistinfo(cmd, mngr, artist, output);
    } else if (entity == 'U') {
        UserManager* u_mngr = getUserManager(mngr);
        User* user = lookupUserHash(u_mngr, ID);
        if (!user) writeNewLine(output);
        else userinfo(cmd, user, output);
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


void artistinfo (CMD* cmd, AlmightyManager* mngr, Artist* artist, Output* file) {
    char* lines[5] = {NULL};

    lines[0] = getArtistName(artist);
    
    if(getArtistType(artist)) lines[1] = "group";
    else lines[1] = "individual";

    lines[2] = getArtistCountry(artist);
    
    static char indAlbums[5];
    snprintf(indAlbums, sizeof(indAlbums), "%d", individualAlbums(mngr, artist));
    lines[3] = indAlbums;

    static char tRecipe [10];
    snprintf(tRecipe, sizeof(tRecipe), "%.2f", totalRecipe(mngr, artist));
    lines[4] = tRecipe;

    setOutput(file, lines, 5);

    writeQuerys(file, cmd);

    free(lines[0]);
    free(lines[2]);

    deleteArtist(artist);
}

int individualAlbums(AlmightyManager* mngr, Artist* artist) {
    AlbumManager* al_mngr = getAlbumManager(mngr);
    int artistID = getArtistID(artist);
    int count = 0;

    albumCountArtist(artistID, al_mngr, &count);

    return count;
}

double totalRecipe (AlmightyManager* mngr, Artist* artist) {
    HistoryManager* h_mngr = getHistoryManager(mngr);

    Q1Feeder feeder = { .artist = artist,
                        .mngr = mngr,
                        .total = 0
                      };

    if(!getArtistType(artist)) traverseHistorybyMusic(h_mngr, singleArtist, &feeder);
    else traverseHistorybyMusic(h_mngr, collectiveArtist, &feeder);

    return feeder.total;
}

void singleArtist (gpointer key, gpointer value, gpointer data) {
    Q1Feeder* feeder = (Q1Feeder*) data;
    AlmightyManager* mngr = feeder->mngr;
    MusicManager* m_mngr = getMusicManager(mngr);
    ArtistManager* a_mngr = getArtistManager(mngr);

    Artist* artist = feeder->artist;
    int artistID = getArtistID(artist);
    
    Music* currentMusic = lookupMusicHash(m_mngr, GPOINTER_TO_INT(key));
    const int* artistList = getMusicArtistID(currentMusic);
    int constcounter = getMusicArtistIDCount(currentMusic);

    double total = feeder->total;

    for(int i = 0; i < constcounter; i++) {
        Artist* currentArtist = lookupArtistHash(a_mngr, artistList[i]);
            
        if (getArtistType(currentArtist)){
            int currentArtistSize = getArtistIDConstituentCounter(currentArtist);

            if (isArtistInList(getArtistIDConstituent(currentArtist), artistID, currentArtistSize)) {
                double currentArtistRecipe = getArtistRecipePerStream(currentArtist);
                int reproductions = getHistoryListLengthByMusic(value);

                total += (reproductions * currentArtistRecipe) / currentArtistSize;
            }

        } else if (getArtistID(currentArtist) == artistID) {
            double currentArtistRecipe = getArtistRecipePerStream(currentArtist);
            int reproductions = getHistoryListLengthByMusic(value);

            total += (reproductions * currentArtistRecipe);
        }

        deleteArtist(currentArtist);
    }

    deleteMusic(currentMusic);

    feeder->total = total;
}

void collectiveArtist (gpointer key, gpointer value, gpointer data) {
    Q1Feeder* feeder = (Q1Feeder*) data;
    AlmightyManager* mngr = feeder->mngr;
    MusicManager* m_mngr = getMusicManager(mngr);

    Artist* artist = feeder->artist;
    int artistID = getArtistID(artist);
    double recipe_per_stream = getArtistRecipePerStream(artist);

    double total = feeder->total;
    
    Music* currentMusic = lookupMusicHash(m_mngr, GPOINTER_TO_INT(key));
    const int* artistList = getMusicArtistID(currentMusic);
    int constcounter = getMusicArtistIDCount(currentMusic);

    if (isArtistInList(artistList, artistID, constcounter)) {
        int reproductions = getHistoryListLengthByMusic(value);
        total += reproductions * recipe_per_stream;
    }

    deleteMusic(currentMusic);

    feeder->total = total;
}
