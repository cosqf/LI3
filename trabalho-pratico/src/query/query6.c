    #include <historyManager.h>
    #include <query6.h>
    #include <stdio.h>
    #include <string.h>
    #include <glib.h>
    #include <history.h>
    #include <userManager.h>
    #include <cmd.h>

    // Structures and functions used to store music

    //Struct that store Listened Music
    typedef struct ListenedMusicNode {
        int music_id;                     
        struct ListenedMusicNode* next;   
    } ListenedMusicNode;



    // Function to add musics to the linked list ListenedMusicNode
    ListenedMusicNode* addMusic(ListenedMusicNode* head, int music_id) {
        ListenedMusicNode* new_node = malloc(sizeof(ListenedMusicNode));
        if (!new_node) {
            printf("Erro ao alocar memória!\n");
            return head;
        }
        new_node->music_id = music_id;
        new_node->next = head;
        return new_node;
    }

    // Check if the song has already been played
    int wasMusicListened(ListenedMusicNode* head, int music_id) {
        ListenedMusicNode* current = head;
        while (current != NULL) {
            if (current->music_id == music_id) {
                return 1;  // returns 1 if the music has found
            }
            current = current->next;
        }
        return 0;  // returns 0 if the music hasn't found
    }

    // Function to free up memory of the linked list
    void freeMusicList(ListenedMusicNode* head) {
        ListenedMusicNode* current = head;
        while (current != NULL) {
            ListenedMusicNode* temp = current;
            current = current->next;
            free(temp);
        }
    }

    // Structures and functions used to store artists and there listened time

    //store artists and there listened time
typedef struct {
    int artist_id;           // ID do artista
    int totalMusic;          // Contador de músicas ouvidas
    Duration totalTime;      // Duração total
    int* music_ids;          // Array dinâmico de IDs de músicas ouvidas
    int music_ids_count;     // Número de músicas no array
    int music_ids_capacity;  // Capacidade atual do array
} ArtistListenData;



    // Function to find the artist index in the array
    int findArtistIndex(ArtistListenData* array, int size, int artist_id) {
        for (int i = 0; i < size; i++) {
            if (array[i].artist_id == artist_id) {
                return i;
            }
        }
        return -1;
    }



// Função de comparação para ordenar por totalTime (decrescente)
int compareArtists(const void* a, const void* b) {
    const ArtistListenData* artistA = (const ArtistListenData*)a;
    const ArtistListenData* artistB = (const ArtistListenData*)b;

    // Comparar horas
    if (artistA->totalTime.hours != artistB->totalTime.hours) {
        return artistB->totalTime.hours - artistA->totalTime.hours;
    }
    // Comparar minutos
    if (artistA->totalTime.minutes != artistB->totalTime.minutes) {
        return artistB->totalTime.minutes - artistA->totalTime.minutes;
    }
    // Comparar segundos
    if (artistA->totalTime.seconds != artistB->totalTime.seconds) {
        return artistB->totalTime.seconds - artistA->totalTime.seconds;
    }
    // Comparar IDs (crescente para desempate)
    return artistA->artist_id - artistB->artist_id;
}

// Função para ordenar o array
void sortArtistsByListeningTime(ArtistListenData* array, int size) {
    qsort(array, size, sizeof(ArtistListenData), compareArtists);
}

