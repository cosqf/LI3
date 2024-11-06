#include <query3.h>
#include <parsing.h>
#include <glib.h>
#include <stdlib.h>


void query3 (CMD *cmd, UserManager *u_mngr, MusicManager *m_mngr){
    GHashTable* userHashTable = getUserTable (u_mngr);
   // GHashTable* musicHashTable = getMusicTable (m_mngr);
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, userHashTable);

    int AgeMin = getCMDAgeMin(cmd);
    int AgeMax = getCMDAgeMax(cmd);
    TupleMusics arrayResults [10];

    defineGender (arrayResults);

    while (g_hash_table_iter_next(&iter, &key, &value)) { //para cada user
        User* user = (User*) value;
        int age = getUserAge (user), nLikes = getUserLikedCounter (user);
        int* LikedMusics = getUserLikedMusicsID (user);

        if (age >= AgeMin && age <= AgeMax){
            for (int i=0; i<nLikes; i++){ //para cada musica
                int idAtual = LikedMusics[i];
                Music* music = lookupMusicHash (m_mngr, idAtual);
                char* genre = getMusicGenre (music);


                //ver as musicas e adicionar à contagem do array
            }
        }

    };
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
