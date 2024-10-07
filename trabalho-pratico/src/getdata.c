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

        user = ALTparseDataU (str, user);
        // filtra (user)
        // poeNaHash (user);
        //printf ("GETDATA:\nuser: %d\nemail:%s\nfirst name:%s\nlast name:%s\nbirthdate: %s\ncountry:%s\nsubscription:%d\nno. of liked songs: %d\nliked songs:", user->username, user->email, user->first_name, user->last_name, user->buffer, user->country, user->subscription_type, user->liked_musics_count); //DEBUG
        //for (int i = 0; i<user->liked_musics_count; i++) printf ("%d\t", user->liked_musics_id[i]); //DEBUG
        //printf ("\n\n"); //DEBUG
    }
    fclose(fp);
    freeUser (user);
}

void getDataArtist (char *path) {
    char *artistPath = strcat (path, "artists.csv");
    FILE* fp = fopen (artistPath, "r");
    if (!fp) {
        perror("Error: File didn't open");
        exit(EXIT_FAILURE);
    }
    short unsigned int i = 0;
    char str[DEFAULT];
    Artist *artist = malloc (sizeof (Artist));
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i++;
            continue; // skip first line
        } 
        artist = parseDataA (str, artist);
        // filtra (artist)
        // poeNaHash (music);
        // free (artist) ?
    }
    fclose(fp);
    freeArtist (artist);
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
    Music *music = malloc (sizeof (Music));
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i++;
            continue; // skip first line
        }

        music = parseDataM (str, music);
        //printf ("%d, %s, %d, %s, %s, %d, %s\n", music->id, music->title, music->artist_id_counter, music->buffer, music->genre, music->year, music->lyrics); // DEBUG
        //for (int i=0; i < music->artist_id_counter; i++) printf ("%d ", music->artist_id[i]);
        //printf ("\n\n");
        // filtra (music)
        // poeNaHash (music);
        // free (music) ?
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