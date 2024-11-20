#include <history.h>
#include <utils.h>
#include <parsingUtils.h>
#include <errorfiles.h>
#include <stdlib.h>

typedef struct history {
    int id;                   //– identificador único do registo;
    int user_id;              //– user_id – identificador único do utilizador a que o registo se refere;
    int music_id;             //– music_id – identificador único da música a que o registo se refere;
    Date timestamp;            //– timestamp – data e hora em que a música foi ouvida pelo utilizador;
    Duration* duration;             //– duration – tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
    char* platform;             //– platform – plataforma em que a música foi reproduzida. I.e., computador ou dispositivo móvel.
} History;

typedef struct albumString {
    char* id;                   //– identificador único do registo;
    char* user_id;              //– user_id – identificador único do utilizador a que o registo se refere;
    char* music_id;             //– music_id – identificador único da música a que o registo se refere;
    char* timestamp;            //– timestamp – data e hora em que a música foi ouvida pelo utilizador;
    char* duration;             //– duration – tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
    char* platform;             //– platform – plataforma em que a música foi reproduzida. I.e., computador ou dispositivo móvel.
} AlbumString;












//– id – identificador único do registo;
//– user_id – identificador único do utilizador a que o registo se refere;
//– music_id – identificador único da música a que o registo se refere;
//– timestamp – data e hora em que a música foi ouvida pelo utilizador;
//– duration – tempo de duração da audição da música. E.g., um utilizador pode ter ouvido apenas 30 segundos de uma música;
//– platform – plataforma em que a música foi reproduzida. I.e., computador ou dispositivo móvel.