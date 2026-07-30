#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define CANTIDAD_RECURSOS 10 // 10 siendo un ejemplo de M
#define CANTIDAD_INSTANCIAS_POR_RECURSO 3
#define CANTIDAD_PROCESOS 100 // 100 siendo un ejemplo de N

sem_t semaforos_recursos[CANTIDAD_RECURSOS];

void inicializar_semaforos()
{
    int i = 0;
    while (i < CANTIDAD_RECURSOS)
    {
        sem_init(&semaforos_recursos[i], 0, CANTIDAD_INSTANCIAS_POR_RECURSO);
        i++;
    }
}

int pedir_recurso()
{
    return rand() % (CANTIDAD_RECURSOS);
}

void usar_recurso(int id_recurso)
{
    printf("%d:  Utilizando recurso %d...\n", (int)syscall(__NR_gettid), id_recurso);
    sleep(1);
    printf("%d:  Liberando proceso %d...\n", (int)syscall(__NR_gettid), id_recurso);
}

void *proceso()
{
    while (1)
    {

        int id_recurso = pedir_recurso();

        sem_wait(&semaforos_recursos[id_recurso]);
        usar_recurso(id_recurso);
        sem_post(&semaforos_recursos[id_recurso]);
    }
}

int main(void)
{
    inicializar_semaforos();

    int i = 0;
    pthread_t hilos_procesos[CANTIDAD_PROCESOS];
    while (i < CANTIDAD_PROCESOS)
    {
        pthread_create(&hilos_procesos[i], NULL, proceso, NULL);
        i++;
    }
    i = 0;
    while (i < CANTIDAD_PROCESOS)
    {
        pthread_join(hilos_procesos[i], NULL);
        i++;
    }

    return 0;
}
