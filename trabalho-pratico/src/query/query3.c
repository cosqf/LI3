#include <query3.h>
#include <parsing.h>
#include <glib.h>
#include <stdlib.h>


void query3 (CMD *cmd, UserManager *u_mngr){
    (void) u_mngr;
    GHashTable* userHashTable = getUserTable (u_mngr);
    int AgeMin = getCMDAgeMin(cmd);
    int AgeMax = getCMDAgeMax(cmd);
    TupleMusics arrayResults [10];

    defineGender (arrayResults);

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
        //int id = getUserID (user);
        //if (age == 50)
            //printf ("%d\n", id);



        }
    }


void defineGender (TupleMusics *array){
    array[0].gender = "Metal";
    array[1].gender = "Reggae";
    array[2].gender = "Jazz";
    array[3].gender = "Hip Hop";
    array[4].gender = "Classical";
    array[5].gender = "Rock";
    array[6].gender = "Blues";
    array[7].gender = "Country";
    array[8].gender = "Pop";
    array[9].gender = "Electronic";
}
