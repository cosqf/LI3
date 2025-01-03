#include <stdio.h>
#include <stdbool.h>
#include <parsingUtils.h>

#ifndef _USERS_H_
#define _USERS_H_

/**
 * @brief A user struct.
 */
typedef struct user User;

/**
 * @brief A user struct in string format.
 */
typedef struct userString UserString;

/**
 * @brief Creates a user struct in string format.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to a user string struct.
 */
UserString* createUserString (char** tokens);

/**
 * @brief Creates a user struct.
 *
 * @param tokens An array of parsed tokens.
 * 
 * @return A pointer to a user struct.
 */
User* createUser (char** tokens);

/**
 * @brief Deletes a user string struct and frees its memory.
 *
 * @param user A pointer to the user string struct to be deleted.
 */
void deleteUserString(UserString* user);

/**
 * @brief Deletes a user struct and frees its memory.
 *
 * @param user A pointer to the user struct to be deleted.
 */
void deleteUser(User* user);

/**
 * @brief Creates an user struct from another, copying its contents.
 *
 * @param userOg A pointer to the original user struct.
 * 
 * @return A pointer to the copied user struct.
 */
User* copyUser (User* userOg);


/* Getters */
/**
 * @brief A getter function that returns the ID of a user.
 *
 * @param user A pointer to the user struct.
 * 
 * @return ID of the given user.
 */
int getUserID(User* user);

/**
 * @brief A getter function that returns the email of a user.
 *
 * @param user A pointer to the user struct.
 * 
 * @return Email of the given user.
 */
char* getUserEmail(User* user);

/**
 * @brief A getter function that returns the first name of a user.
 *
 * @param user A pointer to the user struct.
 * 
 * @return First name of the given user.
 */
char* getUserFirstName(User* user);

/**
 * @brief A getter function that returns the last name of a user.
 *
 * @param user A pointer to the user struct.
 * 
 * @return Last name of the given user.
 */
char* getUserLastName(User* user);

/**
 * @brief A getter function that returns the birth date of a user.
 *
 * @param user A pointer to the user struct.
 * 
 * @return Birth date of the given user.
 */
Date getUserBirthDate(User* user);

/**
 * @brief A getter function that returns the country of a user.
 *
 * @param user A pointer to the user struct.
 * 
 * @return Country of the given user.
 */
char* getUserCountry(User* user);

/**
 * @brief A getter function that returns the IDs of liked musics for a user.
 *
 * @param user A pointer to the user struct.
 * 
 * @return Pointer to an array of liked music IDs.
 */
const int* getUserLikedMusicsID(User* user);

/**
 * @brief A getter function that returns the number of liked musics for a user.
 *
 * @param user A pointer to the user struct.
 * 
 * @return Count of liked musics.
 */
int getUserLikedCounter (User* user);

/**
 * @brief A getter function that returns the position of the user ID in the ID array.
 *
 * @param user A pointer to the user struct.
 * 
 * @return The array position it occupies.
 */
int getUserArrayPosition(User* user);

/**
 * @brief A getter function that returns the age of a user.
 *
 * @param user A pointer to the user struct.
 * 
 * @return Age of the given user.
 */
int getUserAge (User* user);


/* Getter string*/
/**
 * @brief A getter function that returns the ID of a user in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return ID of the given user in string format.
 */
char* getUserIDString (UserString* user);

/**
 * @brief A getter function that returns the email of a user in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return Email of the given user in string format.
 */
char* getUserEmailString (UserString *user);

/**
 * @brief A getter function that returns the first name of a user in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return First name of the given user in string format.
 */
char* getUserFirstNameString(UserString* user);

/**
 * @brief A getter function that returns the last name of a user in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return Last name of the given user in string format.
 */
char* getUserLastNameString(UserString* user);

/**
 * @brief A getter function that returns the birth date of a user in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return Birth date of the given user in string format.
 */
char* getUserBirthDateString (UserString* user);

/**
 * @brief A getter function that returns the country of a user in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return Country of the given user in string format.
 */
char* getUserCountryString(UserString* user);

/**
 * @brief A getter function that returns the subscription type of a user in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return Subscription type of the given user in string format.
 */
char* getUserSubscriptionTypeString (UserString *user);

/**
 * @brief A getter function that returns the liked music IDs of a user in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return Liked music IDs of the given user in string format.
 */
char* getUserLikedMusicsIDString (UserString *user);

/**
 * @brief A getter function that returns the number of liked musics of a user in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return Count of liked musics in string format.
 */
int getUserLikedCounterString (UserString* user);

/**
 * @brief A getter function that returns the liked music IDs of a user as an array in string format.
 *
 * @param user A pointer to the user string struct.
 * 
 * @return Pointer to an array of liked music IDs in string format.
 */
const int* getUserLikedMusicsIDStringArray (UserString *user);


/* Setters*/

/**
 * @brief A setter function used during the creation of the user array that updates the array position.
 *
 * @param user A pointer to the user struct.
 * @param position The position number to store.
 */
void setUserArrayPosition(User* user, int position);

#endif  
