#include <almightyManager.h>
#include <cmd.h>
#include <historyManager.h>


#ifndef _QUERY6_H_
#define _QUERY6_H_

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