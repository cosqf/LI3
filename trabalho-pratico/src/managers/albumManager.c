#include <glib.h>
#include <albumManager.h>

typedef struct albumManager {
    GHashTable *album;
} AlbumManager;

bool isAlbumInHash (AlbumManager *a_mngr, int id) {
    Album* album = g_hash_table_lookup (a_mngr->album, GINT_TO_POINTER(id));
    if (album == NULL) return 0;
    else return 1;
}
