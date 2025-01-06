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
 * @brief Counts how often artists appear in the weekly top 10, optionally applying a date filter.

 * @param key Pointer to the week's start date.
 * @param value Pointer to the ArtistList for that week.
 * @param dataFeed Pointer to feederHistory with filter settings and results.
 * @return TRUE to stop early if the date exceeds the range; FALSE otherwise.
 */





void query6(CMD* cmd, HistoryManager* h_mngr, MusicManager* m_mngr, int cmdCounter);

Duration calculateListenTime (History* history, Duration listenTime);

//int findDayIndex(MusicDay* musicDay, int musicDaysCount, Date day);

typedef struct ListenedMusicNode ListenedMusicNode;

typedef struct ArtistListenData ArtistListenData;

typedef struct MusicDay MusicDay;

typedef struct GenreCount GenreCount;

typedef struct AlbumListenData AlbumListenData;

typedef struct HourCount HourCount;

void freeQ6Data (History* history, ListenedMusicNode* listenedList, ArtistListenData* artistData, MusicDay* musicDay, GenreCount* genreCount, AlbumListenData* albumData, HourCount* hourCount);

void q6Output (Output* output, CMD* cmd, Duration listenTime, Date mostListenedDay, int nMusics, int mostListenedArtist, const char* mostHeardGenreString, int mostListenedAlbum, int mostListenedHour);

void q6NArtistsOutput (Output* output, CMD* cmd, int mostListenedArtist, int nMusicsArtist, Duration listenedTimeArtist);

#endif