ArtistListenData* updateArtistData(ArtistListenData* array, int* size, int artist_id, int music_id, Duration duration) {
    int index = findArtistIndex(array, *size, artist_id);

    if (index != -1) {
        // Atualiza a duração total
        array[index].totalTime.hours += duration.hours;
        array[index].totalTime.minutes += duration.minutes;
        array[index].totalTime.seconds += duration.seconds;

        // Corrige segundos e minutos
        if (array[index].totalTime.seconds >= 60) {
            array[index].totalTime.minutes += array[index].totalTime.seconds / 60;
            array[index].totalTime.seconds %= 60;
        }
        if (array[index].totalTime.minutes >= 60) {
            array[index].totalTime.hours += array[index].totalTime.minutes / 60;
            array[index].totalTime.minutes %= 60;
        }

        // Verifica se a música já foi ouvida
        int already_listened = 0;
        for (int i = 0; i < array[index].music_ids_count; i++) {
            if (array[index].music_ids[i] == music_id) {
                already_listened = 1;
                break;
            }
        }

        // Adiciona a música se ainda não foi ouvida
        if (!already_listened) {
            if (array[index].music_ids_count == array[index].music_ids_capacity) {
                // Expande a capacidade do array
                int new_capacity = array[index].music_ids_capacity * 2;
                if (new_capacity == 0) new_capacity = 2;

                int* new_music_ids = realloc(array[index].music_ids, new_capacity * sizeof(int));
                if (!new_music_ids) {
                    printf("Erro ao alocar memória!\n");
                    exit(1);
                }

                array[index].music_ids = new_music_ids;
                array[index].music_ids_capacity = new_capacity;
            }

            // Adiciona o ID da música
            array[index].music_ids[array[index].music_ids_count++] = music_id;
            array[index].totalMusic++;
        }

    } else {


        // Adiciona um novo artista
        ArtistListenData* new_array = realloc(array, (*size + 1) * sizeof(ArtistListenData));
        if (!new_array) {
            printf("Erro ao alocar memória!\n");
            free(array);
            exit(1);
        }
        array = new_array;

        array[*size].artist_id = artist_id;
        array[*size].totalTime = duration;
        array[*size].totalMusic = 1;

        // Inicializa o array de músicas
        array[*size].music_ids_capacity = 2;
        array[*size].music_ids_count = 1;
        array[*size].music_ids = malloc(array[*size].music_ids_capacity * sizeof(int));
        if (!array[*size].music_ids) {
            printf("Erro ao alocar memória!\n");
            exit(1);
        }
        array[*size].music_ids[0] = music_id;

        (*size)++;
    }

    return array;
}


    // Function to find the most listened artist
 //   int findMostListenedArtist(ArtistListenData* array, int size) {
 //       if (size == 0) {
 //           return -1;
 //       }
//
 //       int maxIndex = 0;
 //       for (int i = 1; i < size; i++) {
 //           Duration current = array[i].totalTime;
 //           Duration max = array[maxIndex].totalTime;
//
 //           if ((current.hours > max.hours) || 
 //               (current.hours == max.hours && current.minutes > max.minutes) || 
 //               (current.hours == max.hours && current.minutes == max.minutes && current.seconds > max.seconds) ||
 //               (current.hours == max.hours && current.minutes == max.minutes && current.seconds == max.seconds && array[i].artist_id < array[maxIndex].artist_id)) {
 //               maxIndex = i;
 //           }
 //       }
 //       return array[maxIndex].artist_id;
 //   }


    // Structures and functions used to store the duration of music heard in a day

    // Struct used to store the duration of music heard in a day
    typedef struct {
        Date day;           // dia
        int totalPlays;      // number of heard music
    } MusicDay;

int compareDates(Date d1, Date d2) {
    if (d1.year != d2.year) return d1.year - d2.year;
    if (d1.month != d2.month) return d1.month - d2.month;
    return d1.day - d2.day;
}

    // Finds the most listened Day
Date findMostListenedDay(MusicDay* musicDay, int musicDaysCount) {
    Date mostListenedDay = {0, 0, 0, 0};
    int maxPlays = 0;

    for (int i = 0; i < musicDaysCount; i++) {
        if (musicDay[i].totalPlays > maxPlays || 
            (musicDay[i].totalPlays == maxPlays && compareDates(musicDay[i].day, mostListenedDay) > 0)) {
            maxPlays = musicDay[i].totalPlays;
            mostListenedDay = musicDay[i].day;
        }
    }
    return mostListenedDay;
}


    int findDayIndex(MusicDay* musicDay, int musicDaysCount, Date day) {
        for (int i = 0; i < musicDaysCount; i++) {
            if (musicDay[i].day.year == day.year &&
                musicDay[i].day.month == day.month &&
                musicDay[i].day.day == day.day) {
                return i;
            }
        }
        return -1;
    }

void updateMusicDay(History* ptr, MusicDay** musicDay, int* musicDaysCount) {
    Date day = getHistoryTimestamp(ptr).date;
    int dayIndex = findDayIndex(*musicDay, *musicDaysCount, day);

    if (dayIndex == -1) {
        // Se o dia não foi encontrado, cria um novo dia
        MusicDay* new_musicDay = realloc(*musicDay, (*musicDaysCount + 1) * sizeof(MusicDay));
        if (!new_musicDay) {
            printf("Erro ao alocar memória para MusicDay!\n");
            free(*musicDay);
            exit(1);
        }
        *musicDay = new_musicDay;
        (*musicDay)[*musicDaysCount].day = day;
        (*musicDay)[*musicDaysCount].totalPlays = 0;
        dayIndex = (*musicDaysCount)++;
    }

    // Aumenta o contador de músicas para o dia
    (*musicDay)[dayIndex].totalPlays++;
}


    // Structures and functions used to store the genre


    typedef struct {
    Genre genre;  // O gênero da música (utiliza a enumeração Genre)
    int musicArtistCount;
    int time;     // Tempo total de reprodução em segundos
    } GenreCount;

