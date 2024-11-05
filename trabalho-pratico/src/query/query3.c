#include <query3.h>
#include <parsing.h>
#include <glib.h>
#include <stdlib.h>


void query3 (CMD *cmd, UserManager *u_mngr){
    (void) u_mngr;
    GHashTable* userHashTable = getUserTable (u_mngr);
    int AgeMin = getCMDAgeMin(cmd);
    int AgeMax = getCMDAgeMax(cmd);

    //definir genero array tuplos


    printf ("%d %d\n", AgeMin, AgeMax);
    iter_hash (userHashTable);

};

void iter_hash(GHashTable* userHashTable) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, userHashTable);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        User* user = (User*) value;
        int age = getUserAge (user);
        int id = getUserID (user);
        if (age == 50)
            printf ("%d\n", id);



        }
    }