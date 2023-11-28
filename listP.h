#ifndef PRACTICA_SO_LISTM_H
#define PRACTICA_SO_LISTM_H
#define PNULL NULL
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
void createEmptyListP(tListP *L);
bool isEmptyListP(tListP L);
tPosP firstP(tListP L);
tPosP lastP(tListP L);
tPosP nextP(tPosP P, tListP L);
tPosP previousP(tPosP P, tListP L);
tItemP getDataP(tPosP P, tListP L);
tPosP findDataP(int I, tListP L);
tPosP findKey(int I, tListP L);
tPosP findFich(char *name, tListP L);
tPosP findDir(void * add,tListP L);
bool insertDataP(const tItemP i, tListP *L);
void deleteAtPosP(tPosP p,tListP *L);
void delListP(tListP *L);
#endif //PRACTICA_SO_LISTM_H