// Função que atualiza o tempo de reprodução de cada gênero
int durationToSeconds(Duration duration) {
    return (duration.hours * 3600) + (duration.minutes * 60) + duration.seconds;
}


void updateGenreTime(GenreCount** genreCount, int* genreCountSize, Genre genre, Duration duration) {
    int genreIndex = -1;
    for (int i = 0; i < *genreCountSize; i++) { // Verifica se o gênero já foi registrado
        if ((*genreCount)[i].genre == genre) {
            (*genreCount)[i].time += durationToSeconds(duration);// Se já foi registrado, adiciona o tempo de reprodução
            genreIndex = i;
            break;
        }
    }

    // Se o gênero não foi encontrado, cria uma nova entrada
    if (genreIndex == -1) {
        *genreCount = realloc(*genreCount, (*genreCountSize + 1) * sizeof(GenreCount));
        (*genreCount)[*genreCountSize].genre = genre;
        (*genreCount)[*genreCountSize].time = durationToSeconds(duration);  // Inicializa com o tempo
        (*genreCountSize)++;
    }
}

Genre getMostHeardGenre(GenreCount* genreCount, int genreCountSize) {
    int maxTime = 0;
    Genre mostHeardGenre = 0;

    for (int i = 0; i < genreCountSize; i++) {
        if (genreCount[i].time > maxTime) {
            maxTime = genreCount[i].time;
            mostHeardGenre = genreCount[i].genre;
        }
    }

    return mostHeardGenre;
}




typedef struct {
    int album_id;  // ID do álbum
    int time;      // Tempo total ouvido em segundos
} AlbumListenData;



AlbumListenData* updateAlbumData(AlbumListenData* albumData, int* albumCount, int album_id, Duration duration) {
    int index = -1;

    for (int i = 0; i < *albumCount; i++) { // Procura pelo álbum
        if (albumData[i].album_id == album_id) {
            index = i;
            break;
        }
    }

    if (index != -1) { // Atualiza tempo se encontrado
        albumData[index].time += durationToSeconds(duration);
    } else { // Caso contrário, adiciona um novo álbum
        AlbumListenData* new_albumData = realloc(albumData, (*albumCount + 1) * sizeof(AlbumListenData));
        if (!new_albumData) {
            printf("Erro ao alocar memória para AlbumListenData!\n");
            free(albumData);
            exit(1);
        }
        albumData = new_albumData;
        albumData[*albumCount].album_id = album_id;
        albumData[*albumCount].time = durationToSeconds(duration);
        (*albumCount)++;
    }

    return albumData;
}


int findMostListenedAlbum(AlbumListenData* albumData, int albumCount) {
    if (albumCount == 0) return -1;

    int maxIndex = 0;
    for (int i = 1; i < albumCount; i++) {
        if (albumData[i].time > albumData[maxIndex].time) {
            maxIndex = i;
        }
    }
    return albumData[maxIndex].album_id;
}



typedef struct HourCount {
    int hour;     
    int count;    
} HourCount;



HourCount* updateHourCount(HourCount* hours, int* count, Duration duration, int hour) {
    int totalSeconds = duration.hours * 3600 + duration.minutes * 60 + duration.seconds;  // Converter tudo para segundos

    for (int i = 0; i < *count; i++) {
        if (hours[i].hour == hour) {
            hours[i].count += totalSeconds;  // Somar o tempo em segundos
            return hours;
        }
    }

    // Se a hora não for encontrada, adiciona uma nova
    hours = realloc(hours, (*count + 1) * sizeof(HourCount));
    hours[*count].hour = hour;
    hours[*count].count = totalSeconds;  // Armazena o tempo em segundos
    (*count)++;

    return hours;
}



int findMostListenedHour(HourCount* hours, int count) {
    int mostListenedHour = -1;
    int maxCount = 0;

    for (int i = 0; i < count; i++) {
        if (hours[i].count > maxCount) {
            maxCount = hours[i].count;
            mostListenedHour = hours[i].hour;
        }
    }

    return mostListenedHour;
}


