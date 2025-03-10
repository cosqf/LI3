#include <historyManager.h>
#include <query6.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <history.h>
#include <userManager.h>
#include <cmd.h>
#include <utils.h>

Duration correctTime (Duration duration){
                if (duration.seconds >= 60){ // checks if the duration is more than 60 seconds and corrects it
                duration.minutes += duration.seconds / 60;
                duration.seconds = duration.seconds % 60;
            }

            if (duration.minutes >= 60){ // checks if the duration is more than 60 minutes and corrects it
                duration.hours += duration.minutes / 60;
                duration.minutes = duration.minutes % 60;
            }
    return duration;
}

int compareDates(Date d1, Date d2) {
    if (d1.year != d2.year) return d1.year - d2.year;
    if (d1.month != d2.month) return d1.month - d2.month;
    return d1.day - d2.day;
}

Duration updateListenTime (History* history, Duration listenTime){
    Duration currentDuration = getHistoryDuration(history);

    int hours = currentDuration.hours;
    int min = currentDuration.minutes;
    int sec = currentDuration.seconds;

    listenTime.hours += hours;
    listenTime.minutes += min;
    listenTime.seconds += sec;

    listenTime = correctTime (listenTime);

    return listenTime;
}

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

int wasMusicListened(ListenedMusicNode* head, int music_id) {
    ListenedMusicNode* current = head;
    while (current != NULL) {
        if (current->music_id == music_id)
            return 1;  // returns 1 if the music has found
        current = current->next;
    }
    return 0;  // returns 0 if the music hasn't found
}

void freeMusicList(ListenedMusicNode* head) {
    ListenedMusicNode* current = head;
    while (current != NULL) {
        ListenedMusicNode* temp = current;
        current = current->next;
        free(temp);
    }
}

int findArtistIndex(ArtistListenData* array, int size, int artist_id) {
    for (int i = 0; i < size; i++) {
        if (array[i].artist_id == artist_id)
            return i;
    }
    return -1;
}

int compareArtists(const void* a, const void* b) {
    const ArtistListenData* artistA = (const ArtistListenData*)a;
    const ArtistListenData* artistB = (const ArtistListenData*)b;

    int timeA = artistA->totalTime.hours * 3600 + artistA->totalTime.minutes * 60 + artistA->totalTime.seconds;
    int timeB = artistB->totalTime.hours * 3600 + artistB->totalTime.minutes * 60 + artistB->totalTime.seconds;

    if (timeA != timeB) 
        return timeB - timeA;

    return artistA->artist_id - artistB->artist_id;
}

void sortArtistsByListeningTime(ArtistListenData* array, int size) {
    qsort(array, size, sizeof(ArtistListenData), compareArtists);
}

ArtistListenData* updateArtistData(ArtistListenData* array, int* size, int artist_id, int music_id, Duration duration) {
    int index = findArtistIndex(array, *size, artist_id);

    if (index != -1) {

        array[index].totalTime.hours += duration.hours;
        array[index].totalTime.minutes += duration.minutes;
        array[index].totalTime.seconds += duration.seconds;

        array[index].totalTime = correctTime (array[index].totalTime);

        int already_listened = 0;
        for (int i = 0; i < array[index].music_ids_count; i++) {
            if (array[index].music_ids[i] == music_id) {
                already_listened = 1;
                break;
            }
        }

        if (!already_listened) {
            if (array[index].music_ids_count == array[index].music_ids_capacity) {

                int new_capacity = array[index].music_ids_capacity * 2;
                if (new_capacity == 0) new_capacity = 2;

                int* new_music_ids = realloc(array[index].music_ids, new_capacity * sizeof(int));
                if (!new_music_ids) {
                    printf("Erro ao alocar memória!\n");
                    return NULL;
                }

                array[index].music_ids = new_music_ids;
                array[index].music_ids_capacity = new_capacity;
            }

        array[index].music_ids[array[index].music_ids_count++] = music_id;
        array[index].totalMusic++;
    }

    }
    else {

        ArtistListenData* new_array = realloc(array, (*size + 1) * sizeof(ArtistListenData));
        if (!new_array) {
            printf("Erro ao alocar memória!\n");
            free(array);
            return NULL;
        }
        array = new_array;

        array[*size].artist_id = artist_id;
        array[*size].totalTime = duration;
        array[*size].totalMusic = 1;

        array[*size].music_ids_capacity = 2;
        array[*size].music_ids_count = 1;
        array[*size].music_ids = malloc(array[*size].music_ids_capacity * sizeof(int));
        if (!array[*size].music_ids) {
            printf("Erro ao alocar memória!\n");
            return NULL;
        }
        array[*size].music_ids[0] = music_id;

        (*size)++;
    }

    return array;
}

