#include <users.h>
#include <glib.h>
#include <userManager.h>
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

void getDataUser (char *path, UserManager *userManager, MusicManager *musicManager) {
    char* userPath = changePath (path, Users);
    FILE* fileData = openFile (userPath);
    FILE* fileError = openErrorFileUser ();

    char str[DEFAULT];
    if (fgets(str, sizeof(str), fileData) == NULL) { // skip header
        perror ("skipping user header error");
        exit(EXIT_FAILURE);
    }
    while (fgets (str, sizeof (str), fileData) != NULL){
        char* tokens[8];
        parseLine(str, tokens, ";");
        
        User* user = createUser(tokens);
        if (!validUser(user, musicManager)) {
            insertErrorFileUser(user, fileError);
            deleteUser(user);
        } else insertUserHash(userManager, getUserID(user), user);

        //printf ("GETDATA:\nuser: %d\nemail:%s\nfirst name:%s\nlast name:%s\nbirthdate: %d/%d/%d\ncountry:%s\nsubscription:%d\nno. of liked songs: %d\nliked songs:", user->username, user->email, user->first_name, user->last_name, user->birth_date.year, user->birth_date.month, user->birth_date.day, user->country, user->subscription_type, user->liked_musics_count); //DEBUG

        //Exemplo de como dar print do que está na hashtable. Utilizado para testar
        //int idd = getUserID (user);
        //printf("%d\n", idd);
        
        //printUser (user); 
    }
    fclose(fileData);
    fclose(fileError);
    free (userPath);
}