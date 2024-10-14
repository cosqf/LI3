#include <parsingUtils.h>
#include <getdata.h>
#include <validation.h> 
#include <hashtable.h>
#include <validateDatatypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <parsingDatatypes.h>
#include <users.h>
#include <artists.h>
#include <musics.h>

/* 1. Artists, because it doesn't mess with any other hashtable
   2. Musics, because it needs the artists' hastable for validation
   3. Users, because it needs the musics' hashtable for validation
*/

void getData (char *path) {
    getDataArtist (path);
    getDataMusic (path);
    getDataUser (path);
}

char * changePath(char *path, DataType type) {
    const char* file;

    if (type == Users) file = "/users.csv";
    else if (type == Musics) file = "/musics.csv";
    else file = "/artists.csv";

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
    FILE * ferror = openErrorFileUser ();

    bool i = 0;
    char str[DEFAULT];
    
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i = 1;
            continue; // skip first line
        }
        User *user = createUser();
        if (mallocErrorCheck (user)) exit (EXIT_FAILURE);

        user = fetchDataU (str, user);

        if (!validUser (user)) insertErrorFileUser(user, ferror);
        else g_hash_table_insert(hashUser, GINT_TO_POINTER (getUserName (user)), user);

        //printf ("GETDATA:\nuser: %d\nemail:%s\nfirst name:%s\nlast name:%s\nbirthdate: %d/%d/%d\ncountry:%s\nsubscription:%d\nno. of liked songs: %d\nliked songs:", user->username, user->email, user->first_name, user->last_name, user->birth_date.year, user->birth_date.month, user->birth_date.day, user->country, user->subscription_type, user->liked_musics_count); //DEBUG

        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        //User *myLookup = (User *) g_hash_table_lookup(hashUser, getUserName (user));
        //printf("Username: %d, Email: %s, Primeiro Nome: %s\n", getUserName (myLookup), getUserEmail (myLookup), getUserFirstName (myLookup));
       
        
        //printUser (user); 
        deleteUser (user);
    }
    fclose(fp);
    fclose(ferror);
    free (userPath);
}

void getDataArtist (char *path) {
    char *artistPath = changePath (path, Artists);

    FILE* fp = openFile (artistPath);
    FILE * ferror = openErrorFileArtists ();

    bool i = 0;
    char str[DEFAULT];
    
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i = 1;
            continue; // skip first line
        }
        Artist *artist = createArtist();
        if (mallocErrorCheck (artist)) exit (EXIT_FAILURE);

        artist = fetchDataA (str, artist);

        if (!validArtist(artist)) insertErrorFileArtists(artist, ferror);
        else g_hash_table_insert(hashArtist, GINT_TO_POINTER (getArtistID (artist)), artist);
        
        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        //Artist *myLookup = (Artist *) g_hash_table_lookup(hashArtist, getArtistID (artist));
        //printf("ID: %d, Nome: %s, Descrição: %s\n", getArtistID (myLookup), getArtistName (myLookup), getArtistDescription (myLookup));
      

        //printArtist (artist);
        deleteArtist (artist);
    }
    fclose(fp);
    free (artistPath);
}

void getDataMusic (char *path) {
    char *musicPath = changePath (path, Musics);

    FILE* fp = openFile (musicPath);
    FILE * ferror = openErrorFileMusics ();

    bool i = 0;
    char str[DEFAULT];
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i = 1;
            continue; // skip first line
        }
        Music *music = createMusic ();
        if (mallocErrorCheck (music)) exit (EXIT_FAILURE);

        music = fetchDataM (str, music);

        if (!validMusic (music)) insertErrorFileMusics(music, ferror);
        else g_hash_table_insert(hashMusic, GINT_TO_POINTER (getMusicID (music)), music);
        
        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        //Music *myLookup = (Music *) g_hash_table_lookup(hashMusic, getMusicID (music));
        //printf("ID: %d, Genero: %s, Titulo: %s\n", getMusicID (myLookup), getMusicGenre (myLookup), getMusicTitle (myLookup));
    
        //printMusic (music);
        deleteMusic (music);
    }
    fclose(fp);
    free (musicPath);
}