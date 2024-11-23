#include <stdlib.h>
#include <string.h>
#include <parsingUtils.h>
#include <utils.h>
#include <users.h>
#include <string.h>

/* The User struct */
typedef struct user {
    int id;                             //– identificador único do utilizador;
    char* email;                        //– email de registo do utilizador;
    char* first_name;                   //– primeiro nome do utilizador;
    char* last_name;                    //– apelido do utilizador;
    Date birth_date;                    //– data de nascimento;
    char* country;                      //– país onde a conta do utilizador foi registada;
    int* liked_musics_id;               //– lista de identificadores únicos das músicas gostadas pelo utilizador.
    unsigned int liked_musics_count;    //– número de quantas músicas o utlizador gosta
} User;

/* Temporary User struct */
typedef struct userString {
    char* id;                           //– identificador único do utilizador;
    char* email;                        //– email de registo do utilizador;
    char* first_name;                   //– primeiro nome do utilizador;
    char* last_name;                    //– apelido do utilizador;
    char* birth_date;                   //– data de nascimento;
    char* country;                      //– país onde a conta do utilizador foi registada;
    char* subscription_type;            //– tipo de subscrição, i.e., normal(0) ou premium(1);
    char* liked_musics_id;              //– lista de identificadores únicos das músicas gostadas pelo utilizador.
    unsigned int liked_musics_count;    //– número de quantas músicas o utlizador gosta
} UserString;

/* Create a new User using only strings */
UserString* createUserString (char** tokens) {
    UserString* user = malloc(sizeof(UserString));
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
/* Create a new User */
User* createUser (char** tokens) {
    User* user = malloc(sizeof(User));
    if (mallocErrorCheck (user)) exit (EXIT_FAILURE);
    int id;
    if (convertToInt (trimString((tokens[0])) + 1, &id)) user->id = id;
    else exit (EXIT_FAILURE);
    user->email = strdup (trimString((tokens[1])));
    user->first_name = strdup (trimString((tokens[2])));
    user->last_name = strdup (trimString((tokens[3])));
    user->birth_date = parseDate (trimString((tokens[4])));
    user->country = strdup (trimString((tokens[5])));
    user->liked_musics_id = parseIDs (trimStringWithoutBrackets((tokens[7])));
    user->liked_musics_count = IdCounter ((tokens[7]));
    return user;
}

/* Destroy a UserString and free all allocated memory */
void deleteUserString(UserString* user) {
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

/* Destroy a User and free all allocated memory */
void deleteUser(User* user) {
    if (user) {
        free(user->email);
        free(user->first_name);
        free(user->last_name);
        free(user->country);
        free(user->liked_musics_id);
        free(user);
    }
}

// GETTER

/* Getter for id */
int getUserID(User* user) {
    return user->id;
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
    return user->birth_date;
}

/* Getter for country */
char* getUserCountry(User* user) {
    return strdup(user->country);
}

/* Getter for liked_musics_id */
const int* getUserLikedMusicsID(User* user) {
    int* array = user->liked_musics_id;
    return array;
}

/* Getter for liked_musics_count */
int getUserLikedCounter (User* user) {
    return user->liked_musics_count;
}

/* Getter for the age of the user
Current date 2024/09/09 */
int getUserAge (User* user) {
    int age = -1;
    Date bdate = user->birth_date;
    int birthYear = bdate.year;
    int birthMonth = bdate.month;
    int birthDay = bdate.day;
    age = 2024 - birthYear;
    if (birthMonth > 9 || (birthMonth == 9 && birthDay > 9)) age--;

    return age;
}

User* copyUser( User* userOg) {
    if (userOg == NULL) {
        return NULL;
    }

    User* userCopy = malloc(sizeof(User));
    if (!userCopy) {
        perror("Error allocating memory for User");
        return NULL;
    }

    userCopy->id = userOg->id;
    userCopy->birth_date = userOg->birth_date;
    //userCopy->subscription_type = userOg->subscription_type;

    // copy for string fields
    userCopy->email = userOg->email ? strdup(userOg->email) : NULL;
    userCopy->first_name = userOg->first_name ? strdup(userOg->first_name) : NULL;
    userCopy->last_name = userOg->last_name ? strdup(userOg->last_name) : NULL;
    userCopy->country = userOg->country ? strdup(userOg->country) : NULL;

    // copy for the int array
    int arrayCount = userOg->liked_musics_count;
    if (userOg->liked_musics_id != NULL &&  arrayCount > 0) {
        
        userCopy->liked_musics_id = malloc(arrayCount * sizeof(int));
        if (userCopy->liked_musics_id == NULL) {
            perror("Error allocating memory for liked_musics_id");
            free(userCopy->email);
            free(userCopy->first_name);
            free(userCopy->last_name);
            free(userCopy->country);
            free(userCopy);
            return NULL;
        }
        // Copy the contents of the original liked_musics_id array
        memcpy(userCopy->liked_musics_id, userOg->liked_musics_id, arrayCount * sizeof(int));

    } else userCopy->liked_musics_id = NULL;

    userCopy->liked_musics_count = arrayCount;

    return userCopy;
}


// GETTERS FOR USER STRING

/* Getter for id in string format */
char* getUserIDString (UserString* user) {
    return strdup(user->id);
}

/* Getter for email in string format */
char* getUserEmailString(UserString* user) {
    return strdup(user->email);
}

/* Getter for first_name in string format */
char* getUserFirstNameString(UserString* user) {
    return strdup(user->first_name);
}

/* Getter for last_name in string format */
char* getUserLastNameString(UserString* user) {
    return strdup(user->last_name);
}

/* Getter for birth_date in string format */
char* getUserBirthDateString (UserString* user) {
    return strdup (user->birth_date);
}

/* Getter for country in string format */
char* getUserCountryString(UserString* user) {
    return strdup(user->country);
}

/* Getter for subscription_type in string format */
char * getUserSubscriptionTypeString (UserString *user) {
    return strdup (user->subscription_type);
}

/* Getter for liked_musics_id in string format */
char* getUserLikedMusicsIDString (UserString *user) {
    return strdup (user->liked_musics_id);
}

/* Getter for liked_musics_id in string format in an array */
const int* getUserLikedMusicsIDStringArray (UserString *user) {
    int* result = parseIDs(user->liked_musics_id); 
    return result;
}

/* Getter for liked_musics_count in string format */
int getUserLikedCounterString (UserString* user) {
    return user->liked_musics_count;
}
