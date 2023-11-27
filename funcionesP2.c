#include "funcionesP2.h"

void myMalloc(char **command, int nargs, tListM *L) {
    void *p;
    int size;
    tItemM i;
    if (nargs == 1) ImprimirListaM(0, *L);
    else if (nargs == 2) {
        if (strcmp(command[1], "-free") == 0) ImprimirListaM(0, *L);
        else {
            size = atoi(command[1]);
            p = malloc(size);
            if (p != NULL) {
                createItem(&i, p, size, 0);
                insertDataM(i, L);
                printf("Asignados %dB a %p\n", size, p);
            } else perror("No se pudo reservar la memoria\n");
        }
    } else if (nargs == 3 && strcmp(command[1], "-free") == 0) {
        size = atoi(command[2]);
        tPosM pos = findDataM(size, *L);
        if (pos != NULL) {
            printf("Liberados %dB %p\n", size, pos->data.address);
            free(pos->data.address);
            deleteAtPosM(pos, L);
        } else printf("No se encontraron bloques de tamaño %s\n", command[2]);
    }
}

void myShared(char **command, int nargs, tListM *L) {

    if (nargs == 1 || nargs == 2) ImprimirListaM(1, *L);
    else if (nargs >2) {
        if (strcmp(command[1], "-free") == 0){
            SharedFree(command,L);
        }
        else if (strcmp(command[1], "-create") == 0) {
            SharedCreate(command,L);
        } else if (strcmp(command[1], "-delkey") == 0) {
            SharedDelkey(command,L);
        } else ImprimirListaM(1, *L);
    }
}

 void FreeMmap(char ** command,tListM *L){
    tItemM i;
    tPosM p;
    if((p=findFich(command[2],*L))!=MNULL){
        i = getDataM(p,*L);
        if(munmap(i.address,i.size)!=0) perror("");
        else deleteAtPosM(p,L);
    }
    else printf("Fichero %s no mapeado\n",command[2]);
}

void myMmap(char **command, int nargs, tListM *L) {
    if(nargs==3){
        if(strcmp(command[1], "-free")==0) FreeMmap(command, L);
        else CmdMmap(command,L);
    }
    else ImprimirListaM(2,*L);
}

void myRead(char *ar[]) {
    void *p;
    size_t cont = -1;  /* -1 indica leer todo el fichero*/
    ssize_t n;
    if (ar[1] == NULL || ar[2] == NULL) {
        printf("faltan parametros\n");
        return;
    }
    p = cadtop(ar[2]);  /*convertimos de cadena a puntero*/
    if (ar[3] != NULL)
        cont = (size_t) atoll(ar[2]);

    if ((n = LeerFichero(ar[1], p, cont)) == -1)
        perror("Imposible leer fichero");
    else
        printf("leidos %lld bytes de %s en %p\n", (long long) n, ar[1], p);
}

void myWrite(char **command, int nargs, tListM L) {
    int ow = 0;
    char *fich, *add;
    if (nargs > 3) {
        fich = command[1];
        if (strcmp(fich, "-o") == 0) {
            fich = command[2];
            ow = 1;
        }
        add = command[2 + ow];
        if (findDir(cadtop(add), L) != MNULL) EscribirFichero(fich, cadtop(command[2 + ow]), atoi(command[3 + ow]), ow);
        else perror("Direccion de memoria o fichero o valido");
    }
}

void VolcarMemoria(void *p, int cont) {
    unsigned char *arr = (unsigned char *) p;
    int i, j;
    int cnt = 0;

    for (i = 0; i < cont; i++) {
        printf("  %c %s", arr[i], (i != 0 && i % 10 == 0) ? "\n" : "");
        if (i != 0 && i % 10 == 0 && cnt < cont) {
            for (j = 0; j <= 10; j++) {
                printf(" %02hhx %s", arr[j + cnt], (j != 0 && j % 10 == 0) ? "\n" : "");
            }
            cnt += 10;
        }
    }
    printf("\n");

    printf("\n");
}

