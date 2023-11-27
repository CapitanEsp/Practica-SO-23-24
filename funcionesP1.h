#ifndef P0_FUNCIONESP1_H
#define P0_FUNCIONESP1_H
#include "includes.h"

//Funciones P1
void myCreate(char ** command,int aux);
void myStats(char ** command, int aux);
void myDelete(char **command, int aux);
void myList(char ** command, int aux);
void myDelTree(char** command, int aux);

//Funciones auxiliares
void print_Stat(bool Long,bool Link, bool Acc,struct stat info, char * name);
void listrec(char * command, bool Long, bool Link, bool Acc, bool recA, bool recB, bool hid);
void aux_Deltree(char * name);

//Funciones código ayuda
char LetraTF (mode_t m);
char * ConvierteModo(mode_t m, char * permisos);


#endif //P0_FUNCIONESP1_H
