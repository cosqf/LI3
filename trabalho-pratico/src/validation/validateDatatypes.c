#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <users.h>
#include <musics.h>
#include <artists.h>

#include <validateDatatypes.h>
#include <utils.h>
#include <validation.h>

#include <artistManager.h>
#include <musicManager.h>

//USERS

// Validates the user as a whole
bool validUser(UserString* user, MusicManager *m_mngr){
    char* email = getUserEmailString(user);
    char* birthdate = getUserBirthDateString(user);
    char* subscription = getUserSubscriptionTypeString(user);
    char* likedMusicsString = getUserLikedMusicsIDString(user);
    int* likedMusics = getUserLikedMusicsIDStringArray(user);
    int likedMusicsCount = getUserLikedCounterString(user);

    bool valid = (validEmail(email) && validBirthdate(birthdate) && validSubscription(subscription) && validList(likedMusicsString) && validLikes(likedMusics, likedMusicsCount, m_mngr));
    
    free (email);
    free (birthdate);
    free (subscription);
    free (likedMusicsString);
    free (likedMusics);
    
    return valid;
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
bool validLikes(int* liked_musics_id, int liked_musics_count, MusicManager *m_mngr){
    int i;

    for(i = 0; i < liked_musics_count && lookupMusicHash (m_mngr, liked_musics_id[i]) != NULL; i++);
    
    if (i == liked_musics_count) return true;

    return false;
}


//MUSICS

// Validates the music as a whole
bool validMusic(MusicString* music, ArtistManager *a_mngr){
    Duration dur = parseDuration (getMusicDurationString(music));
    char* idsString = getMusicArtistIDString(music);
    int* ids =  parseIDs (getMusicArtistIDString (music));
    int artistIDCount = getMusicArtistIDCountString(music);

    bool valid = (validDuration(dur) && validList(idsString) && validArtistId(ids, artistIDCount, a_mngr));

    free (idsString);
    free (ids);
    
    return valid;
}

// Validates the music's duration, ensuring it's in the correct format (hh:mm:ss)
bool validDuration(Duration duration){

    if (duration.error == 0){
        if (duration.hours >= 0 && duration.hours <= 99 && duration.minutes >= 0 && duration.minutes <= 59 && duration.seconds >= 0 && duration.seconds <= 59) return true;
    }

    return false;
}

// Validates the music's artist ID, ensuring they are all existent and valid artists
bool validArtistId(int* id, int n, ArtistManager *a_mngr){    
    int i;

    for(i = 0; i < n && lookupArtistHash (a_mngr, id[i]) != NULL; i++);
    

    if (i == n) return true;

    return false;
}


//ARTISTS

// Validates the artist as a whole
bool validArtist(ArtistString* artist){
    char* type = getArtistTypeString(artist);
    int constituentCounter = getArtistIDConstituentCounterString(artist);
    char* constituents = getArtistIDConstituentString(artist);

    bool valid = (validList(constituents) && validIdConst(type, constituentCounter));

    free (type);
    free (constituents);

    return valid;
}

// Validates the artist's ID constituent, ensuring an artist of type 'individual' doesn't have any element in this field
bool validIdConst(char* type, int constituents){

    if(strcmp(trimString(type), "individual") == 0 && constituents != 0) return false;

    return true;
}


//LISTS

// Validates lists of IDs, ensuring they start and end with the proper brackets
bool validList (char* idList) {
    int length = strlen(idList);
        
    if(length < 2 || idList[0] != '[' || idList[length-1] != ']') return false;

    return true;
}