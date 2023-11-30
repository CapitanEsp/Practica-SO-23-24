#include "funcionesP3.h"

extern char **varEnviroment;

//-------------------------------------------------------------------------------------------
//FUNCIONES PRINCIPALES (AARON HAGO LO QUE PUEDO)
//-------------------------------------------------------------------------------------------

void uid(char **command, int nargs){
    if(nargs < 3){
        printf("Credencial real: %d, (%s)\n", getuid(), getUser(getuid()));
        printf("Credencial efectiva: %d, (%s)\n", geteuid(), getUser(geteuid()));
    }else{
        if(strcmp(command[1], "-set") == 0){
            uid_t newuid;
            if(strcmp(command[2], "-l") == 0){
                if(nargs == 4){
                    newuid = getMyuid(command[3]);
                    if(seteuid(newuid) != 0){
                        perror("Usuario no existente: ");
                    }
                }else{
                    printf("Credencial real: %d, (%s)\n", getuid(), getUser(getuid()));
                    printf("Credencial efectiva: %d, (%s)\n", geteuid(), getUser(geteuid()));                    
                }
            }else{
                newuid = atoi(command[2]);
                if(seteuid(newuid) != 0){
                    perror("Imposible cambiar credencial: ");
                }                
            }
        }
    }
}

void showvar(char ** command, int nargs, char ** arg3){
    if(nargs == 1){
        enviroment(arg3, "arg3 main");
    }else{
        int posInEnviro = BuscarVariable(command[1], arg3);
        if(varPos != -1) {
            printf("Con arg3 main %s(%p) @%p\n", arg3[posInEnviro], arg3[posInEnviro], arg3);
            printf("Con environ %s(%p) @%p\n", varEnviroment[posInEnviro], varEnviroment[posInEnviro], varEnviroment);
            printf("Con getenv %s(%p)\n", getenv(command[1]), getenv(command[1]));
        }
        else{
            printf("No ejecutado: %s\n", strerror(errno));
        }
    }
}

void changevar(char ** command, int nargs){
    if(nargs == 4){
        if(nargs > 4 || nargs < 3){
            perror("Numero de parametros incorrecto");
        }
        if(strcmp(command[1], "-a") == 0){
            //Hacer codigo
        }
        if(strcmp(command[1], "-e") == 0){
            //Hacer codigo
        }
        if(strcmp(command[1], "-p") == 0){
            //Hacer codigo
        }
    }else{
        perror("Numero de parametros incorrecto");
    }
}

void subsvar(char ** command,int nargs){
    if(nargs == 4){
        //Hacer codigo
    }else{
        if(nargs > 5 || nargs < 4){
            perror("Numero de parametros incorrecto");
        }
        if(strcmp(command[1], "-a") == 0){
            //Hacer codigo
        }
        if(strcmp(command[1], "-e") == 0){
            //Hacer codigo
        }                
    }
}

void showenv(char ** command,int nargs, char** arg3){
    if(nargs < 3){
        if(nargs == 1){
            enviroment(arg3, "arg3 main");
        }else{
            if(strcmp(command[1], "-environ") == 0){
                enviroment(varEnviroment, "Enviroment");
            }
            if(strcmp(command[1], "-addr") == 0){
                printf("environ:   %p (almacenado en %p)\n", varEnviroment, &varEnviroment);
                printf("main arg3: %p (almacenado en %p)\n", arg3, &arg3);
            }
        }
    }else{
        perror("Numero de parametros incorrecto"); 
    }
}

void my_Fork(char ** command,int nargs){
    if(nargs == 1){
        int pidHijo;
        if((pidHijo = fork()) == 0){
            printf("Ejecutando proceso %d\n", getpid());
        }
        else if (pidHijo!=-1){
            waitpid(pidHijo, PNULL, 0);
        }
    }else{
        perror("Numero de parametros incorrecto"); 
    }
}

//void exec(char ** args,int nargs); //Acabo de ver el shell de referencia y me quede como estaba o peor


void jobs(char ** command,int nargs, tListP L){
    tPosP p;
    tItemP data;
    for(p = L; p != PNULL; p = nextP(p, L)){
        data = getDataP(p, L);
        data.prio = getpriority(data.prio, data.pid);
        data.sig.num = waitpid(data.pid, PNULL, 0);
        if(waitpid(data.pid, &data.sig.num, WNOHANG | WUNTRACED | WCONTINUED) == data.pid){
            if (WIFEXITED(data.sig.num)) {
                strcpy(data.sig.name, "TERMINADO");
            } else if (WIFSIGNALED(data.sig.num)) {
                strcpy(data.sig.name, "SENALADO");
            } else if (WIFSTOPPED(data.sig.num)) {
                strcpy(data.sig.name, "STOPPED");
            } else if (WIFCONTINUED(data.sig.num))
                strcpy(data.sig.name, "ACTIVO");
        }
        printf("%d\t%s p=%d %s %s (%d) %s", data.pid, data.user, data.prio, data.launch, data.sig.name, data.sig.num, data.comandName);
    }
}