void query6(CMD* cmd, HistoryManager* h_mngr, MusicManager* m_mngr, int cmdCounter) {
    int userId = getCMDId(cmd);
    int nMusics = 0;

    Duration listenTime = {0, 0, 0, 0}; 
    History* history = lookupHistoryHashByUser(h_mngr, userId);
    ListenedMusicNode* listenedList = NULL; 
    ArtistListenData* artistData = NULL;
    MusicDay* musicDay = NULL;
    GenreCount* genreCount = NULL;
    AlbumListenData* albumData = NULL;
    HourCount* hourCount = NULL;

    int artistCount = 0;
    int musicDaysCount = 0;
    int genreCountSize = 0;
    int albumCount = 0;
    int hourCountSize = 0;

    char filename[50];
    snprintf(filename, sizeof(filename), "resultados/command%d_output.txt", cmdCounter);
    Output* output = openOutputFile(filename);

    if (history == NULL) {
        writeNewLine(output);
      //  printf("Error: No history found for ID %d.\n\n", userId);
        closeOutputFile(output);

        freeMusicList(listenedList);
        free(artistData);
        free(musicDay);
        free(genreCount);
        free(albumData);
        free(hourCount);
        deleteHistoryByUser(history);

        return;
    }

    History* ptr = history;

    while (ptr != NULL) {
        int currentYear = getHistoryTimestamp(ptr).date.year;
        int intendedYear = getCMDyear(cmd);

        if (currentYear == intendedYear) { 
            listenTime = calculateListenTime(ptr, listenTime);

            int music_id = getHistoryMusicId(ptr);
            if (!wasMusicListened(listenedList, music_id)) {
                nMusics++;
                listenedList = addMusic(listenedList, music_id);
            }

            Music* music = lookupMusicHash(m_mngr, music_id);
            if (music == NULL) {
                ptr = getNextHistoryByUser(ptr);
                continue;
            }

            const int* artist_id_ptr = getMusicArtistID(music);
            if (artist_id_ptr == NULL) {
                ptr = getNextHistoryByUser(ptr);
                deleteMusic(music);
                continue;
            }

            int artist_id = *artist_id_ptr;
            Duration duration = getHistoryDuration(ptr);
            artistData = updateArtistData(artistData, &artistCount, artist_id, music_id, duration);

            updateMusicDay(ptr, &musicDay, &musicDaysCount);

            Genre genre = getMusicGenre(music);
            updateGenreTime(&genreCount, &genreCountSize, genre, duration);

            int album_id = getMusicAlbumID(music);
            albumData = updateAlbumData(albumData, &albumCount, album_id, duration);


            Duration hourDuration = getHistoryTimestamp(ptr).hour;
            int hourInt = hourDuration.hours;
            hourCount = updateHourCount(hourCount, &hourCountSize, duration, hourInt);


            deleteMusic(music);
        }

        ptr = getNextHistoryByUser(ptr);
    }
    free(ptr);

    sortArtistsByListeningTime(artistData,artistCount);

    Genre mostHeardGenre = getMostHeardGenre(genreCount, genreCountSize);

    if (artistData == NULL){
        writeNewLine(output);
     //   printf("Error: No history found for ID %d.\n\n", userId);
        closeOutputFile(output);

        freeMusicList(listenedList);
        free(artistData);
        free(musicDay);
        free(genreCount);
        free(albumData);
        free(hourCount);
        deleteHistoryByUser(history);
        return;
    }

    ArtistListenData mostListenedArtist = artistData[0];
    int mostListenedArtist2 = mostListenedArtist.artist_id;

    Date mostListenedDay = findMostListenedDay(musicDay, musicDaysCount);
    int mostListenedAlbum = findMostListenedAlbum(albumData, albumCount);
    int mostListenedHour = findMostListenedHour(hourCount, hourCountSize);

    if (mostListenedDay.year == 0) { 
        writeNewLine(output);
     //   printf("Error: No history found for ID %d.\n\n", userId);
        closeOutputFile(output);

        freeMusicList(listenedList);
        free(artistData);
        free(musicDay);
        free(genreCount);
        free(albumData);
        free(hourCount);
        deleteHistoryByUser(history);
        return;
    }

  //  int hour = listenTime.hours;
  //  int min = listenTime.minutes;
  //  int seg = listenTime.seconds;
//
  //  int ano = mostListenedDay.year;
  //  int mes = mostListenedDay.month;
  //  int dia = mostListenedDay.day;

    int nArtists = getCMDnArtists(cmd);

//typedef struct {
//    int artist_id;           // ID do artista
//    int totalMusic;          // Contador de músicas ouvidas
//    Duration totalTime;      // Duração total
//    int* music_ids;          // Array dinâmico de IDs de músicas ouvidas
//    int music_ids_count;     // Número de músicas no array
//    int music_ids_capacity;  // Capacidade atual do array
//} ArtistListenData;

    const char* mostHeardGenreString = genreToString(mostHeardGenre);
  //  printf("%02d:%02d:%02d;%d;A%07d;%04d/%02d/%02d;%s;AL%06d;%02d\n", hour, min, seg, nMusics, mostListenedArtist2, ano, mes, dia, genreToString(mostHeardGenre), mostListenedAlbum, mostListenedHour);
    writeQ6Geral(output, cmd, listenTime, mostListenedDay, nMusics, mostListenedArtist2, mostHeardGenreString, mostListenedAlbum, mostListenedHour);

    for(int i=0; i<nArtists && i<artistCount; i++){
        ArtistListenData mostListenedArtist = artistData[i];
        int mostListenedArtist2 = mostListenedArtist.artist_id;
        int nMusicsArtist = mostListenedArtist.totalMusic;
        Duration listenedTimeArtist = mostListenedArtist.totalTime;

        writeQ6Artists(output, cmd, mostListenedArtist2, nMusicsArtist, listenedTimeArtist);
    }

   // printf("NART: %d,  duração: %d:%d:%d  \n dia: %d-%02d-%02d \n   hora Mais Ouvida: %d,  album: %d,  nMusicas: %d,  Artista: %d, Gênero: %s,  IdHistory: %d, IDUser: %d\n\n",
   //     nArtists, hour, min, seg, ano, mes, dia,mostListenedHour, mostListenedAlbum, nMusics, mostListenedArtist2, genreToString(mostHeardGenre), userId, userId);

    closeOutputFile(output);
    freeMusicList(listenedList);
    free(artistData);
    free(musicDay);
    free(genreCount);
    free(albumData);
    free(hourCount);
    deleteHistoryByUser(history);
}


    Duration calculateListenTime (History* history, Duration listenTime){
            Duration currentDuration = getHistoryDuration(history);

            int hours = currentDuration.hours;
            int min = currentDuration.minutes;
            int sec = currentDuration.seconds;

            listenTime.hours += hours;
            listenTime.minutes += min;
            listenTime.seconds += sec;

            if (listenTime.seconds >= 60){ // checks if the duration is more than 60 seconds and corrects it
                listenTime.minutes += listenTime.seconds / 60;
                listenTime.seconds = listenTime.seconds % 60;
            }

            if (listenTime.minutes >= 60){ // checks if the duration is more than 60 minutes and corrects it
                listenTime.hours += listenTime.minutes / 60;
                listenTime.minutes = listenTime.minutes % 60;
            }

            
        return listenTime;
    }


