#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <users.h>
#include <musics.h>
#include <artists.h>
#include <history.h>

#include <validateDatatypes.h>
#include <utils.h>
#include <parsingUtils.h>
#include <output_handling/errorfiles.h>

#include <artistManager.h>
#include <musicManager.h>

//USERS

// Validates the user as a whole
bool validUser(UserString* user, MusicManager *m_mngr){
    char* email = getUserEmailString(user);
    char* birthdate = getUserBirthDateString(user);
    char* subscription = getUserSubscriptionTypeString(user);
    char* likedMusicsString = getUserLikedMusicsIDString(user);
    const int* likedMusics = getUserLikedMusicsIDStringArray(user);
    int likedMusicsCount = getUserLikedCounterString(user);

    bool valid = (validEmail(email) && validBirthdate(birthdate) && validSubscription(subscription) && validList(likedMusicsString) && validLikes(likedMusics, likedMusicsCount, m_mngr));
    
    free (email);
    free (birthdate);
    free (subscription);
    free (likedMusicsString);
    free ((int*)likedMusics);
    
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

// Validates the user's birthdate, ensuring it's in the correct format (aaa/mm/dd) and not more recent than 09/09/2024
bool validBirthdate(char* bdate){
    Date birthdate = parseDate(bdate);

    if(birthdate.error == 1) return false;

    else if (birthdate.year > 2024) return false;

    else if (birthdate.year == 2024){
        if (birthdate.month > 9) return false;
        else if (birthdate.month == 9 && (birthdate.day < 1 || birthdate.day > 9)) return false;
    }

    else if (birthdate.month < 1 || birthdate.month > 12 || birthdate.day < 1 || birthdate.day > 31) return false;

    return true;
}

// Validates the user's subscription type, ensuring it's either "normal" or "premium"
bool validSubscription(char* subs){

    if (strcmp(trimString(subs), "normal") == 0 || strcmp(trimString(subs), "premium") == 0) return true;

    return false;
}

// Validates the liked musics IDs of the user, ensuring they are all existent and valid musics.
bool validLikes(const int* liked_musics_id, int liked_musics_count, MusicManager *m_mngr){
    int i;

    for(i = 0; i < liked_musics_count && isMusicInHash (m_mngr, liked_musics_id[i]); i++);
    
    if (i == liked_musics_count) return true;

    return false;
}


//MUSICS

// Validates the music as a whole
bool validMusic(MusicString* music, ArtistManager *a_mngr, AlbumManager *al_mngr){
    char* durString = getMusicDurationString(music);
    Duration dur = parseDuration (durString);
    char* idsString = getMusicArtistIDString(music);
    int* ids = parseIDs (idsString);
    int artistIDCount = getMusicArtistIDCountString(music);

    char* albumIDString = getMusicAlbumIDString(music);
    int albumID, temp;
    if (convertToInt (trimString(albumIDString) + 2, &temp)) albumID = temp;
    else {
        perror ("Error converting id in Valid Music\n");
        return 1;
    }

    bool valid = (validDuration(dur) && validList(idsString) && validArtistId(ids, artistIDCount, a_mngr) && validAlbumID(albumID, al_mngr));

    free (albumIDString);
    free (durString);
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

// Validates the music's album ID, ensuring it is an existent and valid album
bool validAlbumID(int id, AlbumManager *al_mngr){

    return isAlbumInHash(al_mngr, id);

}


//ARTISTS

// Validates the artist as a whole
bool validArtist(ArtistString* artist){
    char* artistType = getArtistTypeString(artist);
    char* type = lower(artistType); 
    int constituentCounter = getArtistIDConstituentCounterString(artist);
    char* constituents = getArtistIDConstituentString(artist);

    bool valid = (validList(constituents) && validIdConst(type, constituentCounter) && validType(type));

    free (type);
    free (constituents);
    free (artistType);

    return valid;
}

// Validates the artist's ID constituent, ensuring an artist of type 'individual' doesn't have any element in this field
bool validIdConst(char* type, int constituents){

    if(strcmp(trimString(type), "individual") == 0 && constituents != 0) return false;

    return true;
}

//Validates the artist's type, "individual" or "group"
bool validType(char* type){

    if(strcmp(trimString(type), "individual") == 0 || strcmp(trimString(type), "group") == 0) return true;

    return false;
}


//LISTS

// Validates lists of IDs, ensuring they start and end with the proper brackets
bool validList (char* idList) {
    int length = strlen(idList);
        
    if(length < 2 || idList[0] != '[' || idList[length-1] != ']') return false;

    return true;
}

// Validates the list's artist ID, ensuring they are all existent and valid artists
bool validArtistId(int* id, int n, ArtistManager *a_mngr){    
    int i;

    for(i = 0; i < n && isArtistInHash (a_mngr, id[i]); i++);
    

    if (i == n) return true;

    return false;
}


//HISTORY

// Validates the history entry
bool validHistory(HistoryString* history){
    char* historyPlatform = getHistoryPlatformString(history);
    char* platform = lower(historyPlatform);

    bool valid = validPlatform(platform);

    free(platform);
    free (historyPlatform);

    return valid;
}

// Validates the history entry's platform, "mobile" or "desktop"
bool validPlatform(char* platform){

    if(strcmp(trimString(platform), "mobile") == 0 || strcmp(trimString(platform), "desktop") == 0) return true;

    return false;
}


//ALBUM

// Validates the album as a whole
bool validAlbum(AlbumString* album, ArtistManager* a_mngr){
    char* idsString = getAlbumArtistIdString(album);
    int* ids = parseIDs (idsString);
    int artistIDCount = getAlbumArtistIdCountString(album);

    bool valid = validArtistId(ids, artistIDCount, a_mngr) && validList(idsString);

    free (idsString);
    free (ids);
    
    return valid;
}
