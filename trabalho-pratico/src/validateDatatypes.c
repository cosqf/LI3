#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <users.h>
#include <musics.h>
#include <artists.h>

#include <validateDatatypes.h>
#include <hashtable.h>
#include <utils.h>

//USERS

// Validates the user as a whole
bool validUser(User* user){
    return (validEmail(getUserEmail(user)) && validBirthdate(getUserBirthDateString(user)) && validSubscription(getUserSubscriptionTypeString(user)));
}

// Validates the user's email, ensuring it's in the correct format (username@lstr.rstr)
bool validEmail(char* email){
    int length = strlen(email);

    char* username = (char*)malloc(length + 1);
    char* lstr = (char*)malloc(length + 1);
    char* rstr = (char*)malloc(length + 1);

    if (sscanf(email, "%[^@]@%[^.].%s", username, lstr, rstr) == 3){
        
        if (isstr(username, 1) && isstr(lstr, 0) && isstr(rstr, 0)){

            if (strlen(rstr) == 2 || strlen(rstr) == 3){
                free(username);
                free(lstr);
                free(rstr);                
                return true;
            }
        }
    }

    free(username);
    free(lstr);
    free(rstr);

    return false;
}

// Validates the user's birthdate, ensuring it's in the correct format (aaa/mm/dd)
bool validBirthdate(char* bdate){
    int year, month, day;

    if (sscanf(bdate, "%d/%d/%d", &year, &month, &day) != 3) return false;

    else if (year > 2024) return false;

    else if (year == 2024){
        if (month > 9) return false;
        else if (month == 9 && (day < 1 || day > 9)) return false;
    }

    else if (month < 1 || month > 12 || day < 1 || day > 31) return false;

    return true;
}

// Validates the user's subscription type, ensuring it's either "normal" or "premium"
bool validSubscription(char* subs){

    if (strcmp(trimString(subs), "normal") == 0 || strcmp(trimString(subs), "premium") == 0) return true;

    return false;
}

// Validates the liked musics IDs of the user, ensuring they are all existent and valid musics.
bool validLikes(int* liked_musics_id, int liked_musics_count){
    // for(int i = 0; i < liked_musics_count; i++){
        // 
    // }
}


//MUSICS

// Validates the music as a whole
bool validMusic(Music* music){
    return (validDuration(getMusicDuration(music)) && validArtistId(getMusicArtistID(music), getMusicArtistIDCount(music)));
}

// Validates the music's duration, ensuring it's in the correct format (hh:mm:ss)
bool validDuration(Duration duration){

    if (duration.error == 0){
        if (duration.hours >= 0 && duration.hours <= 99 && duration.minutes >= 0 && duration.minutes <= 59 && duration.seconds >= 0 && duration.seconds <= 59) return true;
    }

    return false;
}

// Validates the music's artist ID, ensuring they are all existent and valid artists
bool validArtistId(int* id, int n){    
    int i;

    for(i = 0; i < n && g_hash_table_lookup(hashArtist, (gpointer) id[i]) != NULL; i++);

    if (i == n) return true;

    return false;
}


//ARTISTS

// Validates the artist as a whole
bool validArtist(Artist* artist){
    return (validIdConst(getArtistTypeString(artist), getArtistIDConstituentCounter(artist)));
}

// Validates the artist's ID constituent, ensuring an artist of type 'individual' doesn't have any element in this field
bool validIdConst(char* type, int constituents){

    if(strcmp(trimString(type), "individual") == 0 && constituents != 0) return false;

    return true;
}