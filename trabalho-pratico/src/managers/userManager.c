#include <users.h>
#include <glib.h>
#include <userManager.h>

typedef struct userManager {
    GHashTable *user;
} UserManager;


void insertUserHash (UserManager *u_mngr, int key, User *User) {
    g_hash_table_insert(u_mngr->user, GINT_TO_POINTER (key), User);
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