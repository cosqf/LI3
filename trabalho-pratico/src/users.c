#include <stdlib.h>
#include <string.h>
#include <parsingUtils.h>
#include <utils.h>
#include "users.h"
#include <string.h>

/* The User struct */
typedef struct user {
    char* username;                    //– identificador único do utilizador;
    char* email;                       //– email de registo do utilizador;
    char* first_name;                  //– primeiro nome do utilizador;
    char* last_name;                   //– apelido do utilizador;
    char* birth_date;                  //– data de nascimento;
    char* country;                     //– país onde a conta do utilizador foi registada;
    char* subscription_type;           //– tipo de subscrição, i.e., normal(0) ou premium(1);
    char* liked_musics_id;             //– lista de identificadores únicos das músicas gostadas pelo utilizador.
    unsigned int liked_musics_count;   //– número de quantas músicas o utlizador gosta
} User;

/* Create a new User */
User* createUser() {
    User* user = malloc(sizeof(User));
    if (mallocErrorCheck (user)) exit (EXIT_FAILURE);
    user->username = NULL;
    user->email = NULL;
    user->first_name = NULL;
    user->last_name = NULL;
    user->birth_date = NULL;
    user->country = NULL;
    user->subscription_type = NULL;
    user->liked_musics_id = NULL;
    user->liked_musics_count = 0;
    return user;
}

/* Destroy a User and free all allocated memory */
void deleteUser(User* user) {
    if (user) {
        free(user->username);
        free(user->email);
        free(user->first_name);
        free(user->last_name);
        free(user->birth_date);
        free(user->country);
        free(user->subscription_type);
        free(user->liked_musics_id);
        free(user);
    }
}

void printUser(const User* user) {
    if (user == NULL) {
        printf("User is NULL\n");
        return;
    }

    printf("Username: %s, Email: %s, First Name: %s, Last Name: %s, Birth Date: %s, "
           "Country: %s, Subscription Type: %s, Liked Musics ID: %s, Liked Musics Count: %u\n",
           user->username ? user->username : "N/A",
           user->email ? user->email : "N/A",
           user->first_name ? user->first_name : "N/A",
           user->last_name ? user->last_name : "N/A",
           user->birth_date ? user->birth_date : "N/A",
           user->country ? user->country : "N/A",
           user->subscription_type ? user->subscription_type : "N/A",
           user->liked_musics_id ? user->liked_musics_id : "N/A",
           user->liked_musics_count);
}

// GETTER

/* Getter for username */
int getUserName(User* user) {
    return atoi (user->username + 1);
}
/* Getter for username in string format */
char* getUserNameString (User* user) {
    return strdup(user->username);
}

/* Getter for email */
char* getUserEmail(User* user) {
    return strdup(user->email);
}

/* Getter for first_name */
char* getUserFirstName(User* user) {
    return strdup(user->first_name);
}

/* Getter for last_name */
char* getUserLastName(User* user) {
    return strdup(user->last_name);
}

/* Getter for birth_date */
Date getUserBirthDate(User* user) {
    return parseDate (user->birth_date);
}
/* Getter for birth_date in string format */
char* getUserBirthDateString (User* user) {
    return strdup (user->birth_date);
}

/* Getter for country */
char* getUserCountry(User* user) {
    return strdup(user->country);
}

/* Getter for subscription_type */
bool getUserSubscriptionType(User* user) {
    char* subscription = user->subscription_type;
    if (strcmp (subscription, "normal") == 0) return 0;
    else if (strcmp (subscription, "premium") == 0) return 1;
    return -1;
}
/* Getter for subscription_type in string format */
char * getUserSubscriptionTypeString (User *user) {
    return strdup (user->subscription_type);
}

/* Getter for liked_musics_id */
int* getUserLikedMusicsID(User* user) {
    char* liked_musics_copy = strdup(user->liked_musics_id);

    int* result = parseIDs(liked_musics_copy, user, Users); 
    free(liked_musics_copy);

    return result;
}

/* Getter for liked_musics_id in string format */
char* getUserLikedMusicsIDString (User *user) {
    return strdup (user->liked_musics_id);
}

/* Getter for liked_musics_count */
int getUserLikedCounter (User* user) {
    return user->liked_musics_count;
}



// SETTERS


/* Setter for username */
void setUserName(User* user, const char* username) {
    if (user->username) free(user->username);  
    user->username = strdup(username);
}

/* Setter for email */
void setUserEmail(User* user, const char* email) {
    if (user->email) free(user->email);  
    user->email = strdup(email);  // 
}

/* Setter for first_name */
void setUserFirstName(User* user, const char* first_name) {
    if (user->first_name) free(user->first_name);  
    user->first_name = strdup(first_name);
}

/* Setter for last_name */
void setUserLastName(User* user, const char* last_name) {
    if (user->last_name) free (user->last_name);  
    user->last_name = strdup(last_name);
}

/* Setter for birth_date */
void setUserBirthDate(User* user, const char* birth_date) {
    if (user->birth_date) free (user->birth_date);  
    user->birth_date = strdup(birth_date);
}

/* Setter for country */
void setUserCountry(User* user, const char* country) {
    if (user->country) free(user->country);  
    user->country = strdup(country);
}

/* Setter for subscription_type */
void setUserSubscriptionType(User* user, const char* subscription_type) {
    if (user->subscription_type) free(user->subscription_type);  
    user->subscription_type = strdup(subscription_type);
}

/* Setter for liked_musics_id */
void setUserLikedMusicsID(User* user, const char* liked_musics_id) {
    if (user->liked_musics_id) free(user->liked_musics_id);  
    user->liked_musics_id = strdup(liked_musics_id);
}

/* Setter for liked_musics_count */
void setUserLikedMusicsCount(User* user, int liked_musics_count) {
    user->liked_musics_count = liked_musics_count;
}
