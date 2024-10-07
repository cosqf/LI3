#include <users.h>
#include <musics.h>
#include <artists.h>
#include <processInput.h>
#include <stdlib.h>

void freeCmd (CMD *cmd) {
    if (cmd->paises) free (cmd->paises);
    free (cmd);
}

void freeUser(User *user) {
    if (user) {
        free(user->email);
        free(user->first_name);
        free(user->last_name);
        free(user->country);
        free(user->liked_musics_id);
        if (user->buffer) free (user->buffer);
        free(user);
    }
}

void freeArtist(Artist *artist) {
    if (artist) {
        free (artist->name);
        free (artist->description);
        if (artist->id_constituent_counter>0) free (artist->id_constituent);
        free (artist->country);
        free (artist);
    }
}

void freeMusic (Music *music) {
    if (music) {
        free (music->title);
        if (music->artist_id_counter > 0) free (music->artist_id);
        if (music->buffer) free (music->buffer);
        free (music->genre);
        free (music->lyrics);
        free (music);
    }
}