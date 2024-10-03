#include <processInput.h>

void query1(char* path) {
    getData (path, Users);
}

void freeUser(User *user) {
    if (user) {
        free(user->username);
        free(user->email);
        free(user->first_name);
        free(user->last_name);
        free(user->country);
        free(user->liked_musics_id); 
        free(user);
    }
}