void Memdump(char **command, int nargs, tListM L) {
    tPosM p;
    tItemM i;
    if (nargs == 2) {
        if ((p = findDir(cadtop(command[1]), L)) != MNULL) {
            i = getDataM(p, L);
            VolcarMemoria(i.address, 30);
        }else perror("");
    } else if (nargs == 3) VolcarMemoria(cadtop(command[1]), atoi(command[2]));
}

void Memfill(char **command, int nargs, tListM L) {
    tPosM p;
    int size, aux;
    unsigned char letra = 'A';
    if (nargs == 4) {
        size = atoi(command[2]);
        if ((p = findDir(cadtop(command[1]), L)) != MNULL) {
            aux = atoi(command[3]);
            if (0 <= aux && aux < 10) letra = *command[3];
            else letra = (unsigned char) atoi(command[3]);
            printf("Llenando %d B de %p con %c (%02hhx) a partir de %s\n", size, p->data.address, letra, letra,
                   command[1]);
            LlenarMemoria(p->data.address, size, letra);
        }
    }
}

void Recursive(char **command, int nargs) {
    if (nargs == 2) {
        Recursiva(atoi(command[1]));
    }
}


/*Variables globales para el mem :))) Patri pon un 10*/
tListM lista;
int acaba;
char memy;


void mem(char **command, int nargs, tListM L){
    int l1, l2, l3;
    static float s1, s2, s3;
    if(nargs == 1 || strcmp(command[1], "-all") == 0){
        printf("Variables locales:   %18p, %18p, %18p\n", &l1, &l2, &l3);
        printf("Variables globales:  %18p, %18p, %18p\n", &lista, &memy, &acaba);
        printf("Variables estaticas: %18p, %18p, %18p\n", &s1, &s2, &s3);
        printf("Funciones programa:  %18p, %18p, %18p\n", myMalloc, Memfill, Recursive);
        printf("Funciones libreria:  %18p, %18p, %18p\n", getpid, scanf, strcmp);
        
        ImprimirListaM(0,L);
        ImprimirListaM(1,L);
        ImprimirListaM(2,L);
    }
    else{
        if(strcmp(command[1], "-blocks") == 0){

        ImprimirListaM(0,L);
        ImprimirListaM(1,L);
        ImprimirListaM(2,L);
        }
        else if(strcmp(command[1], "-funcs") == 0){
            printf("Funciones programa:  %18p, %18p, %18p\n", myMalloc, Memfill, Recursive);
            printf("Funciones libreria:  %18p, %18p, %18p\n", getpid, scanf, strcmp);
        }
        else if(strcmp(command[1], "-vars") == 0){
            printf("Variables locales:   %18p, %18p, %18p\n", &l1, &l2, &l3);
            printf("Variables globales:  %18p, %18p, %18p\n", &lista, &memy, &acaba);
            printf("Variables estaticas: %18p, %18p, %18p\n", &s1, &s2, &s3);
        }
        else if(strcmp(command[1], "-pmap") == 0){
            Do_MemPmap();
        }
        else{
            printf("Opción %s no contemplada\n", command[1]);
        }
    }
}

///Funciones Auxiliares
void *cadtop(char *cadena) {
    void *p;
    p = (void *) strtoull(cadena, NULL, 16);
    return p;
}

void getHora(char *hora) {
    time_t t;
    struct tm *tim;
    time(&t);
    tim = localtime(&t);
    snprintf(hora, sizeof(char) * 100, "%d-%d %d:%d:%d  ", tim->tm_mon, tim->tm_mday, tim->tm_hour, tim->tm_min,
             tim->tm_sec);
}

void createItem(tItemM *i, void *p, int size, int type) {
    getHora(i->reservation);
    i->address = p;
    i->type = type;
    i->size = size;
}