void freeArtistListenData (ArtistListenData* artistData) {
    for (int i = 0; i < artistData->music_ids_count; i++) free(artistData->music_ids);
    free(artistData);
}

Date findMostListenedDay(MusicDay* musicDay, int musicDaysCount) {
    Date mostListenedDay = {0, 0, 0, 0};
    int maxPlays = 0;

    for (int i = 0; i < musicDaysCount; i++) {
        if (musicDay[i].totalPlays > maxPlays || (musicDay[i].totalPlays == maxPlays && compareDates(musicDay[i].day, mostListenedDay) > 0)) {
            maxPlays = musicDay[i].totalPlays;
            mostListenedDay = musicDay[i].day;
        }
    }
    return mostListenedDay;
}

int findDayIndex(MusicDay* musicDay, int musicDaysCount, Date day) {
    for (int i = 0; i < musicDaysCount; i++) {
        if (musicDay[i].day.year == day.year && musicDay[i].day.month == day.month && musicDay[i].day.day == day.day)
                return i;
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
            return;
        }
        *musicDay = new_musicDay;
        (*musicDay)[*musicDaysCount].day = day;
        (*musicDay)[*musicDaysCount].totalPlays = 0;
        dayIndex = (*musicDaysCount)++;
    }

    (*musicDay)[dayIndex].totalPlays++;
}


