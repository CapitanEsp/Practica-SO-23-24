/**Autores: Aarón Eiroa López - aaron.eiroa@udc.es  -Grupo 2.3
            Antón Soto Ríos - anton.soto@udc.es     -Grupo 2.1
**/

#include "includes.h"
#include "funcionesP0.h"
#include "listF.h"
#include "funcionesP1.h"
#include "funcionesP2.h"
#include "funcionesP3.h"

//Funciones para tratar los comandos

int partir(char *inCommand, char *outCommand[]) {
    int aux = 1;                                                                  //Inicializo la variable auxiliar
    if ((outCommand[0] = strtok(inCommand, " \n\t")) == NULL) {         //Si el comando es nulo
        return 0;                                                               //se termina la función.
    } else {
        while ((outCommand[aux] = strtok(NULL, " \n\t")) != NULL) {     //Si no, se recorre el comando dividiendolo
            aux++;                                                              //Se cuentan las partes
        }
        return aux;                                                            //Se devuelven el número de partes
    }
}

int processCommand(char *command[], int aux, tList *L, tListF *F,tListM * M, tListP *P, char ** arg3) {
    if (aux > 0) {                                                      //Si el comando tiene contenido
        if (strcmp(command[0], "authors") == 0) {                      //Se comprueba que comando es comparando strings
            if (aux <= 2) {
                autores(command, aux);                     //Se llama a la función correspondiente del comando
            } else {
                printf("Error: Exceso de argumentos\n");      //Si el numero de argumentos es incorrecto, se imprime el mensaje de error
            }
        } else if (strcmp(command[0], "pid") == 0) {                //Se repite lo mismo con todos los comandos
            if (aux <= 2) {
                pid(command, aux);
            } else {
                printf("Error: Exceso de argumentos\n");
            }
        } else if (strcmp(command[0], "chdir") == 0) {
            if (aux <= 2) {
                carpeta(command, aux);
            } else {
                printf("Error: Exceso de argumentos\n");
            }
        } else if (strcmp(command[0], "date") == 0) {
            if (aux <= 2) {
                fecha();
            } else {
                printf("Error: Exceso de argumentos\n");
            }
        } else if (strcmp(command[0], "time") == 0) {
            if (aux <= 2) {
                hora();
            } else {
                printf("Error: Exceso de argumentos\n");
            }
        } else if (strcmp(command[0], "hist") == 0) {
            if (aux <= 2) {
                hist(command, aux, L);
            } else {
                printf("Error: Exceso de argumentos\n");
            }
        } else if (strcmp(command[0], "comand") == 0) {
            if (aux == 2) {
                comandoN(command, *L, *F,*M, *P, arg3);
            } else if (aux == 1) {
                printf("Error: Introduce una N\n");
            } else printf("Error: Exceso de argumentos\n");

        } else if (strcmp(command[0], "open") == 0) {
            Cmd_open(command, F);
        } else if (strcmp(command[0], "close") == 0) {
            Cmd_close(command, F);
        } else if (strcmp(command[0], "dup") == 0) {
            Cmd_dup(command, F);
        } else if (strcmp(command[0], "listopen") == 0) {
            listopen(*F);
        } else if (strcmp(command[0], "infosys") == 0) {
            if (aux <= 2) {
                infosis();
            } else {
                printf("Error: Exceso de argumentos\n");
            }
        } else if (strcmp(command[0], "help") == 0) {
            if (aux <= 2) {
                ayuda(command, aux);
            } else {
                printf("Error: Exceso de argumentos\n");
            }
        } else if (strcmp(command[0], "create") == 0) {
            myCreate(command, aux);
        } else if (strcmp(command[0], "delete") == 0) {
            myDelete(command, aux);
        } else if (strcmp(command[0], "stat") == 0) {
            myStats(command, aux);
        } else if (strcmp(command[0], "list") == 0) {
            myList(command, aux);
        } else if (strcmp(command[0], "deltree") == 0) {
            myDelTree(command, aux);
        }  else if (strcmp(command[0], "malloc") == 0) {
            myMalloc(command,aux,M);
        }  else if (strcmp(command[0], "shared") == 0) {
            myShared(command,aux,M);
        }  else if (strcmp(command[0], "mmap") == 0) {
            myMmap(command,aux,M);
        }  else if (strcmp(command[0], "read") == 0) {
            myRead(command);
        }  else if (strcmp(command[0], "write") == 0) {
            myWrite(command,aux,*M);
        }  else if (strcmp(command[0], "memdump") == 0) {
            Memdump(command,aux,*M);
        }  else if (strcmp(command[0], "memfill") == 0) {
            Memfill(command,aux,*M);
        }  else if (strcmp(command[0], "recurse") == 0) {
            Recursive(command,aux);
        }  else if (strcmp(command[0], "mem") == 0) {
            mem(command,aux,*M);
        }  else if (strcmp(command[0], "fork") == 0) {
            my_Fork(command,aux);
        }  else if (strcmp(command[0], "uid") == 0) {
            uid(command,aux);
        }else if (strcmp(command[0], "exec") == 0) {
            exec(command,aux);
        }else if (strcmp(command[0], "showvar") == 0) {
            showvar(command,aux,arg3);
        }else if (strcmp(command[0], "changevar") == 0) {
            changevar(command,aux,arg3);
        }else if (strcmp(command[0], "subsvar") == 0) {
            subsvar(command,aux,arg3);
        }else if (strcmp(command[0], "showenv") == 0) {
            showenv(command,aux,arg3);
        }else if (strcmp(command[0], "jobs") == 0) {
            jobs(command,aux, P);
        }else if (strcmp(command[0], "deljobs") == 0) {
            deljobs(command,aux, P);
        }else if (strcmp(command[0], "job") == 0) {
            job(command,aux, P);
        }
        else if (strcmp(command[0], "pmap") == 0) {
            Do_MemPmap();
        }else if ((strcmp(command[0], "quit") == 0) || (strcmp(command[0], "bye") == 0) ||
                (strcmp(command[0], "exit") == 0)) { //Como hacen lo mismo se comprueban juntos
            if (aux <= 2) {
                return 1;                           //Devuelve 1 para terminar el bucle en el main
            } else {
                printf("Error: Exceso de argumentos\n");
            }
        } else Random(command, aux, P);
    }
    return 0;
}