void ImprimirListaM(int modo, tListM L) {
    tPosM p;
    tItemM info;
    if (modo == 0)printf("******Lista de bloques asignados por malloc para el proceso %d\n", getpid());
    else if (modo == 1)printf("******Lista de bloques asignados por shared para el proceso %d\n", getpid());
    else if (modo == 2)printf("******Lista de bloques asignados por mmap para el proceso %d\n", getpid());

    for (p = firstM(L); p != NULL; p = nextM(p, L)) {
        info = getDataM(p, L);
        if (info.type == 0) printf("\t%p\t\t%dB %s\n", info.address, info.size, info.reservation);
        else if (info.type == 1)
            printf("\t%p\t\t%dB %s (key %d)\n", info.address, info.size, info.reservation, info.key);
        else if (info.type == 2)
            printf("\t%p\t\t%dB %s %s(descriptor %d)\n", info.address, info.size, info.reservation, info.name, info.df);
    }
}

void SharedFree(char ** command,tListM *L){
    tPosM position;
    int SKey = atoi(command[2]);
    if((position=findKey(SKey,*L))!=MNULL){
        deleteAtPosM(position, L);
    }else{
        printf("No hay bloqye de esa clave mapeado en el proceso\n");
    }
}

///Codigo Ayuda
void Recursiva(int n) {
    char automatico[TAMANO];
    static char estatico[TAMANO];

    printf("parametro:%3d(%p) array %p, arr estatico %p\n", n, &n, automatico, estatico);

    if (n > 0)
        Recursiva(n - 1);
}

void LlenarMemoria(void *p, size_t cont, unsigned char byte) {
    unsigned char *arr = (unsigned char *) p;
    size_t i;

    for (i = 0; i < cont; i++)
        arr[i] = byte;
}

void *ObtenerMemoriaShmget(key_t clave, size_t tam,tListM * L) {
    void *p;
    int aux, id, flags = 0777;
    struct shmid_ds s;
    tItemM i;

    if (tam)     /*tam distito de 0 indica crear */
        flags = flags | IPC_CREAT | IPC_EXCL;
    if (clave == IPC_PRIVATE)  /*no nos vale*/
    {
        errno = EINVAL;
        return NULL;
    }
    if ((id = shmget(clave, tam, flags)) == -1)
        return (NULL);
    if ((p = shmat(id, NULL, 0)) == (void *) -1) {
        aux = errno;
        if (tam)
            shmctl(id, IPC_RMID, NULL);
        errno = aux;
        return (NULL);
    }
    shmctl(id, IPC_STAT, &s);
    i.key = clave;
    createItem(&i,p,tam,1);
    insertDataM(i,L);
    /** Guardar en la lista, p.e.  InsertarNodoShared (&L, p, s.shm_segsz, clave); */
    return (p);
}

void SharedCreate(char *tr[],tListM *L) {
    key_t cl;
    size_t tam;
    void *p;

    if (tr[2] == NULL || tr[3] == NULL) {
        ImprimirListaM(1,*L);
        return;
    }

    cl = (key_t) strtoul(tr[2], NULL, 10);
    tam = (size_t) strtoul(tr[3], NULL, 10);
    if (tam == 0) {
        printf("No se asignan bloques de 0 bytes\n");
        return;
    }
    if ((p = ObtenerMemoriaShmget(cl, tam,L)) != NULL) {

        printf("Asignados %lu bytes en %p\n", (unsigned long) tam, p);
    }
    else
        printf("Imposible asignar memoria compartida clave %lu:%s\n", (unsigned long) cl, strerror(errno));
}

void *MapearFichero(char *fichero, int protection, tListM *L) {
    int df, map = MAP_PRIVATE, modo = O_RDONLY;
    struct stat s;
    void *p;
    tItemM i;
    if (protection & PROT_WRITE)
        modo = O_RDWR;
    if (stat(fichero, &s) == -1 || (df = open(fichero, modo)) == -1) {
        return NULL;
    }
    if ((p = mmap(NULL, s.st_size, protection, map, df, 0)) == MAP_FAILED){
        return NULL;
    }

    createItem(&i, p, s.st_size, 2);
    i.df = df;
    strcpy(i.name, fichero);
    getHora(i.reservation);
    insertDataM(i, L);

    return p;
}

