#ifndef P3_SO_24_LISTP_H
#define P3_SO_24_LISTP_H

/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es
            Antón Soto Ríos - anton.soto@udc.es**/

#include "listP.h"

void initItem(tItemP *i, int pid,char * launch, char * status) {
    i->pid=pid;
    strcpy(i->launch, launch);
    strcpy(i->status, status);
}

bool createNodeM(tPosP *P){
    *P=malloc(sizeof(struct tNodeP));
    return *P!=MNULL;
}

void createEmptyListM(tListP *L){
    *L=MNULL;
}

bool isEmptyListM(tListP L){
    return L==MNULL;
}

tPosP firstM(tListP L){
    return L;
}

tPosP lastM(tListP L){
    tPosP p;
    for(p=L; p->next!=MNULL; p=p->next);
    return p;
}

tPosP nextM(tPosP P, tListP L){
    return P->next;
}

tPosP previousM(tPosP P, tListP L){
    tPosP p;
    if(P==L) p=MNULL;
    else for(p=L; p->next!=P; p=p->next);
    return p;
}

tPosP findDataM(int I, tListP L){
    tPosP p;
    tItemP i;

    if (isEmptyListM(L)) p=MNULL;
    else for(p=firstM(L);p!=MNULL;p= nextM(p,L)){
            i= getDataM(p,L);
            if(i.pid==I) break;
        }
    return p;
}

bool insertDataM(const tItemP i, tListP *L){

    tPosP q,p;
    bool aux= 1;

    if(!createNodeM(&q)) aux=0;
    else{
        q->data=i;
        q->next=MNULL;
        if(*L==MNULL)*L=q;
        else{
            for (p = *L; p->next != MNULL; p = p->next);
            p->next = q;
        }
    }
    return aux;
}

tItemP getDataM(tPosP p, tListP L){
    return p->data;
}

void deleteAtPosM(tPosP p, tListP *L) {
    tPosP q;
    if (p == *L) {//Caso de 1 solo elemento
        *L = nextM(p, *L);//El primer elemento es el siguiente de L
    } else {//Cualquier otro caso
        if (p == lastM(*L)) {//Caso última posición
            q = previousM(lastM(*L), *L); //Selecciono el penúltimo
            q->next = MNULL;
        } else {//Caso elemento del medio
            q = nextM(p, *L);
            p->data = getDataM(q, *L);
            p->next = nextM(q, *L);
            p = q;
        }
    }
    free(p);
}

void delListM( tListP *L){
    tPosP p,q;
    p=*L;
    while(p!=MNULL){
        q=p->next;
        free(p);
        p=q;
    }
    *L=MNULL;
}

#endif //P3_SO_24_LISTP_H
