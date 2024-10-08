#include <stdio.h>
#include <musics.h>


//SYNTAX VALIDATION


Duration parseDuration(char* dur){
    Duration duration;

    if (sscanf(dur, "%d:%d:%d", &duration.hours, &duration.minutes, &duration.seconds) != 3) duration.error = 1;

    else if(duration.hours < 0 || duration.hours > 99 || duration.minutes < 0 || duration.minutes > 59 || duration.seconds < 0 || duration.seconds > 59) duration.error = 0;
    
    return duration;
}



//LOGIC VALIDATION

/*
• Utilizadores:
– O campo liked_musics_id de um utilizador, deverá conter apenas mú-
sicas existentes e válidas.
*/
int valid_likes(int* liked_musics_id, int liked_musics_count){
    for(int i = 0; i < liked_musics_count; i++){
        
    }
}
//


/*
• Músicas:
– O campo artist_id de uma música, deverá corresponder a um artista
existente e válido.
*/
int valid_artistid(){

}


/*
• Artistas:
– O campo id_constituent de um artista individual não poderá ter ele-
mentos.
*/
int valid_idconst(){

}