#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <users.h>
#include <processInput.h>


// Checks if the given character is an undercase letter
int isletter(char a){
    if (a >= 'a' && a <= 'z') return 1;
    return 0;
}


// Checks if the given character is a digit
int isDigit(char a){
    if (a >= '0' && a <= '9') return 1;
    return 0;
}


// Checks is the given string is comprised of only undercase letters (if the flag is 0), or comprised of undercase letters and digits (if the flag is 1)
int isstr(char* str, int flag) {
    if (!str) return 0;
    
    int i;

    if (flag == 1) for (i = 0; isletter(str[i]) || isDigit(str[i]); i++);

    else for (i = 0; isletter(str[i]); i++);
    
    if (str[i] == '\0') return 1;
    
    return 0;
}


// Validates the user's email, ensuring it's in the correct format (username@lstr.rstr)
int validEmail(char* email){
    char* username = {0};
    char* lstr = {0};
    char* rstr = {0};
/*
    char* atSign = strchr(email, '@');  // Search for the '@'
    if (!atSign) return 0;              // If no '@' is found, the email is invalid

    char* dot = strrchr(atSign, '.');    // Search for the '.'
    if (!dot) return 0;                  // If no '.' is found, the email is invalid
*/
    if (sscanf(email, "%s@%s.%s", username, lstr, rstr) != 3) return 0;

    if (!isstr(username, 1) || !isstr(lstr, 0) || !isstr(rstr, 0)) return 0;

    if (strlen(rstr) < 2 || strlen(rstr) > 3) return 0;

    return 1;
}


// Validating the user's birthdate, ensuring it's in the correct format and not more recent than 09/09/2024
Date parseDate(char* dateStr) {
    Date date;

    if (sscanf(dateStr, "%d/%d/%d", &date.year, &date.month, &date.day) != 3) date.error = 1;
    else if (date.year > 2024) date.error = 1;
    else if (date.year == 2024){
        if (date.month > 9) date.error = 1;
        if (date.month == 9 && (date.day < 1 || date.day > 9)) date.error = 1;
    }
    else if (date.month < 1 || date.month > 12 || date.day < 1 || date.day > 31) date.error = 1;

    return date;
}


User* parseDataU(char *str, User *user) {
    if (!str || !user) return NULL; 

    char *token = NULL;

    // Parsing the user ID, skipping the U 
    token = trimString(strsep(&str, ";"));
    if (token && token[0] == 'U') user->username = atoi(token + 1);

    // Parsing the email
    token = strsep(&str, ";");
    if (token && validEmail(token)) user->email = strdup(trimString(token));
    else {
        perror("Email parsing error");
        return NULL;
    }

    // Parsing first name
    token = strsep(&str, ";");
    if (token) user->first_name = strdup(trimString(token));
    else {
        perror("First name parsing error");
        return NULL;
    }

    // Parsing last name
    token = strsep(&str, ";");
    if (token) user->last_name = strdup(trimString(token));
    else {
        perror("Last name parsing error");
        return NULL;
    }

    // Parsing the birth date
    token = strsep(&str, ";");

    if (token) {
        //user->buffer = strdup(trimString(token));
        user->birth_date = parseDate(strdup(trimString(token)));
        //free(user->buffer);
        //user->buffer = NULL;
        if (user->birth_date.error == 1) {
            perror("Invalid birthdate");
            return NULL;
        }
    } else {
        perror("Date parsing error");
        return NULL;
    }
    /*
    if (token) {
        Date date = parseDate(trimString(token)); 
        if (date.error == 1) {
            perror("Date parsing error");
            return NULL; 
        }

        user->birth_date = date;
    } else {
        perror("Birth date parsing error");
        return NULL;
    }
*/
    // Parsing the country
    token = strsep(&str, ";");
    if (token) user->country = strdup(trimString(token));
    else {
        perror("Country parsing error");
        return NULL;
    }

    // Parsing the subscription type
    token = strsep(&str, ";");
    if (token) {
        if (strcmp (trimString(token), "normal") == 0) user->subscription_type = 0;
        if (strcmp (trimString(token), "premium") == 0) user->subscription_type = 1;
        else {
            perror("Invalid subscription type");
            return NULL;
        }
    }
    else {
        perror("Subscription type parsing error");
        return NULL;
    }

    // Parsing the liked music IDs
    user->liked_musics_id = parseIDs(str, user);
    if (user->liked_musics_id == NULL) {
        perror("Liked music IDs parsing error");
        return NULL;
    }

    return user;
}
