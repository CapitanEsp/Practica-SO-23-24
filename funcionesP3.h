#ifndef P3_SO_24_FUNCIONESP3_H
#define P3_SO_24_FUNCIONESP3_H

#include "includes.h"

#include "listP.h"

extern char** varEnviroment;

void uid(char ** command,int nargs);
void showvar(char ** command, int nargs, char ** arg3);
void changevar(char ** command,int nargs, char** arg3);
void subsvar(char ** command,int nargs, char** arg3);
void showenv(char ** command,int nargs, char** arg3);
void my_Fork(char ** command,int nargs);
void exec(char ** args,int nargs);
void jobs(char ** command,int nargs, tListP L);
void deljobs(char ** command,int nargs, tListP *L);
void job(char ** command, int nargs, tListP *L);
void Random(char ** command,int nargs);

//Func aux
char * getUser(uid_t uid);
uid_t getMyuid(char * name);
void enviroment(char **varEnviroment, char *enviromentName);
int CambiarVariablebyAntonetiiii(char * var1, char *var2, char * valor, char *e[]);

//Codigo de ayuda
int BuscarVariable (char * var, char *e[]);
int CambiarVariable(char * var, char * valor, char *e[]);

#endif //P3_SO_24_FUNCIONESP3_H