//Funciones de los comandos

void autores(char *command[], int aux) {
    if (aux == 1) {
        printf("Autor 1: Aaron Eiroa Lopez: aaron.eiroa@udc.es\n"
               "Autor 2: Anton Soto Rios: anton.soto@udc.es\n");
    } else {
        if (strcmp(command[1], "-l") == 0)
            printf("Autor 1: aaron.eiroa@udc.es\nAutor 2: anton.soto@udc.es\n");
        else if (strcmp(command[1], "-n") == 0)
            printf("Autor 1: Aaron Eiroa Lopez\nAutor 2: Anton Soto Rios\n");
    }
}

void pid(char *command[], int aux) {
    if (aux == 1) printf("Pid del shell: %d\n", getpid());
    else if (strcmp(command[1], "-p") == 0) printf("Pid del padre del shell: %d\n", getppid());
}

void carpeta(char *command[], int aux) {
    char path[TCOM];
    if (aux == 1) {
        getcwd(path, TCOM);                     //Se obtiene el directorio actual y se guarda en un string
        printf("Ruta actual: %s\n", path);
    } else {
        if (chdir(command[1]) == -1) perror("No se pudo acceder al directorio\n");
    }
}

void infosis() {
    struct utsname pc;
    uname(&pc);
    printf("%s  %s, SO:%s\n", pc.sysname, pc.nodename, pc.version);
}

void hora() {
    time_t auxtime;
    struct tm *sTime;
    time(&auxtime);
    sTime = localtime(&auxtime);
    if (sTime != NULL) {
        printf("Time: %d:%02d:%02d\n", sTime->tm_hour, sTime->tm_min, sTime->tm_sec);
    } else {
        perror("Error: Command failed");
    }
}

void fecha() {
    time_t auxtime;
    struct tm *sTime;
    time(&auxtime);
    sTime = localtime(&auxtime);
    if (sTime != NULL) {
        printf("Date: %d/%d/%d\n", sTime->tm_mday, sTime->tm_mon + 1, sTime->tm_year + 1900);
    } else {
        perror("Error: Command failed");
    }
}

void hist(char **comand, int aux, tList *L) {
    tPosL i;
    int n, m = 0;
    if (aux == 1) {                                             //Si el comando es "hist" se recorre la lista
        for (i = first(*L); i != NULL; i = next(i, *L)) {   //y se imprimen los comandos.
            printf("%s", getItem(i, *L));
        }
    } else if (strcmp(comand[1], "-c") == 0) {                  //Si es "hist -c"
        delHistoric(L);                                        //se eliminan los comandos la lista.
    } else {                                                   //Si es "hist -N"
        n = quitarGuion(comand[1]);                         //Se elimina el guion en una función auxiliar
        for (i = first(*L);
             n != 0; i = next(i, *L)) {      //Se recorre la lista el numero de veces solicitado en el comando
            printf("\t%d %s\n", m, getItem(i, *L));     //Y se imprime en cada iteración el comando
            m++;
            n--;
        }
    }
}

