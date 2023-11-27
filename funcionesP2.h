#ifndef PRACTICA_SO_FUNCIONESP2_H
#define PRACTICA_SO_FUNCIONESP2_H
#include "includes.h"
#include "listM.h"
#define TAMANO 2048

void myMalloc(char ** command, int nargs,tListM *L);
void myShared(char ** command, int nargs,tListM *L);
void myMmap(char ** command, int nargs,tListM *L);
void myRead(char ** command);
void myWrite(char ** command, int nargs,tListM L);
void Memdump(char ** command, int nargs,tListM L);
void Memfill(char ** command, int nargs,tListM L);
void mem(char ** command, int nargs,tListM L);
void Recursive(char **command,int nargs);

//Funciones auxiliares
void * cadtop(char * add);
void ImprimirListaM(int type,tListM L);
void getHora(char * hora);
void createItem(tItemM *i,void *p,int size,int type);
void ImprimirListaM(int modo, tListM L);
void SharedFree(char ** command, tListM * L);

//Codigo ayuda
void Recursiva (int n);
void LlenarMemoria(void *p, size_t cont, unsigned char byte);
void * ObtenerMemoriaShmget (key_t clave, size_t tam,tListM *L);
void SharedCreate (char *args[],tListM *L);
void * MapearFichero (char * fichero, int protection,tListM* L);
void CmdMmap(char *arg[],tListM *L);
void SharedDelkey (char *args[],tListM *L);
ssize_t EscribirFichero (char *f, void *p, size_t cont,int overwrite);
ssize_t LeerFichero (char *f, void *p, size_t cont);
void Do_MemPmap(void);

#endif //PRACTICA_SO_FUNCIONESP2_H
