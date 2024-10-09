#include <users.h>

#ifndef _PARSINGUSER_H_
#define _PARSINGUSER_H_

// Parses user
User* parseDataU(User *user, UserRaw *raw); 
// fetches data from the user file
UserRaw* fetchDataU (char *str, UserRaw *user); 


#endif