/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es
            Antón Soto Ríos - anton.soto@udc.es**/

#ifndef P0_LISTF_H
#define P0_LISTF_H
#include "includes.h"

#define LNULL NULL
typedef struct {
    int df,mode;
    char name[200];
}tItemF;
typedef struct tNodeF* tPosF;
struct tNodeF{
    tItemF data;
    tPosF next;
};
typedef tPosF tListF;

void createEmptyListF(tListF *L);
bool isEmptyListF(tListF L);
tPosF firstF(tListF L);
tPosF lastF(tListF L);
tPosF nextF(tPosF P, tListF L);
tPosF previousF(tPosF P, tListF L);
tItemF getDataF(tPosF P, tListF L);
tPosF findDataF(int I, tListF L);
bool insertDataF(int fd, int mode,char *name, tListF *L);
void deleteAtPosF(tPosF p,tListF *L);
void delListF(tListF *L);
#endif