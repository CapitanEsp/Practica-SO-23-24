/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es   -Grupo 2.3
            Antón Soto Ríos - anton.soto@udc.es     -Grupo 2.1 **/

#include "TADLista.h"

//Funciones de la lista

bool createNode(tPosL *P){
    *P=malloc(sizeof(struct tNode));
    return *P!=LNULL;
}

void createEmptyList(tList *L){
    *L=LNULL;
}

bool isEmptyList(tList L){
    return L==LNULL;
}

tPosL first(tList L){
    return L;
}

tPosL last(tList L){
    tPosL p;
    for(p=L; p->next!=LNULL; p=p->next);
    return p;
}

tPosL next(tPosL P, tList L){
    return P->next;
}

tPosL previous(tPosL P, tList L){
    tPosL p;
    if(P==L) p=LNULL;
    else for(p=L; p->next!=P; p=p->next);
    return p;
}

tPosL findItem(int I, tList L){
        tPosL p=L;
        int i;

    if (isEmptyList(L)) p=LNULL;
    else for(i=0; p!=NULL && i!=I ; i++) p=p->next;
    return p;   
}

bool insertItem(char* I,tList *L){
    tPosL q,p;
    bool aux= false;

    if(!createNode(&q)) aux=true;
    else{
        strcpy(q->comand, I);
        q->next=LNULL;
        if(*L==LNULL)*L=q;
        else{
            for (p = *L; p->next != LNULL; p = p->next);
            p->next = q;
        }
    }
    return aux;
}

char* getItem(tPosL P, tList L){
    return P->comand;
}

void delHistoric( tList *L){
    tPosL p,q;
    p=*L;
    while(p!=LNULL){
        q=p->next;
        free(p);
        p=q;
    }
    *L=LNULL;
}