void deljobs(char ** command, int nargs, tListP *L){
    if(nargs == 2){
        tPosP p;
        tItemP i;
        if(strcmp(command[1], "-term") == 0){
            for(p = *L; p != PNULL; p = nextP(p, *L)){
                i = getDataP(p, *L);
                if(strcmp("TERMINADO", i.sig.name) == 0){
                    deleteAtPosP(p, L);
                }
            }
        }
        if(strcmp(command[1], "-sig") == 0){
            for(p = *L; p != PNULL; p = nextP(p, *L)){
                i = getDataP(p, *L);
                if(strcmp("SENALADO", i.sig.name) == 0){
                    deleteAtPosP(p, L);
                }
            }
        }     
    }else{
        perror("Numero de parametros incorrecto"); 
    }
}

void job(char ** command, int nargs, tListP *L){
    if(nargs < 2){
        jobs(command, nargs, *L);
    }else{
        if(nargs > 3){
            perror("Numero de parametros incorrecto");
        }else{
            tPosP p;
            tItemP i;
            if(nargs == 2){
                p = findDataP(atoi(command[1]), *L);
                i = getDataP(p, *L);
                printf("%d\t%s p=%d %s %s (%d) %s", i.pid, i.user, i.prio, i.launch, i.sig.name, i.sig.num, i.comandName);
            }else{
                if(strcmp(command[1], "-fg") == 0){
                    p = findDataP(atoi(command[1]), *L);
                    i = getDataP(p, *L);
                    if(waitpid(atoi(command[2]), &i.sig.num, 0) != -1){
                        if(WIFEXITED(i.sig.num)){
                            printf("Proceso %d terminado normalmente. Valor devuelto: %d\n", atoi(command[1]), WEXITSTATUS(i.sig.num));
                            i.sig.name = "TERMINADO";
                    }
                    else if(WIFSIGNALED(i.sig.num)){
                        printf("Proceso %d terminado por la señal %d", atoi(command[1]), WTERMSIG(i.sig.num));
                        i.sig.name = "SENALADO";
                        }
                    }
                }
            }
        }        
    }
}

//-------------------------------------------------------------------------------------------
//FUNCIONES AUXILIARES
//-------------------------------------------------------------------------------------------

//Aaron eres el fucking MVP
char * getUser(uid_t uid){
    struct passwd *contraseñaNombre;
    contraseñaNombre = getpwuid(uid);
    return contraseñaNombre->pw_name;
}

uid_t getMyuid(char * name){
    struct passwd *contraseñaNombre;
    contraseñaNombre = getpwnam(name);
    return contraseñaNombre->pw_uid;
}

void enviroment(char **varEnviroment, char *enviromentName){
    int p;
    for(p = 0; env[p] != NULL; p++){
        printf("%p -> %s [%d] = (%p) %s\n", &varEnviroment[p], enviromentName, p, varEnviroment[p], varEnviroment[p]);
    }
}

//-------------------------------------------------------------------------------------------
//CODIGO DE AYUDA
//-------------------------------------------------------------------------------------------

void Cmd_fork (char *tr[]){
    pid_t pid;

    if ((pid=fork())==0){
/*		VaciarListaProcesos(&LP); Depende de la implementación de cada uno*/
        printf ("ejecutando proceso %d\n", getpid());
    }
    else if (pid!=-1)
        waitpid (pid,NULL,0);
}

int BuscarVariable (char * var, char *e[])  /*busca una variable en el entorno que se le pasa como parámetro*/{
    int pos=0;
    char aux[500];

    strcpy (aux,var);
    strcat (aux,"=");

    while (e[pos]!=NULL)
        if (!strncmp(e[pos],aux,strlen(aux)))
            return (pos);
        else
            pos++;
    errno=ENOENT;   /*no hay tal variable*/
    return(-1);
}


int CambiarVariable(char * var, char * valor, char *e[]) {
    /*cambia una variable en el entorno que se le pasa como parámetro*/
    /*lo hace directamente, no usa putenv*/
    int pos;
    char *aux;

    if ((pos=BuscarVariable(var,e))==-1)
        return(-1);

    if ((aux=(char *)malloc(strlen(var)+strlen(valor)+2))==NULL)
        return -1;
    strcpy(aux,var);
    strcat(aux,"=");
    strcat(aux,valor);
    e[pos]=aux;
    return (pos);
}

int ValorSenal(char * sen){  /*devuelve el numero de senial a partir del nombre*/

    int i;
    for (i=0; sigstrnum[i].name!=NULL; i++)
        if(!strcmp(sen, sigstrnum[i].name))
            return sigstrnum[i].num;
    return -1;
}


char *NombreSenal(int sen){  /*devuelve el nombre senal a partir de la senal*/
			/* para sitios donde no hay sig2str*/
    int i;
    for (i=0; sigstrnum[i].name!=NULL; i++)
        if (sen==sigstrnum[i].num)
            return sigstrnum[i].name;
    return ("SIGUNKNOWN");
}

void Random(char ** args, int nargs){
    
}
