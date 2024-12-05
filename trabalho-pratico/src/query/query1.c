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


void query1(CMD* cmd, hashtableManager* mngr, int counter) {
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


void artistinfo (CMD* cmd, hashtableManager* mngr, Artist* artist, Output* file) {
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

int individualAlbums(hashtableManager* mngr, Artist* artist) {
    AlbumManager* al_mngr = getAlbumManager(mngr);
    int artistID = getArtistID(artist);
    int count = 0;

    albumCountArtist(artistID, al_mngr, &count);

    return count;
}

double singleArtist (GHashTable* hashtable, Artist* artist, hashtableManager* mngr) {
    MusicManager* m_mngr = getMusicManager(mngr);
    ArtistManager* a_mngr = getArtistManager(mngr);

    GHashTableIter iter;
    gpointer key, value;

    double total = 0;
    int artistID = getArtistID(artist);
    double recipe_per_stream = getArtistRecipePerStream(artist);

    g_hash_table_iter_init(&iter, hashtable);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {

        Music* currentMusic = lookupMusicHash(m_mngr, GPOINTER_TO_INT(key));
        const int* artistList = getMusicArtistID(currentMusic);
        int constcounter = getMusicArtistIDCount(currentMusic);

        if ((constcounter == 1 && artistList[0] == artistID) || isArtistInList(artistList, artistID, constcounter)) {
            int reproductions = getHistoryListLengthByMusic(value);
            total += artistRecipe(reproductions, recipe_per_stream);

        } else if (artistParticipation(a_mngr, artistList, artistID, constcounter)) {
            int reproductions = getHistoryListLengthByMusic(value);
            total += artistRecipe(reproductions, recipe_per_stream);
        }
    }

    return total;
}

bool artistParticipation (ArtistManager* a_mngr, const int* ids, int artistID, int length) {
    for(int i = 0; i < length; i++) {
        if (ids[i] == artistID) return true;
        Artist* currentID = lookupArtistHash(a_mngr, ids[i]);
        if (getArtistType(currentID)) return isArtistInList(getArtistIDConstituent(currentID), artistID, length);
    }
    return false;
}



double collectiveArtist (GHashTable* hashtable, Artist* artist, hashtableManager* mngr) {
    MusicManager* m_mngr = getMusicManager(mngr);

    GHashTableIter iter;
    gpointer key, value;
    double total = 0;
    int artistID = getArtistID(artist);
    
    double recipe_per_stream = getArtistRecipePerStream(artist);

    g_hash_table_iter_init(&iter, hashtable);
    
    while (g_hash_table_iter_next(&iter, &key, &value)) {

        Music* currentMusic = lookupMusicHash(m_mngr, GPOINTER_TO_INT(key));
        const int* currentArtist = getMusicArtistID(currentMusic);

        if (*currentArtist && currentArtist[0] == artistID) {
            int reproductions = getHistoryListLengthByMusic(value);
            total += artistRecipe(reproductions, recipe_per_stream);
        }
    }

    return total;
}

double artistRecipe (int reproductions, double recipe_per_stream) {
    return reproductions * recipe_per_stream;
}

double participationRecipe (int reproductions, double recipe_per_stream, int constituents) {
    return (reproductions * recipe_per_stream) / constituents;
}
