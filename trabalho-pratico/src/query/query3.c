#include <query3.h>
#include <parsing.h>
#include <glib.h>
#include <stdlib.h>


void query3 (CMD *cmd, UserManager *u_mngr, MusicManager *m_mngr, int cmdCounter){
    GHashTable* userHashTable = getUserTable (u_mngr);
   // GHashTable* musicHashTable = getMusicTable (m_mngr);
    GHashTableIter iter;
    gpointer key, value;
//
    char filename[50];  // buffer for the formatted file name

    // Format the filename with the counter value
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", cmdCounter);

    FILE* results = fopen (filename, "w");
//

    g_hash_table_iter_init(&iter, userHashTable);

    int AgeMin = getCMDAgeMin(cmd);
    int AgeMax = getCMDAgeMax(cmd);
    TupleMusics arrayResults [10];

    defineGenre (arrayResults);

    while (g_hash_table_iter_next(&iter, &key, &value)) { //para cada user
        User* user = (User*) value;
        int age = getUserAge (user), nLikes = getUserLikedCounter (user);
        int* LikedMusics = getUserLikedMusicsID (user);

        if (age >= AgeMin && age <= AgeMax){
            for (int i=0; i<nLikes; i++){ //para cada musica
                int idAtual = LikedMusics[i];
                Music* music = lookupMusicHash (m_mngr, idAtual);
                //if(music != NULL) {
                    char* genre = getMusicGenre (music);

                    addToResults (arrayResults, genre);
                //}

            }
        }

    };

    qsort(arrayResults, 10, sizeof(TupleMusics), compareLikes);

    for (int j=0; j<10; j++){
        if(arrayResults[j].likes == 0) continue;
        char str[20];
        snprintf(str, sizeof(str), "%d", arrayResults[j].likes);
        fprintf(results, "%s;%s\n", arrayResults[j].genre, str);
    }
    //printf ("\n");
    //fprintf(results, "\n");
    fclose(results);
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

void defineGenre(TupleMusics *array) {
    array[0].genre = "Metal"; array[0].likes = 0;
    array[1].genre = "Reggae"; array[1].likes = 0;
    array[2].genre = "Jazz"; array[2].likes = 0;
    array[3].genre = "Hip Hop"; array[3].likes = 0;
    array[4].genre = "Classical"; array[4].likes = 0;
    array[5].genre = "Rock"; array[5].likes = 0;
    array[6].genre = "Blues"; array[6].likes = 0;
    array[7].genre = "Country"; array[7].likes = 0;
    array[8].genre = "Pop"; array[8].likes = 0;
    array[9].genre = "Electronic"; array[9].likes = 0;
}

int compareLikes(const void* a, const void* b) {
    const TupleMusics* tupleA = (const TupleMusics*)a;
    const TupleMusics* tupleB = (const TupleMusics*)b;

    if (tupleA->likes > tupleB->likes) return -1;  // descending order
    if (tupleA->likes < tupleB->likes) return 1;
 
    // if the likes are equal, orders alphabetically
    if(tupleA->genre[0] > tupleB->genre[0]) return 1;
    if(tupleA->genre[0] < tupleB->genre[0]) return -1;

    return 0;
}
