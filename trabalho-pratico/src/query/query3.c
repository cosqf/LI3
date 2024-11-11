#include <query3.h>
#include <parsing.h>
#include <glib.h>
#include <stdlib.h>
#include <output_handling/outputWriter.h>


void query3 (CMD *cmd, UserManager *u_mngr, MusicManager *m_mngr, int cmdCounter){
    GHashTable* userHashTable = getUserTable (u_mngr);
    GHashTableIter iter;
    gpointer key, value;
    char filename[50];  // buffer for the formatted file name

    // Format the filename with the counter value
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", cmdCounter);

    g_hash_table_iter_init(&iter, userHashTable);

    int AgeMin = getCMDAgeMin(cmd);
    int AgeMax = getCMDAgeMax(cmd);
    TupleMusics arrayResults [10];

    defineGenre (arrayResults); // initialize arrayResults

    GHashTable* musicCache = g_hash_table_new(g_direct_hash, g_direct_equal); // create local cache hash table

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        User* user = (User*) value;
        int age = getUserAge(user), nLikes = getUserLikedCounter(user);
        const int* LikedMusics = getUserLikedMusicsID(user);

        if (age >= AgeMin && age <= AgeMax) {
            for (int i = 0; i < nLikes; i++) {
                int idAtual = LikedMusics[i];

                // Check cache first
                Music* music = g_hash_table_lookup(musicCache, GINT_TO_POINTER(idAtual));
                if (!music) {
                    // Perform lookup if not in cache
                    music = lookupMusicHash(m_mngr, idAtual);
                    if (music) g_hash_table_insert(musicCache, GINT_TO_POINTER(idAtual), music);
                    else continue;
                }

                Genre genre = getMusicGenre(music);
                addToResults(arrayResults, genre);
            }
        }
    }

    g_hash_table_destroy(musicCache);
    
    qsort(arrayResults, 10, sizeof(TupleMusics), compareLikes);


    // printing segment

    Output* output = openOutputFile (filename);

    for (int j=0; j<10; j++){
        if(arrayResults[j].likes == 0) {
            writeNewLine(output);
            break;
        }
        char str[20];
        snprintf(str, sizeof(str), "%d", arrayResults[j].likes);

        char* lines[10] = {NULL};
        lines[0] = arrayResults[j].genre;
        lines[1] = str;
        setOutput (output, lines, 2);
        writeQuerys (output);
    }

    closeOutputFile (output);
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