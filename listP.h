#ifndef PRACTICA_SO_LISTM_H
#define PRACTICA_SO_LISTM_H
#define MNULL NULL
#include "includes.h"

typedef struct {
    int pid;
    char launch[100],status[100];
}tItemP;
typedef struct tNodeP* tPosP;
struct tNodeP{
    tItemP data;
    tPosP next;
};
typedef tPosP tListP;

void initItem(tItemP *i, int pid,char * launch, char * status);
void createEmptyListM(tListP *L);
bool isEmptyListM(tListP L);
tPosP firstM(tListP L);
tPosP lastM(tListP L);
tPosP nextM(tPosP P, tListP L);
tPosP previousM(tPosP P, tListP L);
tItemP getDataM(tPosP P, tListP L);
tPosP findDataM(int I, tListP L);
tPosP findKey(int I, tListP L);
tPosP findFich(char *name, tListP L);
tPosP findDir(void * add,tListP L);
bool insertDataM(const tItemP i, tListP *L);
void deleteAtPosM(tPosP p,tListP *L);
void delListM(tListP *L);
#endif //PRACTICA_SO_LISTM_H
