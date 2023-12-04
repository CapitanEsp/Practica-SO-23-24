#ifndef P3_SO_24_LISTP_H
#define P3_SO_24_LISTP_H

/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es
            Antón Soto Ríos - anton.soto@udc.es**/

#include "listP.h"

void initItem(tItemP *i, int pid,char * launch, int status, int prio, char* user){
    i->pid = pid;
    strcpy(i->launch, launch);
    i->prio = prio;
    i->sig.num = status;
    strcpy(i->sig.name, sigstrnum[i->sig.num].name);
    strcpy(i->user, user);

}

bool createNodeP(tPosP *P){
    *P=malloc(sizeof(struct tNodeP));
    return *P!=PNULL;
}

void createEmptyListP(tListP *L){
    *L=PNULL;
}

bool isEmptyListP(tListP L){
    return L==PNULL;
}

tPosP firstP(tListP L){
    return L;
}

tPosP lastP(tListP L){
    tPosP p;
    for(p=L; p->next!=PNULL; p=p->next);
    return p;
}

tPosP nextP(tPosP P, tListP L){
    return P->next;
}

tPosP previousP(tPosP P, tListP L){
    tPosP p;
    if(P==L) p=PNULL;
    else for(p=L; p->next!=P; p=p->next);
    return p;
}

tPosP findDataP(int I, tListP L){
    tPosP p;
    tItemP i;

    if (isEmptyListP(L)) p=PNULL;
    else for(p=firstP(L);p!=PNULL;p= nextP(p,L)){
            i= getDataP(p,L);
            if(i.pid==I) break;
        }
    return p;
}

bool insertDataP(const tItemP i, tListP *L){

    tPosP q,p;
    bool aux= 1;

    if(!createNodeP(&q)) aux=0;
    else{
        q->data=i;
        q->next=PNULL;
        if(*L==PNULL)*L=q;
        else{
            for (p = *L; p->next != PNULL; p = p->next);
            p->next = q;
        }
    }
    return aux;
}

tItemP getDataP(tPosP p, tListP L){
    return p->data;
}

void deleteAtPosP(tPosP p, tListP *L) {
    tPosP q;
    if (p == *L) {//Caso de 1 solo elemento
        *L = nextP(p, *L);//El primer elemento es el siguiente de L
    } else {//Cualquier otro caso
        if (p == lastP(*L)) {//Caso última posición
            q = previousP(lastP(*L), *L); //Selecciono el penúltimo
            q->next = PNULL;
        } else {//Caso elemento del medio
            q = nextP(p, *L);
            p->data = getDataP(q, *L);
            p->next = nextP(q, *L);
            p = q;
        }
    }
    free(p);
}

void delListP(tListP *L){
    tPosP p,q;
    p=*L;
    while(p!=PNULL){
        q=p->next;
        free(p);
        p=q;
    }
    *L=PNULL;
}

#endif //P3_SO_24_LISTP_H
