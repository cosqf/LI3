#include <users.h>
#include <glib.h>
#include <userManager.h>
#include <entityManager.h>
#include <musicManager.h>
#include <parsingUtils.h>
#include <parsing.h>
#include <utils.h>
#include <validation.h>
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
    User* User = g_hash_table_lookup (u_mngr->user, GINT_TO_POINTER(id));
    return User;
}

GHashTable* getUserTable (UserManager *u_mngr) {
    return u_mngr->user;
}

void callbackUser(char **tokens, void *manager, FILE *errorFile) { // receives entity manager
    EntityManager* mngr = (EntityManager*) manager;
    UserManager* user_mngr = getUserManager(mngr);
    MusicManager* music_mngr = getMusicManager(mngr);

    User *user = createUser(tokens);
    if (!validUser(user, music_mngr)) {
        insertErrorFileUser(user, errorFile);
        deleteUser(user);
    } else {
        insertUserHash(user_mngr, getUserID(user), user);
    }
}