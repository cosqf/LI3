#include <album.h>
#include <utils.h>
#include <parsingUtils.h>
#include <errorfiles.h>
#include <stdlib.h>

typedef struct album {
    int id;                         //– identificador único do álbum;
    char* title;                    //– título do álbum;
    int* artist_id;                 //– lista de identificadores únicos dos artistas que lançaram o álbum;
    unsigned int artist_id_count;
    short int year;                 //– ano de lançamento;
} Album;

typedef struct albumString {
    char* id;                   //– identificador único do álbum;
    char* title;                //– título do álbum;
    char* artist_id;            //– lista de identificadores únicos dos artistas que lançaram o álbum;
    unsigned int artist_id_count;
    char* year;                 //– ano de lançamento;
    char* producers;            //– lista de produtores.
} AlbumString;


