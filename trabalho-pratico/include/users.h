#include <stdio.h>
#ifndef _USERS_H_
#define _USERS_H_

typedef struct {
    int year;    //aaaa (<=2024)
    int month;   //mm   (01-12)
    int day;     //dd   (01-31)
    short int error; 
} Date;

typedef struct {
    int username;           //– identificador único do utilizador;
    char* email;              //– email de registo do utilizador;
    char* first_name;         //– primeiro nome do utilizador;
    char* last_name;          //– apelido do utilizador;
    Date birth_date;          //– data de nascimento;
    char* buffer;             //– buffer;
    char* country;            //– país onde a conta do utilizador foi registada;
    int subscription_type;    //– tipo de subscrição, i.e., normal(0) ou premium(1);
    int* liked_musics_id;     //– lista de identificadores únicos das músicas gostadas pelo utilizador.
    int liked_musics_count;
} User;

#endif  