void CmdMmap(char *arg[], tListM *L) {
    char *perm;
    void *p;
    int protection = 0;
    if ((perm = arg[2]) != NULL && strlen(perm) < 4) {
        printf("Strleng %lu\n",strlen(perm) );
        printf("%c %c %c\n",perm[0],perm[1],perm[2]);
        if (strchr(perm, 'r') != NULL) protection |= PROT_READ;
        if (strchr(perm, 'w') != NULL) protection |= PROT_WRITE;
        if (strchr(perm, 'x') != NULL) protection |= PROT_EXEC;
    }
    if ((p = MapearFichero(arg[1], protection, L)) == NULL) perror("Imposible mapear fichero");
    else printf("fichero %s mapeado en %p\n", arg[1], p);
}

void SharedDelkey(char *args[],tListM *L) {
    key_t clave;
    int id;
    char *key = args[2];

    if (key == NULL || (clave = (key_t) strtoul(key, NULL, 10)) == IPC_PRIVATE) {
        printf("      delkey necesita clave_valida\n");
        return;
    }
    if ((id = shmget(clave, 0, 0666)) == -1) {
        perror("shmget: imposible obtener memoria compartida");
        return;
    }
    if (shmctl(id, IPC_RMID, NULL) == -1)
        perror("shmctl: imposible eliminar id de memoria compartida\n");
}

ssize_t EscribirFichero(char *f, void *p, size_t cont, int overwrite) {
    ssize_t n;
    int df, aux, flags = O_CREAT | O_EXCL | O_WRONLY;

    if (overwrite)
        flags = O_CREAT | O_WRONLY | O_TRUNC;

    if ((df = open(f, flags, 0777)) == -1)
        return -1;

    if ((n = write(df, p, cont)) == -1) {
        aux = errno;
        close(df);
        errno = aux;
        return -1;
    }
    close(df);
    return n;
}

ssize_t LeerFichero(char *f, void *p, size_t cont) {
    struct stat s;
    ssize_t n;
    int df, aux;

    if (stat(f, &s) == -1 || (df = open(f, O_RDONLY)) == -1)
        return -1;
    if (cont == -1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont = s.st_size;
    if ((n = read(df, p, cont)) == -1) {
        aux = errno;
        close(df);
        errno = aux;
        return -1;
    }
    close(df);
    return n;
}


void Do_MemPmap(void) /*sin argumentos*/{
    pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
    char elpid[32];
    char *argv[4] = {"pmap", elpid, NULL};

    sprintf(elpid, "%d", (int) getpid());
    if ((pid = fork()) == -1) {
        perror("Imposible crear proceso");
        return;
    }
    if (pid == 0) { /*proceso hijo*/
        if (execvp(argv[0], argv) == -1)
            perror("cannot execute pmap (linux, solaris)");

        argv[0] = "vmmap";
        argv[1] = "-interleave";
        argv[2] = elpid;
        argv[3] = NULL;
        if (execvp(argv[0], argv) == -1) /*probamos vmmap Mac-OS*/
            perror("cannot execute vmmap (Mac-OS)");

        argv[0] = "procstat";
        argv[1] = "vm";
        argv[2] = elpid;
        argv[3] = NULL;
        if (execvp(argv[0], argv) == -1)/*No hay pmap, probamos procstat FreeBSD */
            perror("cannot execute procstat (FreeBSD)");

        argv[0] = "procmap", argv[1] = elpid;
        argv[2] = NULL;
        if (execvp(argv[0], argv) == -1)  /*probamos procmap OpenBSD*/
            perror("cannot execute procmap (OpenBSD)");

        exit(1);
    }
    waitpid(pid, NULL, 0);
}