#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/syscall.h>
#define LIMITE_LISTA 2
#define INSTANCIAS_COMPILADOR 5

sem_t semaforo_mutex_lista;
sem_t semaforo_hay_resultados;
sem_t semaforo_maximo_en_lista;

typedef struct resultados
{
    int resultado_depositado;
    int resultado;
} resultados;

resultados lista_resultados[LIMITE_LISTA];

int obtener_nuevo_programa()
{
    printf("%d - El compilador esta obteniendo un nuevo programa...\n", (int)syscall(__NR_gettid));
    return rand();
}

int compilar_programa(int id_programa)
{
    printf("%d - El compilador esta compilando el programa %d...\n", (int)syscall(__NR_gettid), id_programa);
    return rand() % id_programa;
}

void depositar_resultado(int resultado, resultados lista_resultados[])
{
    int i = 0;
    while (i < LIMITE_LISTA)
    {
        if (!lista_resultados[i].resultado_depositado)
        {
            lista_resultados[i].resultado_depositado = 1;
            lista_resultados[i].resultado = resultado;

            printf("%d - el compilador deposito el resultado %d en la lista de resultados...\n", (int)syscall(__NR_gettid), resultado);
            sleep(1);
            return;
        }
        i++;
    }
}

int retirar_resultado(resultados lista_resultados[])
{
    int i = 0;
    while (i < LIMITE_LISTA)
    {
        if (lista_resultados[i].resultado_depositado)
        {
            lista_resultados[i].resultado_depositado = 0;
            printf("%d - el notificador retira el resultado %d...\n", (int)syscall(__NR_gettid), lista_resultados[i].resultado);
            sleep(1);
            return lista_resultados[i].resultado;
        }
        i++;
    }
}

void enviar_email(int resultado)
{
    printf("%d - el notificador envia mail del resultado %d...\n", (int)syscall(__NR_gettid), resultado);
}

/* EJERCICIO */

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
