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
void exec(char **args, int nargs);
void jobs(char ** command,int nargs, tListP *L);
void deljobs(char ** command,int nargs, tListP *L);
void job(char ** command, int nargs, tListP *L);
void Random(char **args, int nargs, tListP *L);

//Func aux
char * getUser(uid_t uid);
uid_t getMyuid(char * name);
void enviroment(char **varEnviroment, char *enviromentName);
int CambiarVariablebyAntonetiiii(char * var1, char *var2, char * valor, char *e[]);

//Codigo de ayuda
int BuscarVariable (char * var, char *e[]);
int CambiarVariable(char * var, char * valor, char *e[]);
char *NombreSenal(int sen);

struct SEN {
    char * name;
    int num;
};

static struct SEN sigstrnum[]={
        {"HUP", SIGHUP},
        {"INT", SIGINT},
        {"QUIT", SIGQUIT},
        {"ILL", SIGILL},
        {"TRAP", SIGTRAP},
        {"ABRT", SIGABRT},
        {"IOT", SIGIOT},
        {"BUS", SIGBUS},
        {"FPE", SIGFPE},
        {"KILL", SIGKILL},
        {"USR1", SIGUSR1},
        {"SEGV", SIGSEGV},
        {"USR2", SIGUSR2},
        {"PIPE", SIGPIPE},
        {"ALRM", SIGALRM},
        {"TERM", SIGTERM},
        {"CHLD", SIGCHLD},
        {"CONT", SIGCONT},
        {"STOP", SIGSTOP},
        {"TSTP", SIGTSTP},
        {"TTIN", SIGTTIN},
        {"TTOU", SIGTTOU},
        {"URG", SIGURG},
        {"XCPU", SIGXCPU},
        {"XFSZ", SIGXFSZ},
        {"VTALRM", SIGVTALRM},
        {"PROF", SIGPROF},
        {"WINCH", SIGWINCH},
        {"IO", SIGIO},
        {"SYS", SIGSYS},

/*senales que no hay en todas partes*/
#ifdef SIGPOLL
        {"POLL", SIGPOLL},
#endif
#ifdef SIGPWR
        {"PWR", SIGPWR},
#endif
#ifdef SIGEMT
        {"EMT", SIGEMT},
#endif
#ifdef SIGINFO
        {"INFO", SIGINFO},
#endif
#ifdef SIGSTKFLT
        {"STKFLT", SIGSTKFLT},
#endif
#ifdef SIGCLD
        {"CLD", SIGCLD},
#endif
#ifdef SIGLOST
        {"LOST", SIGLOST},
#endif
#ifdef SIGCANCEL
        {"CANCEL", SIGCANCEL},
#endif
#ifdef SIGTHAW
        {"THAW", SIGTHAW},
#endif
#ifdef SIGFREEZE
        {"FREEZE", SIGFREEZE},
#endif
#ifdef SIGLWP
        {"LWP", SIGLWP},
#endif
#ifdef SIGWAITING
        {"WAITING", SIGWAITING},
#endif
        {NULL,-1},
};    /*fin array sigstrnum */


#endif //P3_SO_24_FUNCIONESP3_H