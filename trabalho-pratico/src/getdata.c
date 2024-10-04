#include <processInput.h>
#include <getdata.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void getData (char *path) {
    getDataUser (path);
    getDataArtist (path);
    getDataMusic (path);
}

void getDataUser (char *path) {
    char *userPath = strcat (path, "users.csv");
    FILE* fp = fopen (userPath, "r");
    if (!fp) {
        perror("Error: File didn't open");
        exit(EXIT_FAILURE);
    }
    short int i = 0;
    char str[DEFAULT];
    User *user = malloc (sizeof (User));
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i++;
            continue; // skip first line
        }

        user = parseDataU (str, user);
        // filtra (user)
        // poeNaHash (user);
        printf ("GETDATA:\nuser: %d\nemail:%s\nfirst name:%s\nlast name:%s\nbirthdate: %s\ncountry:%s\nsubscription:%d\nno. of liked songs: %d\nliked songs:", user->username, user->email, user->first_name, user->last_name, user->buffer, user->country, user->subscription_type, user->liked_musics_count); //DEBUG
        for (int i = 0; i<user->liked_musics_count; i++) printf ("%d\t", user->liked_musics_id[i]); //DEBUG
        printf ("\n\n"); //DEBUG
    }
    fclose(fp);
}

void getDataArtist (char *path) {
    char *artistPath = strcat (path, "artists.csv");
    FILE* fp = fopen (artistPath, "r");
    if (!fp) {
        perror("Error: File didn't open");
        exit(EXIT_FAILURE);
    }
    short int i = 0;
    char str[DEFAULT];
    User *artist = malloc (sizeof (Artists));
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i++;
            continue; // skip first line
        }

        artist = parseDataU (str, artist);
        // filtra (artist)
        // poeNaHash (music);
    }
    fclose(fp);
}

void getDataMusic (char *path) {
    char *musicPath = strcat (path, "musics.csv");
    FILE* fp = fopen (musicPath, "r");
    if (!fp) {
        perror("Error: File didn't open");
        exit(EXIT_FAILURE);
    }
    short int i = 0;
    char str[DEFAULT];
    User *music = malloc (sizeof (Artists));
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i++;
            continue; // skip first line
        }

        music = parseDataU (str, music);
        // filtra (music)
        // poeNaHash (music);
    }
    fclose(fp);
}

void freeUser(User *user) {
    if (user) {
        free(user->email);
        free(user->first_name);
        free(user->last_name);
        free(user->country);
        free(user->liked_musics_id); 
        free(user);
    }
}