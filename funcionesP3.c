#include "funcionesP3.h"
#include "includes.h"
#include "funcionesP2.h"


//-------------------------------------------------------------------------------------------
//FUNCIONES PRINCIPALES (AARON HAGO LO QUE PUEDO)
//-------------------------------------------------------------------------------------------

void uid(char **command, int nargs) {
    if (nargs < 3) {
        printf("Credencial real: %d, (%s)\n", getuid(), getUser(getuid()));
        printf("Credencial efectiva: %d, (%s)\n", geteuid(), getUser(geteuid()));
    } else {
        if (strcmp(command[1], "-set") == 0) {
            uid_t newuid;
            if (strcmp(command[2], "-l") == 0) {
                if (nargs == 4) {
                    newuid = getMyuid(command[3]);
                    if (seteuid(newuid) != 0) {
                        perror("Usuario no existente: ");
                    }
                } else {
                    printf("Credencial real: %d, (%s)\n", getuid(), getUser(getuid()));
                    printf("Credencial efectiva: %d, (%s)\n", geteuid(), getUser(geteuid()));
                }
            } else {
                newuid = atoi(command[2]);
                if (seteuid(newuid) != 0) {
                    perror("Imposible cambiar credencial: ");
                }
            }
        }
    }
}

void showvar(char **command, int nargs, char **arg3) {
    if (nargs == 1) {
        enviroment(arg3, "arg3 main");
    } else {
        int posInEnviro = BuscarVariable(command[1], arg3);
        if (posInEnviro != -1) {
            printf("Con arg3 main %s(%p) @%p\n", arg3[posInEnviro], arg3[posInEnviro], arg3);
            printf("Con environ %s(%p) @%p\n", varEnviroment[posInEnviro], varEnviroment[posInEnviro], varEnviroment);
            printf("Con getenv %s(%p)\n", getenv(command[1]), getenv(command[1]));
        } else {
            printf("No ejecutado: %s\n", strerror(errno));
        }
    }
}

void changevar(char **command, int nargs, char **arg3) {
    if (nargs == 4) {
        if (strcmp(command[1], "-a") == 0) {
            if (CambiarVariable(command[2], command[3], arg3) == -1) {
                printf("Imposible cambiar variable: %s\n", strerror(errno));
            }
        } else if (strcmp(command[1], "-e") == 0) {
            if (CambiarVariable(command[2], command[3], varEnviroment) == -1) {
                printf("Imposible cambiar variable: %s\n", strerror(errno));
            }
        } else if (strcmp(command[1], "-p") == 0) {
            char newVar[500];
            strcpy(newVar, command[2]);
            strcat(newVar, "=");
            strcat(newVar, command[3]);
            if (putenv(newVar) != 0) {
                printf("Imposible cambiar variable: %s\n", strerror(errno));
            }
        } else {
            perror("Formato de parametros incorrecto");
        }
    } else {
        perror("Numero de parametros incorrecto");
    }
}

void subsvar(char **command, int nargs, char **arg3) {
    if (nargs == 5) {
        if (strcmp(command[1], "-a") == 0) {
            if (CambiarVariablebyAntonetiiii(command[2], command[3], command[4], arg3) == -1) {
                printf("Imposible cambiar variable: %s\n", strerror(errno));
            }
        } else if (strcmp(command[1], "-e") == 0) {
            if (CambiarVariablebyAntonetiiii(command[2], command[3], command[4], varEnviroment) == -1) {
                printf("Imposible cambiar variable: %s\n", strerror(errno));
            }
        } else {
            perror("Formato de parametros incorrecto");
        }
    } else {
        perror("Numero de parametros incorrecto");
    }
}

void showenv(char **command, int nargs, char **arg3) {
    if (nargs < 3) {
        if (nargs == 1) {
            enviroment(arg3, "arg3 main");
        } else {
            if (strcmp(command[1], "-environ") == 0) {
                enviroment(varEnviroment, "Enviroment");
            }
            if (strcmp(command[1], "-addr") == 0) {
                printf("environ:   %p (almacenado en %p)\n", varEnviroment, &varEnviroment);
                printf("main arg3: %p (almacenado en %p)\n", arg3, &arg3);
            }
        }
    } else {
        perror("Numero de parametros incorrecto");
    }
}

void my_Fork(char **command, int nargs) {
    if (nargs == 1) {
        int pidHijo;
        if ((pidHijo = fork()) == 0) {
            printf("Ejecutando proceso %d\n", getpid());
        } else if (pidHijo != -1) {
            waitpid(pidHijo, PNULL, 0);
        }
    } else {
        perror("Numero de parametros incorrecto");
    }
}