void updateGenreTime(GenreCount** genreCount, int* genreCountSize, Genre genre, Duration duration) {
    int genreIndex = -1;
    for (int i = 0; i < *genreCountSize; i++) {
        if ((*genreCount)[i].genre == genre) {
            (*genreCount)[i].time += durationInSeconds(duration);
            genreIndex = i;
            break;
        }
    }
    if (genreIndex == -1) {
        *genreCount = realloc(*genreCount, (*genreCountSize + 1) * sizeof(GenreCount));
        (*genreCount)[*genreCountSize].genre = genre;
        (*genreCount)[*genreCountSize].time = durationInSeconds(duration);
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

AlbumListenData* updateAlbumData(AlbumListenData* albumData, int* albumCount, int album_id, Duration duration) {
    int index = -1;
    for (int i = 0; i < *albumCount; i++) {
        if (albumData[i].album_id == album_id) {
            index = i;
            break;
        }
    }

    if (index != -1)
        albumData[index].time += durationInSeconds(duration);
    else {
        AlbumListenData* new_albumData = realloc(albumData, (*albumCount + 1) * sizeof(AlbumListenData));
        if (!new_albumData) {
            printf("Erro ao alocar memória para AlbumListenData!\n");
            free(albumData);
            return NULL;
        }
        albumData = new_albumData;
        albumData[*albumCount].album_id = album_id;
        albumData[*albumCount].time = durationInSeconds(duration);
        (*albumCount)++;
    }
    return albumData;
}

int findMostListenedAlbum(AlbumListenData* albumData, int albumCount) {
    if (albumCount == 0) 
        return -1;
    int maxIndex = 0;
    for (int i = 1; i < albumCount; i++) {
        if (albumData[i].time > albumData[maxIndex].time)
            maxIndex = i;
    }
    return albumData[maxIndex].album_id;
}

HourCount* updateHourCount(HourCount* hours, int* count, Duration duration, int hour) {
    int totalSeconds = durationInSeconds(duration);
    for (int i = 0; i < *count; i++) {
        if (hours[i].hour == hour) {
            hours[i].count += totalSeconds;
            return hours;
        }
    }
    hours = realloc(hours, (*count + 1) * sizeof(HourCount));
    hours[*count].hour = hour;
    hours[*count].count = totalSeconds;
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
        closeOutputFile(output);
        freeQ6Data(history, listenedList, artistData, musicDay, genreCount, albumData, hourCount);
        return;
    }

    History* ptr = history;

    while (ptr != NULL) {
        int currentYear = getHistoryTimestamp(ptr).date.year;
        int intendedYear = getCMDyear(cmd);

        if (currentYear == intendedYear) { 
            listenTime = updateListenTime(ptr, listenTime);

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
            //if(artist_id == 377 && userId == 205751)
            //printf("AQUI");
            Duration duration = getHistoryDuration(ptr);
            artistData = updateArtistData(artistData, &artistCount, artist_id, music_id, duration);

            if (mallocErrorCheck(artistData)){
                writeNewLine(output);
                closeOutputFile(output);
                freeQ6Data(history, listenedList, artistData, musicDay, genreCount, albumData, hourCount);
                return;
            }

            updateMusicDay(ptr, &musicDay, &musicDaysCount);
            if (mallocErrorCheck(musicDay)){
                writeNewLine(output);
                closeOutputFile(output);
                freeQ6Data(history, listenedList, artistData, musicDay, genreCount, albumData, hourCount);
                return;
            }

            Genre genre = getMusicGenre(music);
            updateGenreTime(&genreCount, &genreCountSize, genre, duration);

            int album_id = getMusicAlbumID(music);
            albumData = updateAlbumData(albumData, &albumCount, album_id, duration);
            if (mallocErrorCheck(albumData)){
                writeNewLine(output);
                closeOutputFile(output);
                freeQ6Data(history, listenedList, artistData, musicDay, genreCount, albumData, hourCount);
                return;
            }

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
        closeOutputFile(output);
        freeQ6Data(history, listenedList, artistData, musicDay, genreCount, albumData, hourCount);
        return;
    }

    ArtistListenData mostListenedArtist = artistData[0];
    int mostListenedArtist2 = mostListenedArtist.artist_id;

    Date mostListenedDay = findMostListenedDay(musicDay, musicDaysCount);
    int mostListenedAlbum = findMostListenedAlbum(albumData, albumCount);
    int mostListenedHour = findMostListenedHour(hourCount, hourCountSize);

    int nArtists = getCMDnArtists(cmd);

    const char* mostHeardGenreString = genreToString(mostHeardGenre);

    q6Output(output, cmd, listenTime, mostListenedDay, nMusics, mostListenedArtist2, mostHeardGenreString, mostListenedAlbum, mostListenedHour);

    for(int i=0; i<nArtists && i<artistCount; i++){
        ArtistListenData mostListenedArtist = artistData[i];
        int mostListenedArtist2 = mostListenedArtist.artist_id;
        int nMusicsArtist = mostListenedArtist.totalMusic;
        Duration listenedTimeArtist = mostListenedArtist.totalTime;

        q6NArtistsOutput(output, cmd, mostListenedArtist2, nMusicsArtist, listenedTimeArtist);
    }

    closeOutputFile(output);
    freeQ6Data(history, listenedList, artistData, musicDay, genreCount, albumData, hourCount);
}

void freeQ6Data (History* history, ListenedMusicNode* listenedList, ArtistListenData* artistData, MusicDay* musicDay, GenreCount* genreCount, AlbumListenData* albumData, HourCount* hourCount) {
    freeMusicList(listenedList);
    free(artistData);
    free(musicDay);
    free(genreCount);
    free(albumData);
    free(hourCount);
    deleteHistoryByUser(history);
}

void q6Output (Output* output, CMD* cmd, Duration listenTime, Date mostListenedDay, int nMusics, int mostListenedArtist, const char* mostHeardGenreString, int mostListenedAlbum, int mostListenedHour) {
    char duration[15], musics[15], topArtist[15], topDay[15], topGenre[15], topAlbum[15], topHour[15];

    snprintf (duration, sizeof(duration), "%02d:%02d:%02d", listenTime.hours, listenTime.minutes, listenTime.seconds);
    snprintf (musics, sizeof(musics), "%d", nMusics);
    snprintf (topArtist, sizeof(topArtist), "A%07d", mostListenedArtist);
    snprintf (topDay, sizeof(topDay), "%04d/%02d/%02d", mostListenedDay.year, mostListenedDay.month, mostListenedDay.day);
    snprintf (topGenre, sizeof(topGenre), "%s", mostHeardGenreString);
    snprintf (topAlbum, sizeof(topAlbum), "AL%06d", mostListenedAlbum);
    snprintf (topHour, sizeof(topHour), "%02d", mostListenedHour);

    char* lines [7] = {duration, musics, topArtist, topDay, topGenre, topAlbum, topHour};

    setOutput (output, lines, 7);
    writeQuerys (output, cmd);
}

void q6NArtistsOutput (Output* output, CMD* cmd, int mostListenedArtist, int nMusicsArtist, Duration listenedTimeArtist) {
    char artist[15], musics[15], duration[15];

    snprintf (artist, sizeof(artist), "A%07d", mostListenedArtist);
    snprintf (musics, sizeof(musics), "%d", nMusicsArtist);
    snprintf (duration, sizeof(duration), "%02d:%02d:%02d", listenedTimeArtist.hours, listenedTimeArtist.minutes, listenedTimeArtist.seconds);

    char* lines [3] = {artist, musics, duration};

    setOutput (output, lines, 3);
    writeQuerys (output, cmd);
}
