#include <stdlib.h>
#include <query1.h>
#include <parsing.h>
#include <userManager.h>
#include <users.h>
#include <stdio.h>
#include <outputWriter.h>


void query1(CMD* cmd, UserManager *u_mngr, int counter) {
    char filename[50];  // buffer for the formatted file name

    // Format the filename with the counter value
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", counter);

    FILE* results = fopen (filename, "w");

    int userID = getCMDId(cmd);
    User* user = lookupUserHash(u_mngr, userID);

    if(user != NULL){
        char* email = getUserEmail(user);
        char* firstname = getUserFirstName(user);
        char* lastname = getUserLastName(user);
        int age = getUserAge(user);
        char* country = getUserCountry(user);

        writeQuery1 (results, email, firstname, lastname, age, country);

        free(email);
        free(firstname);
        free(lastname);
        free(country);
    }

    writeNewLine(results);
    fclose(results);
}