#include <stdio.h>
#include <stdbool.h>
#include <parsingUtils.h>

#ifndef _USERS_H_
#define _USERS_H_

typedef struct User User;

User* createUser();
void destroyUser(User* user);

// GETTERs
int getUserName(User* user);
char* getUserEmail(User* user);
char* getUserFirstName(User* user);
char* getUserLastName(User* user);
Date getUserBirthDate(User* user);
char* getUserCountry(User* user);
bool getUserSubscriptionType(User* user);
int* getUserLikedMusicsID(User* user);
int getUserLikedCounter (User* user);

// SETTERs
void setUserName(User* user, const char* username);
void setUserEmail(User* user, const char* email);
void setUserFirstName(User* user, const char* first_name);
void setUserLastName(User* user, const char* last_name);
void setUserBirthDate(User* user, const char* birth_date);
void setUserCountry(User* user, const char* country);
void setUserSubscriptionType(User* user, const char* subscription_type);
void setUserLikedMusicsID(User* user, const char* liked_musics_id);
void setUserLikedMusicsCount(User* user, int liked_musics_count);

#endif  
