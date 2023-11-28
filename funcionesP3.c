#include "funcionesP3.h"

//-------------------------------------------------------------------------------------------
//FUNCIONES PRINCIPALES (AARON HAGO LO QUE PUEDO)
//-------------------------------------------------------------------------------------------

void uid(char *command, int nargs){
    if(nargs > 2){
        if(strcmp(command[1], "-get") == 0){
            if(nargs == 3){
                //Hacer codigo
            }else{
                perror("Numero de parametros incorrecto");
            }
        }
        if(strcmp(command[1], "-set") == 0){
            if(nargs == 3){
                //Hacer codigo
            }else{
                if((nargs == 4) && (strcmp(command[2],"-l") == 0)){
                    //Hacer codigo
                }else{
                    perror("Numero de parametros incorrecto");
                }
            }
        }
    }else{
        if(nargs == 2){
            //Hacer codigo
        }else{
            perror("Numero de parametros incorrecto");
        }
    }
}

void showvar(char ** args){
    //Valor y direcciones de la variable de entorno
}

void changevar(char ** args,int nargs){
    if(nargs == 3){
        //Cambia el valor de una variable de entorno
    }else{
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
    }
}

void subsvar(char ** args,int nargs){
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

void showenv(char ** args,int nargs){
    if(nargs == 2){
        if(strcmp(command[1], "-environ") == 0){
            //Hacer codigo
        }
        if(strcmp(command[1], "-addr") == 0){
            //Hacer codigo
        }     
    }else{
        perror("Numero de parametros incorrecto"); 
    }
}

void my_Fork(char ** args,int nargs){
    //No entendi ni chota
}

//void exec(char ** args,int nargs); //Acabo de ver el shell de referencia y me quede como estaba o peor


void jobs(char ** args,int nargs){
    //Lista los procesos en segundo plano
}

void deljobs(char ** args,int nargs){
    if(nargs == 2){
        if(strcmp(command[1], "-term") == 0){
            //Hacer codigo
        }
        if(strcmp(command[1], "-sig") == 0){
            //Hacer codigo
        }     
    }else{
        perror("Numero de parametros incorrecto"); 
    }
}

void job(char ** args, int nargs){
    if(nargs <= 2 && nargs < 4){
        if(strcmp(command[1], "-fg") == 0){
            //Hacer codigo
        }else{
            //Hacer codigo
        }
    }else{
        perror("Numero de parametros incorrecto"); 
    }
}

//-------------------------------------------------------------------------------------------
//FUNCIONES AUXILIARES
//-------------------------------------------------------------------------------------------

//Aaron eres el fucking MVP



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
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (!strcmp(sen, sigstrnum[i].nombre))
            return sigstrnum[i].senal;
    return -1;
}


char *NombreSenal(int sen){  /*devuelve el nombre senal a partir de la senal*/
			/* para sitios donde no hay sig2str*/
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (sen==sigstrnum[i].senal)
            return sigstrnum[i].nombre;
    return ("SIGUNKNOWN");
}

void Random(char ** args, int nargs){
    execl(args[0],*args);
}