void comandoN(char **comand, tList L, tListF F,tListM M, tListP P, char** arg3) {
    int n, n2;
    char *comando;
    char *auxcmd[TCOM];
    tPosL i;
    n = abs(atoi(comand[1]));           //Se obtiene el int del numero pasado por comando
    if ((i = findItem(n, L)) != NULL) {         //Si se encuentra el comando en la lista
        comando = getItem(i, L);           //Se obtiene su contenido
        if (strncmp(comando, "comand", strlen(comando)) == 0) {    //Si el comando es "comand"
            printf("No se puede ejecutar comando comando\n");  //Se evita un bucle infinito
        } else {
            n2 = partir(comando, auxcmd);   //Si no, se parte el comando otra vez
            processCommand(auxcmd, n2, &L, &F,&M, &P, arg3);      //y se procesa el comando de nuevo.
        }
    } else {
        perror("Error: El argumento es incorrecto o el digito no es valido.");
    }
}

void ayuda(char **command, int aux) {
    if (aux == 1) {
        printf("Command list: \n \t- authors"
               "\n \t- pid\n \t- chdir\n \t- date"
               "\n \t- time\n \t- hist\n \t- comand"
               "\n \t- open\n \t- close\n \t- dup"
               "\n \t- listopen\n \t- infosys"
               "\n \t- help\n \t- quit\n \t- exit"
               "\n \t- bye\n \t- create\n \t- stat"
               "\n \t- list\n \t- delete\n \t- deltree");
    } else if (strcmp(command[1], "authors") == 0) {
        printf("authors [-l]: Muestra los login de los autores.\n"
               "\t[-n]: Muestra los nombres de los autores.\n"
               "\t[]: Muestra las dos opciones anteriores.\n");
    } else if (strcmp(command[1], "pid") == 0) {
        printf("pid []: Muestra el pid del proceso que se está ejecutando en el shell.\n"
               "\t[-p]: Muestra el pid del proceso padre del shell.\n");
    } else if (strcmp(command[1], "chdir") == 0) {
        printf("chdir [dir]: Cambia el directorio actual para el solicitado.\n"
               "\t[]: Imprime el directorio actual.\n");
    } else if (strcmp(command[1], "hist") == 0) {
        printf("hist []: Muestra la lista de comandos usados anteriormente con un número asignado.\n"
               "\t[-N]: Muestra los N primeros comandos.\n"
               "\t[-c]: Elimina la lista de comandos guardados.\n");
    } else if (strcmp(command[1], "date") == 0) {
        printf("date: Muestra la fecha actual.\n");
    } else if (strcmp(command[1], "time") == 0) {
        printf("time: Muestra la hora actual.\n");
    } else if (strcmp(command[1], "comand") == 0) {
        printf("comand [-N]: Repite el comando número N del historial.\n");
    } else if (strcmp(command[1], "infosys") == 0) {
        printf("infosys: Muestra las especificaciones de la máquina.\n");
    } else if (strcmp(command[1], "help") == 0) {
        printf("help []: Imprime una lista de los comandos disponibles.\n"
               "\t[cmd]: Imprime un texto de ayuda del comando solicitado.\n");
    } else if (strcmp(command[1], "listopen") == 0) {
        printf("listopen: Nombra los ficheros abiertos en el shell, el modo de apertura y su"
               "descriptor.\n");
    } else if (strcmp(command[1], "open") == 0) {
        printf("open []: Nombra los ficheros abiertos en el shell, el modo de apertura y su"
               "descriptor.\n"
               "\t[file]: Mete en la lista de ficheros el fichero, su descriptor y sus permisos.\n"
               "\tmode: Abre el fichero con los modos seleccionados "
               "\n\tcr=O_CREAT\tex=O_EXCL\n\t\tro=O_RDONLY\two=O_WRONLY\n"
               "\t\trw=O_RDWR\tap=O_APPEND\n\t\ttr=O_TRUNC\n");
    } else if (strcmp(command[1], "close") == 0) {
        printf("close []: Nombra los ficheros abiertos en el shell, el modo de apertura y sus"
               "descriptor.\n"
               "\t[df]: Elimina el fichero solicitado de la lista de ficheros abiertos.\n");
    } else if (strcmp(command[1], "dup") == 0) {
        printf("dup []: Nombra los ficheros abiertos en el shell, el modo de apertura y su"
               "descriptor.\n"
               "\t[df]: Duplica el fichero solicitado de la lista de abiertos.\n");
    } else if (strcmp(command[1], "create") == 0) {
        printf("create [-f] [name]: Crea un directorio con nombre name en el directorio actual\n"
               "\t[-f] [name]: Crea un fichero con nombre name en el directorio actual");
    } else if (strcmp(command[1], "delete") == 0) {
        printf("delete [name1 name2 ...]: Elimina ficheros y directorios vacios\n");
    } else if (strcmp(command[1], "stat") == 0) {
        printf("stat [-long] [-acc] [-link] name1 name2 ...: Muestra informacion sobre ficheros o directorios\n"
               "\t[-long]: Muestra el listado largo del fichero\n"
               "\t[-acc]: Muestra la ultima vez que se accedió al fichero/directorio\n"
               "\t[-link]: Si es enlace simbolico, muestra el path contenido\n");
    } else if (strcmp(command[1], "list") == 0) {
        printf("list [-reca] [-recb] [-hid] [-long] [-acc] [-link] name1 name2 ...: Lista contenido de directorios\n"
               "\t[-reca]: Muestra el listado recursivo hacia delante\n"
               "\t[-recb]: Muestra el listado recursivo hacia atras\n"
               "\t[-hid]: Muestra los ficheros ocultos\n"
               "\tResto de parametros como stat\n");
    } else if (strcmp(command[1], "deltree") == 0) {
        printf("deltree [name1 name2 ...]: Elimina recursivamente ficheros o directorios no vacios\n");
    } else if (strcmp(command[1], "malloc") == 0) {
        printf("malloc [-free] [tam]: Asigna un bloque de memoria de tamaño tam con malloc\n"
               "\t[-free]: Desasigna un bloque de memoria de tamaño tam asignado por malloc");
    }  else if (strcmp(command[1], "shared") == 0) {
        printf("shared [-free|-create|-delkey] cl [tam] asigna memoria compartida con clave cl en el programa\n"
               "\t[-create] cl tam: asigna (creando) el bloque de memoria compartida de clave cl y tamano tam\n"
               "\t[-free] cl: desmapea el bloque de memoria compartida de clave cl\n"
               "\t[-delkey] cl: elimina del sistema (sin desmapear) la clave de memoria cl\n");
    } else if (strcmp(command[1], "mmap") == 0) {
        printf("mmap [-free] fich perm: mapea el fichero fich con permisos perm\n"
               "\t[-free]: Desmapea el fichero fich\n");
    } else if (strcmp(command[1], "recurse") == 0) {
        printf("recurse [n]: Invoca a la funcion recursive n veces\n");
    } else if (strcmp(command[1], "read") == 0) {
        printf("read [file][dirMem][bytes]: Lee el fichero nombrado en la direccion de memoria solicitada. Se"
                "puede especificar cuantos bytes se quieren leer.\n");
    } else if (strcmp(command[1], "write") == 0) {
        printf("write [file][dirMem][bytes]: Escribe el numero de bytes desde dirMem en file\n"
                "\t[-o]: Indica sobreescritura\n");
    } else if (strcmp(command[1], "memdump") == 0) {
        printf("memdump [dirMem]: Muestra el numero de bytes que hay en dirMem.\n"
                "\t[bytes]: Se especifica el numero de bytes a volcar\n");
    } else if (strcmp(command[1], "memfill") == 0) {
        printf("memfill [dirMem]: Llena la direccion de memoria a partir de dirMem.\n"
        "\t[bytes]: Se especifica el numero de bytes a rellenar\n"
        "\t[var]: Se especifica el caracter, por defecto sera 'A'\n"); 
    } else if (strcmp(command[1], "mem") == 0) {
        printf("mem [-blocks|-funcs|-vars|-all|-pmap]: Muestra detalles de la memoria de la shell.\n"
        "\t[-blocks]: Muestra el numero de bloques asignados\n"
        "\t[-funcs]: Muestra las direcciones de las funciones asignadas\n"
        "\t[-vars]: Muestra las direcciones de las variables asignadas\n"
        "\t[-pmap]: Muestra la salida del comando pmap\n"
        "\t[-all]: Muestra todo lo nombrado anteriormente\n");                                
    }else if (strcmp(command[1], "quit") == 0) {
        printf("quit: Termina la ejecución del shell.\n");
    } else if (strcmp(command[1], "exit") == 0) {
        printf("exit: Termina la ejecución del shell.\n");
    } else if (strcmp(command[1], "bye") == 0) {
        printf("bye: Termina la ejecución del shell.\n");
    }
}

