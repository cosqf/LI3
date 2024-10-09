#include <parsingUtils.h>
#include <getdata.h>
#include <validation.h> 
#include <hashtable.h>
#include <validateUser.h> //ALTparseDataU (l30)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <freeFunctions.h>
#include <parsingUser.h>
#include <parsingArtist.h>
#include <parsingMusic.h>

void getData (char *path) {
    //getDataUser (path);
    //getDataArtist (path);
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
        UserRaw *userRaw = malloc (sizeof (UserRaw));
        if (mallocErrorCheck (userRaw)) exit (EXIT_FAILURE);

        userRaw = fetchDataU (str, userRaw);
        if (!userRaw) {
            perror ("Fetching User error");
            exit (EXIT_FAILURE);
        }
        User *user = malloc (sizeof (User));
        if (mallocErrorCheck (user)) exit (EXIT_FAILURE);
        user = parseDataU (user, userRaw);
        if (!user) insertErrorFileUser (userRaw);
        else g_hash_table_insert(hashUser, &user->username, user);


        //printf ("GETDATA:\nuser: %d\nemail:%s\nfirst name:%s\nlast name:%s\nbirthdate: %d/%d/%d\ncountry:%s\nsubscription:%d\nno. of liked songs: %d\nliked songs:", user->username, user->email, user->first_name, user->last_name, user->birth_date.year, user->birth_date.month, user->birth_date.day, user->country, user->subscription_type, user->liked_musics_count); //DEBUG

        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        // User *myLookup = (User *) g_hash_table_lookup(hashUser, &user->username);
        // printf("Username: %d, Email: %s, Primeiro Nome: %s\n", myLookup->username, myLookup->email, myLookup->first_name);
       
        
        //printf ("GETDATA:\nuser: %d\nemail:%s\nfirst name:%s\nlast name:%s\nbirthdate: %s\ncountry:%s\nsubscription:%d\nno. of liked songs: %d\nliked songs:", user->username, user->email, user->first_name, user->last_name, user->buffer, user->country, user->subscription_type, user->liked_musics_count); //DEBUG
        //for (int i = 0; i<user->liked_musics_count; i++) printf ("%d\t", user->liked_musics_id[i]); //DEBUG
        //printf ("\n\n"); //DEBUG
        freeUser (user);
        freeUserRaw (userRaw);
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
        ArtistRaw *artistRaw = malloc (sizeof (ArtistRaw));
        if (mallocErrorCheck (artistRaw)) exit (EXIT_FAILURE);

        artistRaw = fetchDataA (str, artistRaw);
        if (!artistRaw) {
            perror ("Fetching artist error");
            exit (EXIT_FAILURE);
        }


        Artist *artist = malloc (sizeof (Artist));
        if (mallocErrorCheck (artist)) exit (EXIT_FAILURE);
        artist = parseDataA (artist, artistRaw);
        if (!artist) insertErrorFileArtists (artistRaw);
        // poeNaHash (music);

        freeArtist (artist);
        freeArtistRaw (artistRaw);
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
        MusicRaw *musicRaw = malloc (sizeof (MusicRaw));
        if (mallocErrorCheck (musicRaw)) exit (EXIT_FAILURE);

        musicRaw = fetchDataM (str, musicRaw);
        if (!musicRaw) {
            perror ("Fetching artist error");
            exit (EXIT_FAILURE);
        }

        Music *music = malloc (sizeof (Music));
        if (mallocErrorCheck (music)) exit (EXIT_FAILURE);
        music = parseDataM (music, musicRaw);
        if (!music) insertErrorFileMusics (musicRaw);

        //printf ("%d, %s, %d, %s, %s, %d, %s\n", music->id, music->title, music->artist_id_counter, music->buffer, music->genre, music->year, music->lyrics); // DEBUG
        //for (int i=0; i < music->artist_id_counter; i++) printf ("%d ", music->artist_id[i]);
        //printf ("\n\n");
        
        // poeNaHash (music);
        freeMusic (music);
        freeMusicRaw (musicRaw);
    }
    fclose(fp);
    free (musicPath);
}