#include "funcionesP3.h"
/*el siguiente codigo se da como ayuda por si se quiere utilizar*/
/*NO ES OBLIGATORIO USARLO*/
/*y pueden usarse funciones enteras o parte de funciones */

/*Este fichero, ayudaP3.c no está pensado para ser compilado separadamente */
/*, entre otras cosas, no contiene los includes necesarios*/
/*y las constantes utilizadas, no están definidas en él*/

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
