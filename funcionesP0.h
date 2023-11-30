/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es
            Antón Soto Ríos - anton.soto@udc.es**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/utsname.h>
#include "TADLista.h"
#include "listF.h"
#include "listM.h"
#include "listP.h"

#define TCOM PATH_MAX
#define MAX 10


//Funciones para tratar los comandos
int partir(char *inCommand, char* outCommand[]);
int processCommand(char* command[], int aux, tList* L,tListF *F,tListM *M, tListP *P, char ** arg3);

//Funciones de los comandos en si
void autores(char* Arg[], int aux);
void pid(char* Arg[], int aux);
void carpeta(char* Arg[], int aux);
void fecha();
void hora();
void hist(char* Arg[], int aux, tList *L);
void comandoN(char **comand, tList L, tListF F,tListM M, tListP P, char** arg3);
void infosis();
void ayuda(char* Arg[], int aux);
void Cmd_open(char * Arg[],tListF *L);
void Cmd_close(char * Arg[],tListF *L);
void Cmd_dup(char * Arg[],tListF *L);
void listopen(tListF L);

//Sub funciones del hist
void permisosChar(const int mode);
int quitarGuion(char* s);