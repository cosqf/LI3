#include <stdlib.h>
#include <string.h>
#include <parsingUtils.h>
#include <utils.h>
#include <users.h>
#include <string.h>

/* The User struct */
typedef struct user {
    char* id;                    //– identificador único do utilizador;
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
User* createUser (char** tokens) {
    User* user = malloc(sizeof(User));
    if (mallocErrorCheck (user)) exit (EXIT_FAILURE);

    user->id = strdup (trimString((tokens[0])));
    user->email = strdup (trimString((tokens[1])));
    user->first_name = strdup (trimString((tokens[2])));
    user->last_name = strdup (trimString((tokens[3])));
    user->birth_date = strdup (trimString((tokens[4])));
    user->country = strdup (trimString((tokens[5])));
    user->subscription_type = strdup (trimString((tokens[6])));
    user->liked_musics_id = strdup (trimStringWithoutBrackets((tokens[7])));
    user->liked_musics_count = IdCounter ((tokens[7]));
    return user;
}

/* Destroy a User and free all allocated memory */
void deleteUser(User* user) {
    if (user) {
        free(user->id);
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

    printf("id: %s, Email: %s, First Name: %s, Last Name: %s, Birth Date: %s, "
           "Country: %s, Subscription Type: %s, Liked Musics ID: %s, Liked Musics Count: %u\n",
           user->id ? user->id : "N/A",
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

/* Getter for id */
int getUserID(User* user) {
    return atoi (user->id + 1);
}
/* Getter for id in string format */
char* getUserIDString (User* user) {
    return strdup(user->id);
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
    char* liked_musics_copy = strdup((trimString(user->liked_musics_id)));
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


/* Setter for id */
void setUserID(User* user, const char* id) {
    if (user->id) free(user->id);  
    user->id = strdup(id);
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
