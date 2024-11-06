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

                addToResults (arrayResults, genre);

            }
        }

    };
    for (int j=0; j<10; j++)
        printf("%s, %d\n", arrayResults[j].genre, arrayResults[j].likes);
    printf ("\n");
}

void addToResults(TupleMusics *array, char* genre){
    if (strcmp (genre, "Metal") == 0)
        array[0].likes++;
    else if (strcmp (genre, "Reggae") == 0)
        array[1].likes++;
    else if (strcmp (genre, "Jazz") == 0)
        array[2].likes++;
    else if (strcmp (genre, "Hip Hop") == 0)
        array[3].likes++;
    else if (strcmp (genre, "Classical") == 0)
        array[4].likes++;
    else if (strcmp (genre, "Rock") == 0)
        array[5].likes++;
    else if (strcmp (genre, "Blues") == 0)
        array[6].likes++;
    else if (strcmp (genre, "Country") == 0)
        array[7].likes++;
    else if (strcmp (genre, "Pop") == 0)
        array[8].likes++;
    else if (strcmp (genre, "Electronic") == 0)
        array[9].likes++;
}

void defineGender (TupleMusics *array){
    array[0].genre = "Metal";
    array[1].genre = "Reggae";
    array[2].genre = "Jazz";
    array[3].genre = "Hip Hop";
    array[4].genre = "Classical";
    array[5].genre = "Rock";
    array[6].genre = "Blues";
    array[7].genre = "Country";
    array[8].genre = "Pop";
    array[9].genre = "Electronic";
}
