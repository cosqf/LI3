#include <parsingUtils.h>
#include <getdata.h>
#include <validation.h> 
#include <validateDatatypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <parsingDatatypes.h>
#include <users.h>
#include <artists.h>
#include <musics.h>
#include <entityManager.h>

/* 1. Artists, because it doesn't mess with any other hashtable
   2. Musics, because it needs the artists' hastable for validation
   3. Users, because it needs the musics' hashtable for validation
*/

void getData (char *path, EntityManager *mngr) {
    getDataArtist (path, getArtistManager (mngr));
    getDataMusic (path, getMusicManager (mngr), getArtistManager(mngr));
    getDataUser (path, getUserManager(mngr), getMusicManager(mngr));
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

void getDataUser (char *path, UserManager *u_mngr, MusicManager *m_mngr) {
    char* userPath = changePath (path, Users);
    FILE* fp = openFile (userPath);
    FILE* ferror = openErrorFileUser ();

    bool i = 0;
    char str[DEFAULT];
    
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i = 1;
            continue; // skip first line (header)
        }
        User *user = createUser();
        if (mallocErrorCheck (user)) {
            free (user);
            exit (EXIT_FAILURE);
        }

        fetchDataU (str, user);

        if (!validUser (user, m_mngr)) {
            insertErrorFileUser(user, ferror);
            deleteUser (user);
        }
        else insertUserHash (u_mngr, getUserID (user), user);

        //printf ("GETDATA:\nuser: %d\nemail:%s\nfirst name:%s\nlast name:%s\nbirthdate: %d/%d/%d\ncountry:%s\nsubscription:%d\nno. of liked songs: %d\nliked songs:", user->username, user->email, user->first_name, user->last_name, user->birth_date.year, user->birth_date.month, user->birth_date.day, user->country, user->subscription_type, user->liked_musics_count); //DEBUG

        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        //User *myLookup = (User *) g_hash_table_lookup(hashUser, getUserName (user));
        //printf("Username: %d, Email: %s, Primeiro Nome: %s\n", getUserName (myLookup), getUserEmail (myLookup), getUserFirstName (myLookup));
       
        
        //printUser (user); 
    }
    fclose(fp);
    fclose(ferror);
    free (userPath);
}


void getDataArtist (char *path, ArtistManager *mngr) {
    char *artistPath = changePath (path, Artists);

    FILE* fp = openFile (artistPath);
    FILE * ferror = openErrorFileArtists ();

    bool i = 0;
    char str[DEFAULT];
    
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i = 1;
            continue; // skip first line (header)
        }
        Artist *artist = createArtist();
        if (mallocErrorCheck (artist)) {
            free (artist);
            exit (EXIT_FAILURE);
        }
        fetchDataA (str, artist);

        if (!validArtist(artist)) {
            insertErrorFileArtists(artist, ferror);
            deleteArtist (artist);
        }
        else insertArtistHash (mngr, getArtistID (artist), artist);
        
        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        //Artist *myLookup = (Artist *) g_hash_table_lookup(hashArtist, getArtistID (artist));
        //printf("ID: %d, Nome: %s, Descrição: %s\n", getArtistID (myLookup), getArtistName (myLookup), getArtistDescription (myLookup));
      

        //printArtist (artist);
    }
    fclose(fp);
    fclose (ferror);
    free (artistPath);
}

void getDataMusic (char *path, MusicManager *m_mngr, ArtistManager *a_mngr) {
    char *musicPath = changePath (path, Musics);

    FILE* fp = openFile (musicPath);
    FILE* ferror = openErrorFileMusics ();

    bool i = 0;
    char str[DEFAULT];
    while (fgets (str, sizeof (str), fp) != NULL){
        if (i==0) {
            i = 1;
            continue; // skip first line (header)
        }
        Music *music = createMusic ();
        if (mallocErrorCheck (music)) {
            free (music);
            exit (EXIT_FAILURE);
        }

        fetchDataM (str, music);

        if (!validMusic (music, a_mngr)) {
            insertErrorFileMusics(music, ferror);
            deleteMusic (music);
        }
        else insertMusicHash (m_mngr, getMusicID (music), music);

        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        //Music *myLookup = (Music *) g_hash_table_lookup(hashMusic, getMusicID (music));
        //printf("ID: %d, Genero: %s, Titulo: %s\n", getMusicID (myLookup), getMusicGenre (myLookup), getMusicTitle (myLookup));
    
        //printMusic (music);
        //deleteMusic (music);
    }
    fclose(fp);
    fclose (ferror);
    free (musicPath);
}