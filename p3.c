/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es
         Antón Soto Ríos - anton.soto@udc.es**/

#include "funcionesP0.h"
#include "listF.h"
#include "TADLista.h"
#include "includes.h"
#include <unistd.h>

extern char **environ;

char** varEnviroment = NULL;


///valgrind --leak-check=full --show-leak-kinds=all ./p3
int main(int nargs, char **argv, char **arg3) {
    varEnviroment = environ;
    int fin = 0, num;        //Creo la variable del bucle y la variable donde guardo en cuantas partes se divide el comando
    char t[TCOM];               //Variable donde guardo el comando sin dividir
    char *command[MAX];         //Array donde guardo el comando dividido
    tList L;
    tListF F;
    tListM M;
    tListP P;

    createEmptyList(&L);        //Creo la lista vacía
    createEmptyListF(&F);
    createEmptyListM(&M);
    createEmptyListP(&P);

    while (fin == 0) {
        printf("\n--> ");                            //Printeo el prompt
        fgets(t, TCOM, stdin);                   //Guardo el comando escrito por teclado
        insertItem(t, &L);                          //Meto el comando en el historial
        num = partir(t, command);                  //Parto el comando
        fin = processCommand(command, num, &L, &F,&M, &P, arg3);   //Proceso el comando y miro si el comando finaliza el bucle
    }
    //Si se cierra el Shell se elimina el historial
    delListF(&F);
    delListM(&M);
    delHistoric(&L);
    delListP(&P);
    printf("See you later alligator\n");

    return 0;
}
