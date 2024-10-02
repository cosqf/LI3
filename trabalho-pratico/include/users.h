#include <stdio.h>

typedef struct {
    int year;    //aaaa (<=2024)
    int month;   //mm   (01-12)
    int day;     //dd   (01-31)
} Date;

typedef struct {
    char* username;           //– identificador único do utilizador;
    char* email;              //– email de registo do utilizador;
    char* first_name;         //– primeiro nome do utilizador;
    char* last_name;          //– apelido do utilizador;
    Date birth_date;          //– data de nascimento;
    char* country;            //– país onde a conta do utilizador foi registada;
    int subscription_type;    //– tipo de subscrição, i.e., normal(0) ou premium(1);
    int* liked_musics_id;     //– lista de identificadores únicos das músicas gostadas pelo utilizador.
} User;

