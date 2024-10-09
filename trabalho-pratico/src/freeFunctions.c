#include <users.h>
#include <musics.h>
#include <artists.h>
#include <parsingUtils.h>
#include <stdlib.h>
#include <parsingCmd.h>

void freeCmd (CMD *cmd) {
    if (cmd->paises) free (cmd->paises);
    free (cmd);
}
/*
void freeUser(User *user) {
    if (user) {
        if (user->email) free (user->email);
        if (user->first_name) free (user->first_name);
        if (user->last_name) free (user->last_name);
        if (user->country) free (user->country);
        if (user->liked_musics_id) free (user->liked_musics_id);
        free(user);
    }
}

void freeArtist(Artist *artist) {
    if (artist) {
        if (artist->name) free (artist->name);
        if (artist->description) free (artist->description);
        if (artist->id_constituent) free (artist->id_constituent);
        if (artist->country) free (artist->country);
        free (artist);
    }
}

void freeMusic (Music *music) {
    if (music) {
        if (music->title) free (music->title);
        if (music->artist_id) free (music->artist_id);
        if (music->genre) free (music->genre);
        if (music->lyrics) free (music->lyrics);
        free (music);
    }
}
void freeUserRaw(UserRaw *user) {
    if (user) {
        if (user->username) free (user->username);
        if (user->email) free (user->email);
        if (user->first_name) free (user->first_name);
        if (user->last_name) free (user->last_name);
        if (user->country) free (user->country);
        if (user->birth_date) free (user->birth_date);
        if (user->subscription_type) free (user->subscription_type);
        if (user->liked_musics_id) free (user->liked_musics_id);
        free(user);
    }
}

void freeArtistRaw(ArtistRaw *artist) {
    if (artist) {
        if (artist->id) free(artist->id);
        if (artist->name) free(artist->name);
        if (artist->description) free(artist->description);
        if (artist->recipe_per_stream) free(artist->recipe_per_stream);
        if (artist->id_constituent) free(artist->id_constituent);
        if (artist->country) free(artist->country);
        if (artist->type) free(artist->type);
        free(artist);
    }
}


void freeMusicRaw(MusicRaw *music) {
    if (music) {
        if (music->id) free(music->id);
        if (music->title) free(music->title);
        if (music->artist_id) free(music->artist_id);
        if (music->duration) free(music->duration);
        if (music->genre) free(music->genre);
        if (music->year) free(music->year);
        if (music->lyrics) free(music->lyrics);
        free(music);
    }
}
*/