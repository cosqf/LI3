#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <users.h>
#include <parsingUtils.h>


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
    int length = strlen(email);

    char* username = (char*)malloc(length + 1);
    char* lstr = (char*)malloc(length + 1);
    char* rstr = (char*)malloc(length + 1);

    if (sscanf(email, "%[^@]@%[^.].%s", username, lstr, rstr) == 3){
        
        if (isstr(username, 1) && isstr(lstr, 0) && isstr(rstr, 0)){

            if (strlen(rstr) == 2 || strlen(rstr) == 3){
                free(username);
                free(lstr);
                free(rstr);
                return 1;
            }
        }
    }

    free(username);
    free(lstr);
    free(rstr);

    return 0;
}