char *Ejecutable(char *s) {
    char path[PATH_MAX];
    static char aux2[PATH_MAX];
    struct stat st;
    char *p;
    if (s == NULL || (p = getenv("PATH")) == NULL)
        return s;
    if (s[0] == '/' || !strncmp(s, "./", 2) || !strncmp(s, "../", 3))
        return s;       //is an absolute pathname
    strncpy(path, p, PATH_MAX);
    for (p = strtok(path, ":"); p != NULL; p = strtok(NULL, ":")) {
        sprintf(aux2, "%s/%s", p, s);
        if (lstat(aux2, &st) != -1)
            return aux2;
    }
    return s;
}

void exec(char **args, int nargs) { //Execv, execve, execl
    int i;
    char *arguments[nargs];
    char comando[100];

    strcpy(comando, Ejecutable(args[1]));
    for (i = 1; i < nargs; i++) {
        arguments[i - 1] = strdup(args[i]);
    }
    arguments[nargs - 1] = NULL;
    execv(comando, arguments);
}

//kill -s TERM pid     o cntrl z

void jobs(char **command, int nargs, tListP L) {
    tPosP p;
    tItemP data;
    int aux;
    pid_t pid;
    for (p = L; p != PNULL; p = nextP(p, L)) {
        data = getDataP(p, L);
        if ((strcmp(data.nsignal, "TERMINADO") != 0) && (strcmp(data.nsignal, "SENALADO") != 0)) {
            data.prio = getpriority(data.prio, data.pid);
            aux = waitpid(data.pid, &pid, WNOHANG | WCONTINUED | WUNTRACED);
            if (aux != -1) {
                if (aux == data.pid) {
                    if (WIFSIGNALED(pid)) {
                        strcpy(data.nsignal, "SENALADO");
                        data.signal = WTERMSIG(pid);
                    } else {
                        if (WIFEXITED(pid)) {
                            strcpy(data.nsignal, "TERMINADO");
                            data.signal = WEXITSTATUS(pid);
                        } else if (WIFSTOPPED(pid)) {
                            strcpy(data.nsignal, "PARADO");
                            data.signal = WSTOPSIG(pid);
                        }
                    }
                }
            }
            p->data = data;
        }
        printf("%d\t%s p=%d %s  %s", data.pid, data.user, data.prio, data.launch, /*data.sig.name, data.sig.num,*/
               data.comandName);
        printf("%d %s\n", data.signal, data.nsignal);
    }
}

void deljobs(char **command, int nargs, tListP *L) {
    if (nargs == 2) {
        tPosP p;
        tItemP i;
        if (strcmp(command[1], "-term") == 0) {
            for (p = *L; p != PNULL; p = nextP(p, *L)) {
                i = getDataP(p, *L);
                if (strcmp("TERMINADO", i.nsignal) == 0) {
                    deleteAtPosP(p, L);
                }
            }
        }
        if (strcmp(command[1], "-sig") == 0) {
            for (p = *L; p != PNULL; p = nextP(p, *L)) {
                i = getDataP(p, *L);
                if (strcmp("SENALADO", i.nsignal) == 0) {
                    deleteAtPosP(p, L);
                }
            }
        }
    } else {
        perror("Numero de parametros incorrecto");
    }
}

void job(char **command, int nargs, tListP *L) {
    if (nargs < 2) {
        jobs(command, nargs, *L);
    } else {
        if (nargs > 3) {
            perror("Numero de parametros incorrecto");
        } else {
            tPosP p;
            tItemP i;
            if (nargs == 2) {
                if (atoi(command[1]) != getpid()) {
                    p = findDataP(atoi(command[1]), *L);
                    i = getDataP(p, *L);
                    printf("%d\t%s p=%d %s %s (%d) %s", i.pid, i.user, i.prio, i.launch, i.nsignal, i.signal,
                           i.comandName);
                } else {
                    jobs(command, nargs, *L);
                }
            } else {
                if (strcmp(command[1], "-fg") == 0) {
                    p = findDataP(atoi(command[1]), *L);
                    i = getDataP(p, *L);
                    if (waitpid(atoi(command[2]), &i.signal, 0) != -1) {
                        if (WIFEXITED(i.signal)) {
                            printf("Proceso %d terminado normalmente. Valor devuelto: %d\n", atoi(command[1]),
                                   WEXITSTATUS(i.signal));
                            //i.sig.name = "TERMINADO";
                        } else if (WIFSIGNALED(i.signal)) {
                            printf("Proceso %d terminado por la señal %d", atoi(command[1]), WTERMSIG(i.signal));
                            //i.sig.name = "SENALADO";
                        }
                    }
                }
            }
        }
    }
}

