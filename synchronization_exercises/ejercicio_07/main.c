#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "functions.h"
#define INSTANCIAS_COMPILADOR 5

sem_t semaforo_mutex_lista;
sem_t semaforo_hay_resultados;
sem_t semaforo_maximo_en_lista;

void *compilador()
{
    while (1)
    {
        int id_programa = obtener_nuevo_programa();
        int resultado = compilar_programa(id_programa);

        sem_wait(&semaforo_maximo_en_lista);
        sem_wait(&semaforo_mutex_lista);
        depositar_resultado(resultado, lista_resultados);
        sem_post(&semaforo_mutex_lista);
        sem_post(&semaforo_hay_resultados);

        sleep(1);
    }
}

void *notificador()
{
    while (1)
    {
        sem_wait(&semaforo_hay_resultados);
        sem_wait(&semaforo_mutex_lista);
        int resultado = retirar_resultado(lista_resultados);
        sem_post(&semaforo_mutex_lista);
        sem_post(&semaforo_maximo_en_lista);

        enviar_email(resultado);
        sleep(1);
    }
}

int main(void)
{
    sem_init(&semaforo_mutex_lista, 0, 1);
    sem_init(&semaforo_hay_resultados, 0, 0);
    sem_init(&semaforo_maximo_en_lista, 0, LIMITE_LISTA);

    pthread_t hilo_notificador, hilos_compilador[INSTANCIAS_COMPILADOR];

    pthread_create(&hilo_notificador, NULL, notificador, NULL);

    int i = 0;
    while (i < INSTANCIAS_COMPILADOR)
    {
        pthread_create(&hilos_compilador[i], NULL, compilador, NULL);
        i++;
    }

    pthread_join(hilo_notificador, NULL);
    i = 0;
    while (i < INSTANCIAS_COMPILADOR)
    {
        pthread_join(hilos_compilador[i], NULL);
        i++;
    }

    return 0;
}
