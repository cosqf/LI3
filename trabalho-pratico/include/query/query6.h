#include <almightyManager.h>
#include <cmd.h>
#include <historyManager.h>
#include <utils.h>


#ifndef _QUERY6_H_
#define _QUERY6_H_

/**
 * @brief Linked list used to store the music that was already been listened by the user
*/
typedef struct ListenedMusicNode {
    int music_id;                     
    struct ListenedMusicNode* next;   
} ListenedMusicNode;

/**
 * @brief Structure that stores information of an Artist about the history of a certain User 
*/
typedef struct {
    int artist_id;
    int totalMusic;
    Duration totalTime;
    int* music_ids;
    int music_ids_count;
    int music_ids_capacity;
} ArtistListenData;

/**
 * @brief Structure that stores the total number of songs played in a day
*/
typedef struct {
    Date day;
    int totalPlays;
} MusicDay;

/**
 * @brief Structure that stores the time that a genre was been played
*/
typedef struct {
    Genre genre;
    int musicArtistCount;
    int time;
} GenreCount;

/**
 * @brief Structure that stores the time that a Album was been played
*/
typedef struct {
    int album_id;
    int time;
} AlbumListenData;

/**
 * @brief Structure that stores an hour and the total seconds of music played during that our
*/
typedef struct HourCount {
    int hour;     
    int count;    
} HourCount;

/**
 * @brief Verifies if the minutes or seconds of the duration are bigger than 60 and corrects them
 * 
 * @param duration 
*/
Duration correctTime (Duration duration);

/**
* @brief Compares two @c Date to confirm what is more recent.
*
* @param d1 the first @c Date to compare.
* @param d2 the second @c Date to compare.
*
* @return an integer positive if d1 it's more recent than d2 and negative if it's not.
*/
int compareDates(Date d1, Date d2);

/**
* @brief Updates the Listen Time of a user.
*
* @param history Pointer to the history struct.
* @param listenTime Variable of the type @c Duration that will be updated with data from history
*
* @return the listenTime after being updated
*/
Duration updateListenTime (History* history, Duration listenTime);

/**
* @brief Add musics to the linked list ListenedMusicNode
*
* @param head Pointer to the head of the linked list
* @param music_id The unique identifier of the music to be added
*
* @return Pointer to the updated head of the linked list
*/
ListenedMusicNode* addMusic(ListenedMusicNode* head, int music_id);

/**
* @brief Checks if a music ID exists in the linked list ListenedMusicNode
*
* @param head Pointer to the head of the linked list
* @param music_id The unique indentifier of the music to search for in the list
*
* @return 1 if the music ID exists in the linked list and 0 otherwise
*/
int wasMusicListened(ListenedMusicNode* head, int music_id);

/**
* @brief Frees all nodes in a linked list of @c ListenedMusicNode
*
* @param head Pointer to the head of the linked list
*/
void freeMusicList(ListenedMusicNode* head);

/**
* @brief Finds the index of an artist in an array of ArtistListenedData
*
* @param array Pointer to the array of ArtistListenedData
* @param size The number of elements in the array
* @param artist_id THe unique identifier of the artist to search for
*
* @return the index of the artist if it exists in the array and -1 if the artist is not present in the array
*/
int findArtistIndex(ArtistListenData* array, int size, int artist_id);

/**
* @brief Compares two artists based on their listening time or, if the listening time isn't equal, their IDs
*
* @param a Pointer to the first @c ArtistListenData structure to compare.
* @param b Pointer to the second @c ArtistListenData structure to compare.
*
* @return A positive number if the first artist should be the first, a negative number if shoud be the second and 0 if their listening time is equal
*/
int compareArtists(const void* a, const void* b);

/**
* @brief Sorts an array of artists by their total listening Time in descending order
*
* @param array Pointer to the array of @c ArtistListenData structures
* @param size The number of elements in the array
*/
void sortArtistsByListeningTime(ArtistListenData* array, int size);

/**
* @brief Updates the data of an artist in the array or adds a new artist if it isn't yet in the array
*
* @param array Pointer to the array of @c ArtistListenData structures
* @param size Pointer to the number of elements in the array
* @param artist_id The unique indentifier of the artist whose data is being updated
* @param music_id The unique indentifier of the music being added to the music_ids in @c ArtistListenData
* @param duration a @c Duration structure that represents the time spent listening to the music with the ID music_id
*
* @return A pointer to the updated array of @c ArtistListenData
*/
ArtistListenData* updateArtistData(ArtistListenData* array, int* size, int artist_id, int music_id, Duration duration);

/**
* @brief Frees all nodes in a linked list of @c ArtistListenData
*
* @param artistData Pointer to the head of the linked list
*/
void freeArtistListenData (ArtistListenData* artistData);

/**
* @brief Finds the day with the most music plays
*
* @param musicDay Pointer to an array of @c MusicDay structure
* @param musicDaysCount The number of elements in the array.
*
* @return A @c Date structure representing the day with the most music plays
*/
Date findMostListenedDay(MusicDay* musicDay, int musicDaysCount);

/**
* @brief Finds the index of an specific day in an array of @c MusicDay
*
* @param musicDay Pointer to ano array of @c MusicDay structures
* @param musicDaysCount The number of elements in the array
* @param day the @c Date that will be search in the array
*
* @return The index of the day if it exists in the array, and -1 is not
*/
int findDayIndex(MusicDay* musicDay, int musicDaysCount, Date day);