/*



for (int i = 0; i < artistCount; i++) {
    free(artistData[i].music_ids);
}
ver se é preciso fazer isto

00:04:47;1;A0009964;2019/12/13;Hip Hop;AL006156;07
A0009964;1;00:04:47



typedef struct cmd {
    int query;          // 1, 2, 3, 4, 5, or 6
    char entity;       // A or U (Q1)
    int id;             // entity ID
    int topN;           // top N places
    char *paises;       // (requires memory allocation)
    int ageMin;         // minimum age
    int ageMax;         // maximum age
    Date dateMin;       // minimum date
    Date dateMax;       // max date
    int noUsers;        // number of users to compare with
    short int year;     // year
    short int nArtists; // number of artists
    char separator;     // separator for output (';' or '=')
} CMD;


typedef struct history {
    int id;                   //– identificador único do registo;
    int user_id;              //– identificador único do utilizador a que o registo se refere;
    int music_id;             //– identificador único da música a que o registo se refere;
    Timestamp timestamp;      //– data e hora em que a música foi ouvida pelo utilizador;
    Duration duration;        //– tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
    History* nextByUser;      // points to a History* w the same user_id
    History* nextByMusic;     // points to a History* w the same music_id
} History;

typedef struct historyManager {
    GHashTable *historyByUser;
    GHashTable *historyByMusic;
    GTree* historyInWeeks; // will only have the top 10 artists of each week, key: first day of the week, value: array with artists and duration
} HistoryManager;


typedef struct {
    int hours;         
    int minutes;       
    int seconds;       
    short int error;   
} Duration;

*/