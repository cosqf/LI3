#include <parsingUtils.h>
#include <getdata.h>
#include <validation.h> 
#include <hashtable.h>
#include <validateUser.h> //ALTparseDataU (l30)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <parsingDatatypes.h>
#include <users.h>
#include <artists.h>
#include <musics.h>

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
        User *user = createUser();
        if (mallocErrorCheck (user)) exit (EXIT_FAILURE);

        user = fetchDataU (str, user);
        if (!user) insertErrorFileUser (user);
        //else g_hash_table_insert(hashUser, getUserName (user), user);


        //printf ("GETDATA:\nuser: %d\nemail:%s\nfirst name:%s\nlast name:%s\nbirthdate: %d/%d/%d\ncountry:%s\nsubscription:%d\nno. of liked songs: %d\nliked songs:", user->username, user->email, user->first_name, user->last_name, user->birth_date.year, user->birth_date.month, user->birth_date.day, user->country, user->subscription_type, user->liked_musics_count); //DEBUG

        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        // User *myLookup = (User *) g_hash_table_lookup(hashUser, &user->username);
        // printf("Username: %d, Email: %s, Primeiro Nome: %s\n", myLookup->username, myLookup->email, myLookup->first_name);
       
        
        //printUser (user); 
        deleteUser (user);
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
        Artist *artist = createArtist();
        if (mallocErrorCheck (artist)) exit (EXIT_FAILURE);
        artist = fetchDataA (str, artist);
        if (!artist) insertErrorFileArtists (artist);
        // poeNaHash (music);
        
        //printArtist (artist);
        deleteArtist (artist);
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
        Music *music = createMusic ();
        if (mallocErrorCheck (music)) exit (EXIT_FAILURE);

        music = fetchDataM (str, music);
        if (!music) insertErrorFileMusics (music);

        //printMusic (music);
        
        // poeNaHash (music);
        deleteMusic (music);
    }
    fclose(fp);
    free (musicPath);
}