#include <stdio.h>
#include <stdbool.h>
#include <parsingUtils.h>

#ifndef _USERS_H_
#define _USERS_H_

typedef struct user User;

User* createUser (char** tokens);
void deleteUser(User* user);
void printUser(const User* user);

// GETTERs
int getUserID(User* user);
char* getUserIDString (User* user);
char* getUserEmail(User* user);
char* getUserFirstName(User* user);
char* getUserLastName(User* user);
Date getUserBirthDate(User* user);
char* getUserBirthDateString (User* user);
char* getUserCountry(User* user);
bool getUserSubscriptionType(User* user);
char* getUserSubscriptionTypeString (User *user);
int* getUserLikedMusicsID(User* user);
char* getUserLikedMusicsIDString (User *user);
int getUserLikedCounter (User* user);

// SETTERs
void setUserID(User* user, const char* username);
void setUserEmail(User* user, const char* email);
void setUserFirstName(User* user, const char* first_name);
void setUserLastName(User* user, const char* last_name);
void setUserBirthDate(User* user, const char* birth_date);
void setUserCountry(User* user, const char* country);
void setUserSubscriptionType(User* user, const char* subscription_type);
void setUserLikedMusicsID(User* user, const char* liked_musics_id);
void setUserLikedMusicsCount(User* user, int liked_musics_count);

#endif  
