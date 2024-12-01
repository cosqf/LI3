#include <users.h>
#include <glib.h>
#include <userManager.h>
#include <hashtableManager.h>
#include <musicManager.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <utils.h>
#include <output_handling/errorfiles.h>
#include <validateDatatypes.h>

typedef struct userManager {
    GHashTable *user;
} UserManager;

void insertUserHash (UserManager *u_mngr, int key, User *user) {
    g_hash_table_insert(u_mngr->user, GINT_TO_POINTER (key), user);
}

UserManager* initializeHashUser () {
    UserManager* u_mngr = malloc (sizeof (UserManager));
    if (u_mngr == NULL) {
        perror("Failed to allocate memory for UserManager");
        exit(EXIT_FAILURE); 
    }
    u_mngr->user = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, (GDestroyNotify)deleteUser);
    return u_mngr;
}

void freeHashUser (UserManager* u_mngr) {
    g_hash_table_destroy (u_mngr->user);
    free (u_mngr);
}

User* lookupUserHash (UserManager *u_mngr, int id) {
    User* user = g_hash_table_lookup (u_mngr->user, GINT_TO_POINTER(id));
    if (user == NULL) return NULL;
    return copyUser (user);
}

GHashTable* getUserTable (UserManager *u_mngr) {
    return u_mngr->user;
}


int getDataUser (char* path, hashtableManager* mngr) {
    Output* output = openErrorOutputUser ();
    
    int error = parseFile(path, callbackUser, mngr, output);

    closeOutputFile (output);

    if (error) return 1;
    else return 0;
}

// creates an userString according to its tokens and validates them. 
// if valid, its converted to an user and added to the hashtable
void callbackUser(char **tokens, void *manager, Output *output) { // receives entity manager
    hashtableManager* mngr = (hashtableManager*) manager;
    UserManager* user_mngr = getUserManager(mngr);
    MusicManager* music_mngr = getMusicManager(mngr);

    UserString* userS = createUserString(tokens);
    if (!validUser(userS, music_mngr)) insertErrorFileUser(userS, output);
    else {
        User* user = createUser (tokens);
        insertUserHash(user_mngr, getUserID(user), user);
    }
    deleteUserString(userS);
}