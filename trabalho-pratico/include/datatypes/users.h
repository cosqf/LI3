#include <stdio.h>
#include <stdbool.h>
#include <parsingUtils.h>

#ifndef _USERS_H_
#define _USERS_H_

typedef struct user User;
typedef struct userString UserString;

UserString* createUserString (char** tokens);
User* createUser (char** tokens);
void deleteUserString(UserString* user);
void deleteUser(User* user);

// GETTERs
int getUserID(User* user);
char* getUserEmail(User* user);
char* getUserFirstName(User* user);
char* getUserLastName(User* user);
Date getUserBirthDate(User* user);
char* getUserCountry(User* user);
const int* getUserLikedMusicsID(User* user);
int getUserLikedCounter (User* user);
int getUserAge (User* user);
User* copyUser (User* userOg);

char* getUserIDString (UserString* user);
char* getUserEmailString (UserString *user);
char* getUserFirstNameString(UserString* user);
char* getUserLastNameString(UserString* user);
char* getUserBirthDateString (UserString* user);
char* getUserCountryString(UserString* user);
char* getUserSubscriptionTypeString (UserString *user);
char* getUserLikedMusicsIDString (UserString *user);
int getUserLikedCounterString (UserString* user);
const int* getUserLikedMusicsIDStringArray (UserString *user);

#endif  
