/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es
            Antón Soto Ríos - anton.soto@udc.es**/

#include "listF.h"

bool createNodeF(tPosF *P){
    *P=malloc(sizeof(struct tNodeF));
    return *P!=LNULL;
}

void createEmptyListF(tListF *L){
    *L=LNULL;
}

bool isEmptyListF(tListF L){
    return L==LNULL;
}

tPosF firstF(tListF L){
    return L;
}

tPosF lastF(tListF L){
    tPosF p;
    for(p=L; p->next!=LNULL; p=p->next);
    return p;
}

tPosF nextF(tPosF P, tListF L){
    return P->next;
}

tPosF previousF(tPosF P, tListF L){
    tPosF p;
    if(P==L) p=LNULL;
    else for(p=L; p->next!=P; p=p->next);
    return p;
}

tPosF findDataF(int I, tListF L){
    tPosF p;
    tItemF i;

    if (isEmptyListF(L)) p=LNULL;
    else for(p=firstF(L);p!=NULL;p= nextF(p,L)){
        i= getDataF(p,L);
        if(i.df==I) break;
    }
    return p;
}

bool insertDataF(int df , int mode ,char* name, tListF *L){
    tPosF q,p;
    bool aux= 1;

    if(!createNodeF(&q)) aux=0;
    else{
        q->data.df=df;
        q->data.mode=mode;
        strcpy(q->data.name, name);
        q->next=LNULL;
        if(*L==LNULL)*L=q;
        else{
            for (p = *L; p->next != LNULL; p = p->next);
            p->next = q;
        }
    }
    return aux;
}

tItemF getDataF(tPosF p, tListF L){
    return p->data;
}

void deleteAtPosF(tPosF p, tListF *L) {
    tPosF q;
    if (p == *L) {//Caso de 1 solo elemento
        *L = nextF(p, *L);//El primer elemento es el siguiente de L
    } else {//Cualquier otro caso
        if (p == lastF(*L)) {//Caso última posición
            q = previousF(lastF(*L), *L); //Selecciono el penúltimo
            q->next = LNULL;
        } else {//Caso elemento del medio
            q = nextF(p, *L);
            p->data = getDataF(q, *L);
            p->next = nextF(q, *L);
            p = q;
        }
    }
    free(p);
}

void delListF( tListF *L){
    tPosF p,q;

    p=*L;
    while(p!=LNULL){
        q=p->next;
        free(p);
        p=q;
    }
    *L=LNULL;
}