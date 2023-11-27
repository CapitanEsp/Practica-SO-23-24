#include "funcionesP1.h"
#include "funcionesP0.h"

void myCreate(char **command, int aux) {
    if (strcmp(command[1], "-f") == 0) {
        if (open(command[2], O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
            perror("Error: El fichero no se pudo crear");
        } else printf("Se ha creado el fichero %s\n", command[2]);
    } else if (aux == 2) {
        if (mkdir(command[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) < 0) {
            perror("Error: No se pudo crear el directorio");
        } else printf("Se ha creado el directorio %s\n", command[1]);
    }
}

void myStats(char **command, int aux) {
    struct stat info;
    int i = 1;
    bool Long = 0, Link = 0, Acc = 0;
    while (aux > 1 && i < aux) {//Bucle para detectar las opciones pasadas como argumento
        if (strcmp(command[i], "-long") == 0) Long = true;
        else if (strcmp(command[i], "-link") == 0) Link = true;
        else if (strcmp(command[i], "-acc") == 0) Acc = true;
        else break;
        i++;
    }
    for (; i < aux; i++) {
        //Si no se pudo acceder al fichero devuelve error
        if (lstat(command[i], &info) == -1) fprintf(stderr, "Error al acceder a %s: %s\n", command[i], strerror(errno));
        else print_Stat(Long, Link, Acc, info, command[i]);
    }
}

void myDelete(char **command, int aux) {
    int j;
    struct stat info;
    for (j = 1; j < aux; j++) {
        lstat(command[j], &info);
        if (LetraTF(info.st_mode) == 'd') {
            if (rmdir(command[j]) != 0) {
                perror("Error: No se puede borrar el directorio");
            } else {
                printf("Se ha eliminado el directorio %s\n", command[j]);
            }
        } else if (LetraTF(info.st_mode) == '-') {
            if ((info.st_size == 0) &&
                unlink(command[j]) != 0) {//Se comprueba q el fichero este vacio sino no se puede borrar
                perror("Error: No se puede eliminar el fichero");
            } else {
                printf("Se ha eliminado el fichero %s\n", command[j]);
            }
        }
    }
}

void myList(char **command, int aux) {
    int i = 1;
    bool Long = 0, Link = 0, Acc = 0, recA = 0, recB = 0, hid = 0;

    while (aux > 1 && i < aux && *command[i] == '-') {//Bucle para detectar las opciones pasadas como argumento
        if (strcmp(command[i], "-reca") == 0) recA = 1;
        else if (strcmp(command[i], "-recb") == 0) recB = 1;
        else if (strcmp(command[i], "-hid") == 0) hid = 1;
        else if (strcmp(command[i], "-long") == 0) Long = 1;
        else if (strcmp(command[i], "-link") == 0) Link = 1;
        else if (strcmp(command[i], "-acc") == 0) Acc = 1;
        else break;
        i++;
    }
    if (recA && recB) recA = 0; //Para evitar caer en bucle infinito desactivamos un tipo de rec
    if (command[i] == NULL) carpeta(command, 1); //Muestra la ruta actual
    else if (i < aux) for (; i < aux; i++) listrec(command[i], Long, Link, Acc, recA, recB, hid);
}

void myDelTree(char **command, int trozos) {
    if (trozos == 1) {
        int dir_size = 512;
        char dir[dir_size];
        getcwd(dir, dir_size);
        printf("%s\n", dir);
    } else {
        for (int aux = 1; aux < trozos; aux++) {
            struct stat statbuf;
            if (lstat(command[aux], &statbuf) != 0) {
                printf("Imposible borrar %s: %s\n", command[aux], strerror(errno));
            } else {
                if (LetraTF(statbuf.st_mode) == 'd') {
                    aux_Deltree(command[aux]);
                } else printf("%s no es un directorio\n", command[aux]);
            }
        }
    }
}

//Funciones auxiliares
void print_Stat(bool Long, bool Link, bool Acc, struct stat info, char *name) {
    char permisos[12], format_date[22], path[PATH_MAX];
    struct tm *aux = localtime((const time_t *) &info.st_atim);

    strftime(format_date, sizeof(format_date), "%Y/%m/%d %H:%M:%S", aux);//Formatea la fecha
    if (Long) {
        printf("%s\t%ld(%ld)\t %s\t%s\t%s\t%ldB %s\n", format_date,
               info.st_blocks, info.st_ino, getpwuid(info.st_gid)->pw_name, getpwuid(info.st_uid)->pw_name,
               ConvierteModo(info.st_mode, permisos), info.st_size, name);
    } else if (Link) {
        if (readlink(name, path, PATH_MAX) == -1)perror("");
        printf("\t%lu\t%s -> %s \n", info.st_nlink, name, path);
    } else if (Acc) {
        printf("\t%s %ld %s\n", format_date, info.st_size, name);
    } else {
        printf("\t%lu %s\n", info.st_size, name);
    }
}

void aux_Deltree(char *name) {
    DIR *d;
    struct dirent *dirInfo;
    struct stat info;

    if ((d = opendir(name)) == NULL) { //No se pudo abrir o no existe directorio name
        printf("No se pudo leer el directorio: %s\n%s", name, strerror(errno));
        return;
    }
    chdir(name); //Entramos al directorio
    while ((dirInfo = readdir(d)) != NULL) {
        lstat(dirInfo->d_name, &info);
        if (strcmp(dirInfo->d_name, "..") != 0 && strcmp(dirInfo->d_name, ".") != 0) {
            if (LetraTF(info.st_mode) == 'd') {//Si encuentra otro directorio hace llamada recursiva
                aux_Deltree(dirInfo->d_name);
            } else if (remove(dirInfo->d_name) != 0) {//Borra ficheros
                printf("Imposible borrar %s: %s\n", dirInfo->d_name, strerror(errno));
            }
        }
    }
    chdir("..");//Regresa al directorio anterior para poder borrar el actual
    closedir(d);
    remove(name);
}

void listrec(char *name, bool Long, bool Link, bool Acc, bool recA, bool recB, bool hid) {
    DIR *dp;                                                        //Creo una variable DIR para acceder al path
    struct dirent *dirp;                                            //Un struct para acceder a sus datos
    struct stat infoFichero = {0};                                  //Creo dos variables auxiliares para recorrer
    struct stat infoFichero2 = {0};                                 //el directorio y guardar su información
    char nombreFichero[PATH_MAX];
    char nombreFichero2[PATH_MAX];
    char pathInicial[PATH_MAX];
    nombreFichero[0] = '\0';                                        //Me aseguro de que la cadena esté bien formateada
    char format;                                                    //Inicializo el caracter donde voy a guardar el formato del archivo

    getcwd(pathInicial, PATH_MAX);

    if (lstat(name, &infoFichero) == -1) {                              //Si no se puede obtener la información del
        fprintf(stderr, "Error1 %s: %s\n", name, strerror(errno));      //fichero recibido, se imprime un error
    }
    format = LetraTF(infoFichero.st_mode);                              //Se obtiene el formato del archivo
    if (format == 'd') {                                               //Si es un directorio

        if ((dp = opendir(name)) == NULL) {                            //Y se puede abrir
            perror("error2");
        }
        if (!recB)closedir(dp);                                         //En caso de no ser recursivo B, lo cierro, debido
        //a que compruebo este caso más adelante
        if (recB) {                                                     //Si es recursivo B
            if (chdir(name) == -1) {                                    //Se accede al directorio
                perror("error3");
                return;
            }                                                           //Se recorre el directorio con un bucke
            while ((dirp = readdir(dp)) != NULL) {                      //Si no es el directorio actual o el padre
                if ((strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)) {
                    snprintf(nombreFichero, sizeof(nombreFichero), "%s", dirp->d_name); //Se copia el nombre del fichero de la iteración actual en un string
                    nombreFichero[sizeof(nombreFichero) - 1] = '\0'; //Me aseguro de que la cadena esta bien formateada.
                    if (lstat(nombreFichero, &infoFichero) == -1) { //Si no se puede obtener la info del archivo de esta iteración
                        fprintf(stderr, "Error al acceder a4 %s: %s\n", nombreFichero, strerror(errno)); //Se imprime el error correspondiente
                        // Continúa o retorna, dependiendo de cómo desees manejar el error.
                    }
                    if (nombreFichero[0] == '.') {                                      //Si es un fichero oculto
                        if (hid) {                                                      //Y la flag "hid" está activada
                            listrec(nombreFichero, Long, Link, Acc, recA, recB, hid);   //Se activa la recursividad en ese archivo
                        }
                    } else {                                                            //Si no es un fichero oculto
                        listrec(nombreFichero, Long, Link, Acc, recA, recB, hid);       //Se activa la recursividad
                    }

                }
            }
            closedir(dp);                                                              //Se cierra el archivo pasado por parámetro
            if ((strcmp(name, ".") != 0 && strcmp(name, "..") != 0)) {              //Si no es el directorio padre ni el actual

                chdir("..");                                                       //Se vuelve al fichero padre
            }
        }
        printf("************%s\n", name);                                          //Y se imprime el nombre pasado por parametro

        if (lstat(name, &infoFichero) == -1) {                                          //Se hacen las mismas comprobaciones que antes
            fprintf(stderr, "Error en lstat para6 %s: %s\n", name, strerror(errno));    //Y se prodece a imprimir los archivos
        }                                                                              //Acabando la recursividad
        format = LetraTF(infoFichero.st_mode);
        if (format == 'd') {
            if ((dp = opendir(name)) == NULL) {
                perror("error7");
            }
            if (chdir(name) == -1) {
                perror("error8");
                return;
            }
            while ((dirp = readdir(dp)) != NULL) {
                if (dirp->d_name[0] == '.') {
                    if (hid) {
                        snprintf(nombreFichero2, sizeof(nombreFichero2), "%s", dirp->d_name);
                        nombreFichero2[sizeof(nombreFichero2) -
                                       1] = '\0'; // Asegura que la cadena esté terminada con nulo.
                        if (lstat(nombreFichero2, &infoFichero2) == -1) {
                            fprintf(stderr, "Error al acceder a9 %s: %s\n", nombreFichero2, strerror(errno));
                            // Continúa o retorna, dependiendo de cómo desees manejar el error.
                        }
                        print_Stat(Long, Link, Acc, infoFichero2, nombreFichero2);
                    }
                } else {
                    snprintf(nombreFichero2, sizeof(nombreFichero2), "%s", dirp->d_name);
                    nombreFichero2[sizeof(nombreFichero2) - 1] = '\0'; // Asegura que la cadena esté terminada con nulo.
                    if (lstat(nombreFichero2, &infoFichero2) == -1) {
                        fprintf(stderr, "Error al acceder a9 %s: %s\n", nombreFichero2, strerror(errno));
                        // Continúa o retorna, dependiendo de cómo desees manejar el error.
                    }
                    print_Stat(Long, Link, Acc, infoFichero2, nombreFichero2);
                }

            }
            if(strcmp(name, "..") == 0){
                chdir(pathInicial);
            }
            closedir(dp);
            if ((strcmp(name, ".") != 0 && strcmp(name, "..") != 0)) {
                chdir("..");
            }
            if (recA) {                                                             //Si es recA, se ejecuta casi lo mismo que
                if (lstat(name, &infoFichero) == -1) {                             //RecB pero despues de imprimir la lista
                    fprintf(stderr, "Error10 %s: %s\n", name, strerror(errno));
                }
                format = LetraTF(infoFichero.st_mode);
                if ((dp = opendir(name)) == NULL) {
                    perror("error11");
                }
                if (format == 'd') {
                    if (chdir(name) == -1) {
                        perror("error12");
                        return;
                    }
                    while ((dirp = readdir(dp)) != NULL) {
                        if ((strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)) {
                            snprintf(nombreFichero, sizeof(nombreFichero), "%s", dirp->d_name);
                            nombreFichero[sizeof(nombreFichero) -
                                          1] = '\0'; // Asegura que la cadena esté terminada con nulo.
                            if (lstat(nombreFichero, &infoFichero) == -1) {
                                fprintf(stderr, "Error al acceder a13 %s: %s\n", nombreFichero, strerror(errno));
                                // Continúa o retorna, dependiendo de cómo desees manejar el error.
                            }
                            if (nombreFichero[0] == '.') {
                                if (hid) {
                                    listrec(nombreFichero, Long, Link, Acc, recA, recB, hid);
                                }
                            } else {
                                listrec(nombreFichero, Long, Link, Acc, recA, recB, hid);
                            }
                        }
                    }
                    closedir(dp);                                                   //La unica diferencia es que cerramos el
                    if ((strcmp(name, ".") != 0 && strcmp(name, "..") != 0)) {      //directorio al acabar la recursividad
                        chdir("..");
                    }
                }
            }
        }
    }    else if(format=='-') print_Stat(Long,Link,Acc,infoFichero,name);

}
//Código de ayuda

char LetraTF(mode_t m) {
    switch (m & S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK:
            return 's'; /*socket */
        case S_IFLNK:
            return 'l'; /*symbolic link*/
        case S_IFREG:
            return '-'; /* fichero normal*/
        case S_IFBLK:
            return 'b'; /*block device*/
        case S_IFDIR:
            return 'd'; /*directorio */
        case S_IFCHR:
            return 'c'; /*char device*/
        case S_IFIFO:
            return 'p'; /*pipe*/
        default:
            return '?'; /*desconocido, no deberia aparecer*/
    }
}
/*las siguientes funciones devuelven los permisos de un fichero en formato rwx----*/
/*a partir del campo st_mode de la estructura stat */
/*las tres son correctas pero usan distintas estrategias de asignaciÃ³n de memoria*/

char *ConvierteModo(mode_t m, char *permisos) {
    strcpy(permisos, "---------- ");

    permisos[0] = LetraTF(m);
    if (m & S_IRUSR) permisos[1] = 'r';    /*propietario*/
    if (m & S_IWUSR) permisos[2] = 'w';
    if (m & S_IXUSR) permisos[3] = 'x';
    if (m & S_IRGRP) permisos[4] = 'r';    /*grupo*/
    if (m & S_IWGRP) permisos[5] = 'w';
    if (m & S_IXGRP) permisos[6] = 'x';
    if (m & S_IROTH) permisos[7] = 'r';    /*resto*/
    if (m & S_IWOTH) permisos[8] = 'w';
    if (m & S_IXOTH) permisos[9] = 'x';
    if (m & S_ISUID) permisos[3] = 's';    /*setuid, setgid y stickybit*/
    if (m & S_ISGID) permisos[6] = 's';
    if (m & S_ISVTX) permisos[9] = 't';

    return permisos;
}