void listopen(tListF L) {
    tPosF p;
    tItemF i;
    for (p = firstF(L);
         p != NULL; p = nextF(p, L)) {  //Se recorre la lista de ficheros
        i = getDataF(p, L);    //Se obtiene la información del fichero
        printf("descriptor: %d -> %s ", i.df, i.name);
        permisosChar(i.mode);    //Se imprime la información del fichero de esta iteración
    }
}

void Cmd_open(char *comand[], tListF *L) {
    int i, df, mode = 0;

    if (comand[1] == NULL) { //Si no hay parametros
        listopen(*L);       //Se muestra la lista de ficheros
        return;
    }
    for (i = 2; comand[i] != NULL; i++) //Si los hay, se mira los permisos que tiene
        if (!strcmp(comand[i], "cr"))mode |= O_CREAT;
        else if (!strcmp(comand[i], "ex"))mode |= O_EXCL;
        else if (!strcmp(comand[i], "ro"))mode |= O_RDONLY;
        else if (!strcmp(comand[i], "wo"))mode |= O_WRONLY;
        else if (!strcmp(comand[i], "rw")) mode |= O_RDWR;
        else if (!strcmp(comand[i], "ap")) mode |= O_APPEND;
        else if (!strcmp(comand[i], "tr")) mode |= O_TRUNC;
        else break;

    if ((df = open(comand[1], mode, 0777)) == -1)           //Si no se puede abrir
        perror("Imposible abrir fichero");                        //Se muestra un mensaje de error
    else {
        insertDataF(df, mode, comand[1],
                    L);               //Si la apertura es exitosa, se introduce el fichero en la lista de ficheros
        printf("Anadida entrada a la tabla ficheros abiertos..................%d \n", df);
    }
}

