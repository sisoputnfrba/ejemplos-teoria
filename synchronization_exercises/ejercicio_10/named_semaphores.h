#define PROCESOS_DISPONIBLES 50

/* 
  NOTA: Aca se esta utilizando una variacion de semaphore, llamada
        "named semaphores". Se utiliza esta variacion porque implementa
        por dentro la memoria compartida donde estaran estos semaforos.
        De otra manera, los diferentes procesos no conoceran a los semaforos.
*/
char *semaforo_procesos_disponibles = "semaforo de procesos disponibles";
char *semaforo_log = "semaforo mutex del log";
char *semaforo_logueo_padre = "semaforo padre";
char *semaforo_logueo_hijo = "semaforo hijo";

void realizarTarea()
{
    printf("hijo realizando tarea...\n");
}

/*
    Si se corre de nuevo el programa, hay que desvincular
    los valores de los semaforos utilizados anteriormente. 
*/
void liberar_semaforos()
{
    sem_unlink(semaforo_procesos_disponibles);
    sem_unlink(semaforo_log);
    sem_unlink(semaforo_logueo_padre);
    sem_unlink(semaforo_logueo_hijo);
}

void wait_semaforo(char *nombre_semaforo, int valor_inicial)
{
    sem_t *semaforo_id = sem_open(nombre_semaforo, O_CREAT, 0600, valor_inicial);

    if (semaforo_id == SEM_FAILED)
    {
        printf("ERROR - %d - no se pudo abrir el semaforo %s con sem_open \n", (int)syscall(__NR_gettid), nombre_semaforo);
    }

    sem_wait(semaforo_id);
    sem_close(semaforo_id);
}

void post_semaforo(char *nombre_semaforo, int valor_inicial)
{
    sem_t *semaforo_id = sem_open(nombre_semaforo, O_CREAT, 0600, valor_inicial);

    if (semaforo_id == SEM_FAILED)
    {
        printf("ERROR - %d - no se pudo abrir el semaforo %s con sem_open \n", (int)syscall(__NR_gettid), nombre_semaforo);
    }

    sem_post(semaforo_id);
    sem_close(semaforo_id);
}

void wait_semaforo_procesos_disponibles()
{
    wait_semaforo(semaforo_procesos_disponibles, PROCESOS_DISPONIBLES);
}

void post_semaforo_procesos_disponibles()
{
    post_semaforo(semaforo_procesos_disponibles, PROCESOS_DISPONIBLES);
}

void wait_semaforo_log()
{
    wait_semaforo(semaforo_log, 1);
}

void post_semaforo_log()
{
    post_semaforo(semaforo_log, 1);
}

void wait_semaforo_logueo_padre()
{
    wait_semaforo(semaforo_logueo_padre, 0);
}

void post_semaforo_logueo_padre()
{
    post_semaforo(semaforo_logueo_padre, 0);
}

void wait_semaforo_logueo_hijo()
{
    wait_semaforo(semaforo_logueo_hijo, 1);
}

void post_semaforo_logueo_hijo()
{
    post_semaforo(semaforo_logueo_hijo, 1);
}
