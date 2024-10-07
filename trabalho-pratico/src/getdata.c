#include <processInput.h>
#include <getdata.h>
#include <validateUser.h> //ALTparseDataU (l30)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

    FILE* fp = fopen (userPath, "r");
    if (!fp) {
        perror("Error: File didn't open");
        exit(EXIT_FAILURE);
    }
    short int i = 0;
    char str[DEFAULT];
    
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i++;
            continue; // skip first line
        }
        User *user = malloc (sizeof (User));
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

    FILE* fp = fopen (artistPath, "r");
    if (!fp) {
        perror("Error: File didn't open");
        exit(EXIT_FAILURE);
    }
    short unsigned int i = 0;
    char str[DEFAULT];
    
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i++;
            continue; // skip first line
        }
        Artist *artist = malloc (sizeof (Artist));
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
    FILE* fp = fopen (musicPath, "r");
    if (!fp) {
        perror("Error: File didn't open");
        exit(EXIT_FAILURE);
    }
    short int i = 0;
    char str[DEFAULT];
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i++;
            continue; // skip first line
        }
        Music *music = malloc (sizeof (Music));
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

void freeUser(User *user) {
    if (user) {
        free(user->email);
        free(user->first_name);
        free(user->last_name);
        free(user->country);
        free(user->liked_musics_id);
        if (user->buffer) free (user->buffer);
        free(user);
    }
}

void freeArtist(Artist *artist) {
    if (artist) {
        free (artist->name);
        free (artist->description);
        if (artist->id_constituent_counter>0) free (artist->id_constituent);
        free (artist->country);
        free (artist);
    }
}

void freeMusic (Music *music) {
    if (music) {
        free (music->title);
        if (music->artist_id_counter > 0) free (music->artist_id);
        if (music->buffer) free (music->buffer);
        free (music->genre);
        free (music->lyrics);
        free (music);
    }
}