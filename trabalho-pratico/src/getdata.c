#include <processInput.h>
#include <getdata.h>
#include <validateUser.h> //ALTparseDataU (l30)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <freeFunctions.h>

void getData (char *path) {
    getDataUser (path);
    getDataArtist (path);
    getDataMusic (path);
}

char * changePath(char *path, DataType type) {
    const char* file;

    if (type == Users) file = "users.csv";
    else if (type == Musics) file = "musics.csv";
    else file = "artists.csv";

    char *pathUpdated = malloc(strlen(path) + strlen(file) + 1); 
    if (pathUpdated) {
        strcpy(pathUpdated, path); 
        strcat(pathUpdated, file); 
    }
    return pathUpdated;
}

void getDataUser (char *path) {
    char* userPath = changePath (path, Users);

    FILE* fp = openFile (userPath);
    bool i = 0;
    char str[DEFAULT];
    
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i = 1;
            continue; // skip first line
        }
        User *user = malloc (sizeof (User));
        if (mallocErrorCheck (user)) exit (EXIT_FAILURE);

        user = parseDataU (str, user);
        // filtra (user)
        // poeNaHash (user);
        //printf ("GETDATA:\nuser: %d\nemail:%s\nfirst name:%s\nlast name:%s\nbirthdate: %s\ncountry:%s\nsubscription:%d\nno. of liked songs: %d\nliked songs:", user->username, user->email, user->first_name, user->last_name, user->buffer, user->country, user->subscription_type, user->liked_musics_count); //DEBUG
        //for (int i = 0; i<user->liked_musics_count; i++) printf ("%d\t", user->liked_musics_id[i]); //DEBUG
        //printf ("\n\n"); //DEBUG
        freeUser (user);
    }
    fclose(fp);
    free (userPath);
}

void getDataArtist (char *path) {
    char *artistPath = changePath (path, Artists);

    
    FILE* fp = openFile (artistPath);
    bool i = 0;
    char str[DEFAULT];
    
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i = 1;
            continue; // skip first line
        }
        Artist *artist = malloc (sizeof (Artist));
        if (mallocErrorCheck (artist)) exit (EXIT_FAILURE);
        artist = parseDataA (str, artist);
        // filtra (artist)
        // poeNaHash (music);
        freeArtist (artist);
    }
    fclose(fp);
    free (artistPath);
}

void getDataMusic (char *path) {
    char *musicPath = changePath (path, Musics);
    FILE* fp = openFile (musicPath);
    bool i = 0;
    char str[DEFAULT];
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i = 1;
            continue; // skip first line
        }
        Music *music = malloc (sizeof (Music));
        if (mallocErrorCheck (music)) exit (EXIT_FAILURE);
        music = parseDataM (str, music);
        //printf ("%d, %s, %d, %s, %s, %d, %s\n", music->id, music->title, music->artist_id_counter, music->buffer, music->genre, music->year, music->lyrics); // DEBUG
        //for (int i=0; i < music->artist_id_counter; i++) printf ("%d ", music->artist_id[i]);
        //printf ("\n\n");
        // filtra (music)
        // poeNaHash (music);
        freeMusic (music);
    }
    fclose(fp);
    free (musicPath);
}