#include <stdlib.h>
#include <query1.h>
#include <parsing.h>
#include <userManager.h>
#include <users.h>
#include <stdio.h>


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
        int age = calculateAge(user);
        char* country = getUserCountry(user);

        fprintf(results, "%s;%s;%s;%d;%s", email, firstname, lastname, age, country); //email;first_name;last_name;age;country

        free(email);
        free(firstname);
        free(lastname);
        free(country);
    }

    fprintf(results, "\n");
    fclose(results);
}

int calculateAge(User* user) {
    int age = -1;
    int birthYear, birthMonth, birthDay;
    char* bdate = getUserBirthDateString(user);

    if (sscanf(bdate, "%d/%d/%d", &birthYear, &birthMonth, &birthDay) == 3) {
        age = 2024 - birthYear;
        if (birthMonth > 9 || (birthMonth == 9 && birthDay > 9)) age--;
    }

    free(bdate);
    return age;
}