/**
* @brief Updates the play count for a specific day in the @c MusicDay array
*
* @param ptr A pointer ti the @c History structure
* @param musicDay Pointer to a pointer to the aray of @c MusicDay structures
* @param musicDaysCount Pointer to the number of elements in the array
*/
void updateMusicDay(History* ptr, MusicDay** musicDay, int* musicDaysCount);

/**
* @brief Updates the total time for a specific genre in the @c GenreCount array 
*
* @param genreCount Pointer to a pointer to the array of @c GenreCount structures
* @param genreCountSize Pointer ti the number of elements in the @c GenreCount array
* @param genre The @c Genre to be updated or added if it isn't in the array yet
* @param duration The @c Duration to be added to the genre's total play time.
*/
void updateGenreTime(GenreCount** genreCount, int* genreCountSize, Genre genre, Duration duration);

/**
* @brief Finds the most heard genre in a array of @c GenreCount structures
*
* @param genreCount Array of @c GenreCount structures
* @param genreCountSize The number of elements in the array
*
* @return THe genre with the highest play time
*/
Genre getMostHeardGenre(GenreCount* genreCount, int genreCountSize);

/**
* @brief Updates the play time for a specific album in a array of @c AlbumListenData structures
*
* @param albumData Pointer to the array of @c AlbumListenData structures
* @param albumCount Pointer to the number of elements in the array of @c AlbumListenData
* @param album_id The unique indentifier of the album being updated or added to the array of @c AlbumListenData structures
* @param duration The @c Duration to be added to the album with "album_id" ID 
*
* @return A pointer to the updated array of @c AlbumListenData structures
*/
AlbumListenData* updateAlbumData(AlbumListenData* albumData, int* albumCount, int album_id, Duration duration);

/**
* @brief Finds the album with the most play time
*
* @param albumData Array of @c AlbumListenData structures
* @param albumCount The number of elements in the array of @c AlbumListenData structures
*
* @return The id of the album with the highest play time or -1 if the array is empty
*/
int findMostListenedAlbum(AlbumListenData* albumData, int albumCount);

/**
* @brief Updates the total time for a specific hour in the array of @c HourCount structures
*
* @param hours Pointer to the array of @c HourCount structures
* @param count Pointer to the number of elements in the array of @c HourCount structures
* @param duration The @c Duration to be added to the "hour" current time
* @param hour The hour to be updated or added to the array of @c HourCount structures
*
* @return A pointer to the updated array of @c HourCount structures
*/
HourCount* updateHourCount(HourCount* hours, int* count, Duration duration, int hour);

/**
* @brief Finds the hour with the most listening time the the array of @c HourCount structures
*
* @param hours Pointer to the array of @c HourCount structures
* @param count The number of elements in the array of @c HourCount structures
*
* @return
*/
int findMostListenedHour(HourCount* hours, int count);

/**
 * @brief Counts how often artists appear in the weekly top 10, optionally applying a date filter.

 * @param key Pointer to the week's start date.
 * @param value Pointer to the ArtistList for that week.
 * @param dataFeed Pointer to feederHistory with filter settings and results.
 * @return TRUE to stop early if the date exceeds the range; FALSE otherwise.
 */
void query6(CMD* cmd, HistoryManager* h_mngr, MusicManager* m_mngr, int cmdCounter);

/**
 * @brief Frees all the additional structures created for the resolution of query 6.

 * @param history Pointer to the history struct.
 * @param listenedList Pointer to a ListenedMusicNode struct.
 * @param artistData Pointer to an ArtistListenData struct.
 * @param musicDay Pointer to a MusicDay struct.
 * @param genreCount Pointer to a GenreCount struct.
 * @param albumData Pointer to a AlbumListenData struct.
 * @param hourCount Pointer to an HourCount struct.
 */
void freeQ6Data (History* history, ListenedMusicNode* listenedList, ArtistListenData* artistData, MusicDay* musicDay, GenreCount* genreCount, AlbumListenData* albumData, HourCount* hourCount);

/**
 * @brief Formats and prints the first line of the output to the correct file.

 * @param output Pointer to the Output structure.
 * @param cmd Pointer to the command struct.
 * @param listenTime Total listening time.
 * @param mostListenedDay Day with most listening time.
 * @param nMusics Number of musics listened to.
 * @param mostListenedArtist Most listened artist ID.
 * @param mostHeardGenreString Most listened genre string.
 * @param mostListenedAlbum Most listened album ID.
 * @param mostListenedHour Most listened hour.
 */
void q6Output (Output* output, CMD* cmd, Duration listenTime, Date mostListenedDay, int nMusics, int mostListenedArtist, const char* mostHeardGenreString, int mostListenedAlbum, int mostListenedHour);

/**
 * @brief Formats and prints the optional N artists to the correct output file.

 * @param output Pointer to the Output structure.
 * @param cmd A pointer to the command struct.
 * @param mostListenedArtist Most listened artist ID.
 * @param nMusicsArtist Number of musics heard from said artist.
 * @param listenedTimeArtist Time spent listening to said artist.
 */
void q6NArtistsOutput (Output* output, CMD* cmd, int mostListenedArtist, int nMusicsArtist, Duration listenedTimeArtist);

#endif