void Cmd_close(char *comand[], tListF *L) {
    int df;
    tPosF p;

    if (comand[1] == NULL || (df = atoi(comand[1])) < 0) { //Si no hay parámetros o el descriptor es menor que 0
        listopen(*L);                                          //Se muestra la lista de ficheros
        return;
    }
    if (close(df) == -1)                        //Si no se puede cerrar
        perror("Inposible cerrar descriptor");  //Se muestra un mensaje de error
    else {
        //........EliminarDeFicherosAbiertos......
        p = findDataF(df, *L);                  //Si no, se busca el fichero
        if (p != LNULL) {                         //Si es distinta de nulo
            deleteAtPosF(p, L);                  //Se elimina la posición
        }
    }
}

void Cmd_dup(char *comand[], tListF *L) {
    int df, dfDuplicado;
    char aux[500];
    tPosF p;
    tItemF i;
    if (comand[1] == NULL || (df = atoi(comand[1])) < 0) {  //Si no hay parámetros o el descriptor es menor que 0
        listopen(*L);                                           //Se abre la lista de ficheros
        return;
    }


    dfDuplicado = dup(df);                     //Se obtiene el descriptor del duplicado
    p = findDataF(df, *L);                     //Se encuentra el original
    if (p != NULL) {                                //Si la posición no es nula
        i = getDataF(p, *L);                   //Se obtiene la información de la posición
    }
    sprintf(aux, "dup %d (%s)", dfDuplicado, i.name);
    //.......AnadirAFicherosAbiertos......duplicado......aux.....fcntl(duplicado,F_GETFL).....;
    insertDataF(dfDuplicado, i.mode, aux, L);   //Se introduce el duplicado en la lista de ficheros
}

//Funciones auxiliares

void permisosChar(int mode) {
    if (mode & O_RDONLY) {
        printf("O_RDONLY ");
    }
    if (mode & O_WRONLY) {
        printf("O_WRONLY ");
    }
    if (mode & O_RDWR) {
        printf("O_RDWR ");
    }
    if (mode & O_APPEND) {
        printf("O_APPEND ");
    }
    if (mode & O_CREAT) {
        printf("O_CREAT ");
    }
    if (mode & O_EXCL) {
        printf("O_EXCL ");
    }
    if (mode & O_TRUNC) {
        printf("O_TRUNC ");
    }
    printf("\n");
}

int quitarGuion(char *inCommand) {
    int ret;
    memmove(inCommand, inCommand + 1, strlen(inCommand));
    ret = atoi(inCommand);
    return ret;
}