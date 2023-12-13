#ifndef PRACTICA_SO_LISTP_H
#define PRACTICA_SO_LISTP_H
#define PNULL NULL
#include "includes.h"



typedef struct {
    int pid, prio;
    char user[100];
    char comandName[500];
    char launch[100];
    int signal;
    char nsignal[50];
}tItemP;

typedef struct tNodeP* tPosP;
struct tNodeP{
    tItemP data;
    tPosP next;
};
typedef tPosP tListP;

void initItem(tItemP *i, int pid, int prio, char* user);
void createEmptyListP(tListP *L);
bool isEmptyListP(tListP L);
tPosP firstP(tListP L);
tPosP lastP(tListP L);
tPosP nextP(tPosP P, tListP L);
tPosP previousP(tPosP P, tListP L);
tItemP getDataP(tPosP P, tListP L);
tPosP findDataP(int I, tListP L);
bool insertDataP(const tItemP i, tListP *L);
void deleteAtPosP(tPosP p,tListP *L);
void delListP(tListP *L);
#endif //PRACTICA_SO_LISTM_H