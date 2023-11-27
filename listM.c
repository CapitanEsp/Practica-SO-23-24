/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es
            Antón Soto Ríos - anton.soto@udc.es**/

#include "listM.h"

bool createNodeM(tPosM *P){
    *P=malloc(sizeof(struct tNodeM));
    return *P!=MNULL;
}

void createEmptyListM(tListM *L){
    *L=MNULL;
}

bool isEmptyListM(tListM L){
    return L==MNULL;
}

tPosM firstM(tListM L){
    return L;
}

tPosM lastM(tListM L){
    tPosM p;
    for(p=L; p->next!=MNULL; p=p->next);
    return p;
}

tPosM nextM(tPosM P, tListM L){
    return P->next;
}

tPosM previousM(tPosM P, tListM L){
    tPosM p;
    if(P==L) p=MNULL;
    else for(p=L; p->next!=P; p=p->next);
    return p;
}

tPosM findDataM(int I, tListM L){
    tPosM p;
    tItemM i;

    if (isEmptyListM(L)) p=MNULL;
    else for(p=firstM(L);p!=MNULL;p= nextM(p,L)){
            i= getDataM(p,L);
            if(i.size==I) break;
        }
    return p;
}


tPosM findKey(int I, tListM L){
    tPosM p;
    tItemM i;

    if (isEmptyListM(L)) p=MNULL;
    else for(p=firstM(L);p!=MNULL;p= nextM(p,L)){
            i= getDataM(p,L);
            if(i.key==I) break;
        }
    return p;
}


tPosM findFich(char *name, tListM L){
    tPosM p;
    tItemM i;

    if (isEmptyListM(L)) p=MNULL;
    else for(p=firstM(L);p!=MNULL;p= nextM(p,L)){
            i= getDataM(p,L);
            if(strcmp(i.name,name)==0) break;
        }
    return p;
}

tPosM findDir(void * add,tListM L){
    tPosM p;
    tItemM i;

    if (isEmptyListM(L)) p=MNULL;
    else for(p=firstM(L);p!=MNULL;p= nextM(p,L)){
            i= getDataM(p,L);
            if(i.address==add) break;
        }
    return p;
}

bool insertDataM(const tItemM i, tListM *L){
    /*type = 0 -> malloc
      type = 1 -> shared
      type = 2 -> map*/

    tPosM q,p;
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

tItemM getDataM(tPosM p, tListM L){
    return p->data;
}

void deleteAtPosM(tPosM p, tListM *L) {
    tPosM q;
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

void delListM( tListM *L){
    tPosM p,q;
    p=*L;
    while(p!=MNULL){
        q=p->next;
        if(p->data.type==0)free(p->data.address);
        free(p);
        p=q;
    }
    *L=MNULL;
}