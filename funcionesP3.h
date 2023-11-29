#ifndef P3_SO_24_FUNCIONESP3_H
#define P3_SO_24_FUNCIONESP3_H

#include "includes.h"

#include "listP.h"

void uid(char ** command,int nargs);
void showvar(char ** command);
void changevar(char ** command,int nargs);
void subsvar(char ** command,int nargs);
void showenv(char ** command,int nargs);
void my_Fork(char ** command,int nargs);
//void exec(char ** args,int nargs);
void jobs(char ** command,int nargs);
void deljobs(char ** command,int nargs);
void job(char ** command,int nargs);
void Random(char ** command,int nargs);

#endif //P3_SO_24_FUNCIONESP3_H
