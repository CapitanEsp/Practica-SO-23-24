#ifndef PRACTICA_SO_LISTP_H
#define PRACTICA_SO_LISTP_H
#define PNULL NULL
#include "includes.h"

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


typedef struct {
    int pid, prio;
    char user[100];
    char comandName[500];
    char launch[100];
    int signal;
    char nsignal[50];
}tItemP;

typedef struct tNodeP* tPosP;
struct tNodeP{
    tItemP data;
    tPosP next;
};
typedef tPosP tListP;

void initItem(tItemP *i, int pid, int prio, char* user);
void createEmptyListP(tListP *L);
bool isEmptyListP(tListP L);
tPosP firstP(tListP L);
tPosP lastP(tListP L);
tPosP nextP(tPosP P, tListP L);
tPosP previousP(tPosP P, tListP L);
tItemP getDataP(tPosP P, tListP L);
tPosP findDataP(int I, tListP L);
bool insertDataP(const tItemP i, tListP *L);
void deleteAtPosP(tPosP p,tListP *L);
void delListP(tListP *L);
#endif //PRACTICA_SO_LISTM_H