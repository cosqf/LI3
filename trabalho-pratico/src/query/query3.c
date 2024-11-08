#include <query3.h>
#include <parsing.h>
#include <glib.h>
#include <stdlib.h>
#include <outputWriter.h>


void query3 (CMD *cmd, UserManager *u_mngr, MusicManager *m_mngr, int cmdCounter){
    GHashTable* userHashTable = getUserTable (u_mngr);
   // GHashTable* musicHashTable = getMusicTable (m_mngr);
    GHashTableIter iter;
    gpointer key, value;
    char filename[50];  // buffer for the formatted file name

    // Format the filename with the counter value
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", cmdCounter);

    FILE* results = fopen (filename, "w");

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
                Genre genre = getMusicGenre (music);
                
                addToResults (arrayResults, genre);
            }
        }
    }

    qsort(arrayResults, 10, sizeof(TupleMusics), compareLikes);

    for (int j=0; j<10; j++){
        if(arrayResults[j].likes == 0) {
            writeNewLine(results);
            break;
        }
        char str[20];
        snprintf(str, sizeof(str), "%d", arrayResults[j].likes);
        writeQuery3 (results, arrayResults[j].genre, str);
    }
    //printf ("\n");
    //fprintf(results, "\n");
    fclose(results);
}


void addToResults(TupleMusics *array, Genre genre) {
    if (genre >= 0 && genre < 10) {
        array[genre].likes++;
    }
}


void defineGenre(TupleMusics *array) {
    array[GENRE_METAL]      = (TupleMusics) { .genre = "Metal", .likes = 0 };
    array[GENRE_REGGAE]     = (TupleMusics) { .genre = "Reggae", .likes = 0 };
    array[GENRE_JAZZ]       = (TupleMusics) { .genre = "Jazz", .likes = 0 };
    array[GENRE_HIPHOP]     = (TupleMusics) { .genre = "Hip Hop", .likes = 0 };
    array[GENRE_CLASSICAL]  = (TupleMusics) { .genre = "Classical", .likes = 0 };
    array[GENRE_ROCK]       = (TupleMusics) { .genre = "Rock", .likes = 0 };
    array[GENRE_BLUES]      = (TupleMusics) { .genre = "Blues", .likes = 0 };
    array[GENRE_COUNTRY]    = (TupleMusics) { .genre = "Country", .likes = 0 };
    array[GENRE_POP]        = (TupleMusics) { .genre = "Pop", .likes = 0 };
    array[GENRE_ELECTRONIC] = (TupleMusics) { .genre = "Electronic", .likes = 0 };
}

int compareLikes(const void* a, const void* b) {
    const TupleMusics* tupleA = (const TupleMusics*)a;
    const TupleMusics* tupleB = (const TupleMusics*)b;

    if (tupleA->likes > tupleB->likes) return -1;  // descending order
    if (tupleA->likes < tupleB->likes) return 1;
 
    // if the likes are equal, orders alphabetically
    if(strcmp (tupleA->genre, tupleB->genre) > 0) return 1;
    if(strcmp (tupleA->genre, tupleB->genre) < 0) return -1;

    return 0;
}