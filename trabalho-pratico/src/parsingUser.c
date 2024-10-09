#include <parsingUtils.h>
#include <validateUser.h>
#include <validation.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <parsingUser.h>


UserRaw * fetchDataU (char *str, UserRaw *user) {
    if (!str || !user) return NULL;
    char *token = NULL;
    
    // Fetching the ID
    token = trimString(strsep(&str, ";"));
    if (token) user->username = strdup(token);
    else {
        perror ("Id fetching error");
        return NULL;
    }

    // Fetching the email
    token = trimString(strsep(&str, ";"));
    if (token) user->email = strdup(token);
    else {
        perror ("Email fetching error");
        return NULL;
    }

    // Fetching first name
    token = trimString(strsep(&str, ";"));
    if (token) user->first_name = strdup(token);
    else {
        perror ("First name fetching error");
        return NULL;
    }

    // Fetching last name
    token = trimString(strsep(&str, ";"));
    if (token) user->last_name = strdup(token);
    else {
        perror ("Last name fetching error");
        return NULL;
    }

    // Fetching birth date
    token = trimString(strsep(&str, ";"));
    if (token) user->birth_date = strdup(token);
    else {
        perror ("Birth date fetching error");
        return NULL;
    }

    // Fetching country
    token = trimString(strsep(&str, ";"));
    if (token) user->country = strdup(token);
    else {
        perror ("Country fetching error");
        return NULL;
    }

    // Fetching subscription type

    token = trimString(strsep(&str, ";"));
    if (token) user->subscription_type = strdup(token);
    else {
        perror ("Subscription type fetching error");
        return NULL;
    }

    // Fetching liked musics ID

    token = trimString(strsep(&str, ";"));
    if (token) user->liked_musics_id = strdup(token);
    else {
        perror ("liked musics ID fetching error");
        return NULL;
    }
    return user;
}

User* parseDataU(User *user, UserRaw *raw) {
    char * username = raw->username;
    user->username = atoi (username + 1);

    if (validEmail (raw->email)) {
        user->email = strdup (raw->email);
    }
    else return NULL;

    user->first_name = strdup (raw->first_name);

    user->last_name = strdup (raw->last_name);

    Date birthday = parseDate (raw->birth_date);
    if (birthday.error == 1) return NULL;
    else user->birth_date = birthday;

    user->country = strdup (raw->country);

    char* subscription = raw->subscription_type;
    if (strcmp (subscription, "normal") == 0) user->subscription_type = 0;
    else if (strcmp (subscription, "premium") == 0) user->subscription_type = 1;
    else return NULL;
    
    int * ids = parseIDs (raw->liked_musics_id, user, Users);
    user->liked_musics_id = ids;

    return user;
}