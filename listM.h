#ifndef PRACTICA_SO_LISTM_H
#define PRACTICA_SO_LISTM_H
#define MNULL NULL
#include "includes.h"

typedef struct {
    int size,type,df;
    void * address;
    char reservation[100], name[200];
    int key;
}tItemM;
typedef struct tNodeM* tPosM;
struct tNodeM{
    tItemM data;
    tPosM next;
};
typedef tPosM tListM;

void createEmptyListM(tListM *L);
bool isEmptyListM(tListM L);
tPosM firstM(tListM L);
tPosM lastM(tListM L);
tPosM nextM(tPosM P, tListM L);
tPosM previousM(tPosM P, tListM L);
tItemM getDataM(tPosM P, tListM L);
tPosM findDataM(int I, tListM L);
tPosM findKey(int I, tListM L);
tPosM findFich(char *name, tListM L);
tPosM findDir(void * add,tListM L);
bool insertDataM(const tItemM i, tListM *L);
void deleteAtPosM(tPosM p,tListM *L);
void delListM(tListM *L);
#endif //PRACTICA_SO_LISTM_H
