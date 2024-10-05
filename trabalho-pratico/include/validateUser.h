#include <stdio.h>
#include <users.h>

#ifndef _VALIDATEUSER_H_
#define _VALIDATEUSER_H_

int isletter(char);

int isdigit(char);

int isstr(char*, int);

int validEmail(char*);

Date parseDate(char*);

#endif  
