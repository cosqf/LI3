#include <stdio.h>
#include <users.h>

#ifndef _VALIDATEUSER_H_
#define _VALIDATEUSER_H_

int isletter(char);

int isDigit(char);

int isstr(char*, int);

int validEmail(char*);

Date ALTparseDate(char*);

User* ALTparseDataU (char *, User *);

#endif  
