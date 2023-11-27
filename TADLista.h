/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es
            Antón Soto Ríos - anton.soto@udc.es**/

#ifndef LIST_H
#define LIST_H


#include "includes.h"



#define LNULL NULL
#define COMAND 200

typedef struct tNode* tPosL;
struct tNode{
    char comand[COMAND];
    tPosL next;
};
typedef tPosL tList;


//Funciones de operación de la lista
void createEmptyList(tList *L);
bool isEmptyList(tList L);
tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL P, tList L);
tPosL previous(tPosL P, tList L);
char* getItem(tPosL P, tList L);
tPosL findItem(int I, tList L);
bool insertItem(char *I, tList *L);
void delHistoric( tList *L);


#endif