void Random(char **args, int nargs, tListP *L) {
    pid_t pid;
    pid = fork(); // Crea un hijo
    bool background= false;
    if(args[nargs-1][0]=='&'){
        background = true;
        args[nargs-1] = NULL;
    }
    if (pid == 0) {
        execv(Ejecutable(args[0]), args);
    } // Ejecuta el comando en background
    else if (pid > 0 && background) {
        char comand[500];
        tItemP i;
        getHora(i.launch);
        for (int j = 0; j < nargs - 1; j++) {
            strcat(comand, args[j]);
            strcat(comand, " ");
        }
        initItem(&i, pid, getpriority(PRIO_PROCESS, pid), getUser(getuid()));
        i.comandName = strdup(comand);
        insertDataP(i, L);
    } else if (pid > 0 && !background) waitpid(pid, NULL, 0); //Ejecuciones en foreground
}


//-------------------------------------------------------------------------------------------
//FUNCIONES AUXILIARES
//-------------------------------------------------------------------------------------------

//Aaron eres el fucking MVP
char *getUser(uid_t uid) {
    struct passwd *contraseñaNombre;
    contraseñaNombre = getpwuid(uid);
    return contraseñaNombre->pw_name;
}

uid_t getMyuid(char *name) {
    struct passwd *contraseñaNombre;
    contraseñaNombre = getpwnam(name);
    return contraseñaNombre->pw_uid;
}

void enviroment(char **varEnviroment, char *enviromentName) {
    int p;
    for (p = 0; varEnviroment[p] != NULL; p++) {
        printf("%p -> %s [%d] = (%p) %s\n", &varEnviroment[p], enviromentName, p, varEnviroment[p], varEnviroment[p]);
    }
}

int CambiarVariablebyAntonetiiii(char *var1, char *var2, char *valor, char *e[]) {
    /*cambia una variable en el entorno que se le pasa como parámetro*/
    /*lo hace directamente, no usa putenv*/
    int pos;
    char *aux;

    if ((pos = BuscarVariable(var1, e)) == -1)
        return (-1);

    if ((aux = (char *) malloc(strlen(var2) + strlen(valor) + 2)) == NULL)
        return -1;
    strcpy(aux, var2);
    strcat(aux, "=");
    strcat(aux, valor);
    e[pos] = aux;
    return (pos);
}
//-------------------------------------------------------------------------------------------
//CODIGO DE AYUDA
//-------------------------------------------------------------------------------------------

void Cmd_fork(char *tr[]) {
    pid_t pid;

    if ((pid = fork()) == 0) {
/*		VaciarListaProcesos(&LP); Depende de la implementación de cada uno*/
        printf("ejecutando proceso %d\n", getpid());
    } else if (pid != -1)
        waitpid(pid, NULL, 0);
}

int BuscarVariable(char *var, char *e[])  /*busca una variable en el entorno que se le pasa como parámetro*/{
    int pos = 0;
    char aux[500];

    strcpy(aux, var);
    strcat(aux, "=");

    while (e[pos] != NULL)
        if (!strncmp(e[pos], aux, strlen(aux)))
            return (pos);
        else
            pos++;
    errno = ENOENT;   /*no hay tal variable*/
    return (-1);
}


int CambiarVariable(char *var, char *valor, char *e[]) {
    /*cambia una variable en el entorno que se le pasa como parámetro*/
    /*lo hace directamente, no usa putenv*/
    int pos;
    char *aux;

    if ((pos = BuscarVariable(var, e)) == -1)
        return (-1);

    if ((aux = (char *) malloc(strlen(var) + strlen(valor) + 2)) == NULL)
        return -1;
    strcpy(aux, var);
    strcat(aux, "=");
    strcat(aux, valor);
    e[pos] = aux;
    return (pos);
}

int ValorSenal(char *sen) {  /*devuelve el numero de senial a partir del nombre*/

    int i;
    for (i = 0; sigstrnum[i].name != NULL; i++)
        if (!strcmp(sen, sigstrnum[i].name))
            return sigstrnum[i].num;
    return -1;
}


char *NombreSenal(int sen) {  /*devuelve el nombre senal a partir de la senal*/
    /* para sitios donde no hay sig2str*/
    int i;
    for (i = 0; sigstrnum[i].name != NULL; i++)
        if (sen == sigstrnum[i].num)
            return sigstrnum[i].name;
    return ("SIGUNKNOWN");
}

