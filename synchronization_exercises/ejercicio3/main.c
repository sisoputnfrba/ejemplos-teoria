#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

int cantidad_hilos = 6; // cantidad_hilos siendo la N del ejercicio

int variable_compartida = 1;
int impresoras = 3;
sem_t semaforo_impresora, semaforo_variable, semaforo_scanner;

void usar_impresora()
{
    printf("IMP-U: El proceso %d esta utilizando una impresora\n", (int)syscall(__NR_gettid));
    sleep(1);
    printf("IMP-L: El proceso %d va a liberar una impresora\n", (int)syscall(__NR_gettid));
}

void usar_scanner()
{
    printf("SCAN-U: El proceso %d esta utilizando un scanner\n", (int)syscall(__NR_gettid));
    sleep(1);
    printf("SCAN-L: El proceso %d va a liberar un scanner\n", (int)syscall(__NR_gettid));
}

void *proceso_A()
{
    while (1)
    {
        sem_wait(&semaforo_impresora);
        usar_impresora();
        sem_post(&semaforo_impresora);

        sem_wait(&semaforo_variable);
        variable_compartida++;
        sem_post(&semaforo_variable);
    }
    return 0;
}
void *proceso_B()
{
    while (1)
    {
        sem_wait(&semaforo_variable);
        variable_compartida++;
        sem_post(&semaforo_variable);

        sem_wait(&semaforo_scanner);
        usar_scanner();
        sem_post(&semaforo_scanner);
    }
    return 0;
}

void *proceso_C()
{
    while (1)
    {
        sem_wait(&semaforo_scanner);
        usar_scanner();
        sem_post(&semaforo_scanner);

        sem_wait(&semaforo_impresora);
        usar_impresora();
        sem_post(&semaforo_impresora);
    }
    return 0;
}

int main()
{
    sem_init(&semaforo_impresora, 0, 3);
    sem_init(&semaforo_scanner, 0, 2);
    sem_init(&semaforo_variable, 0, 1);

    pthread_t threads_proceso_A[cantidad_hilos], threads_proceso_B[cantidad_hilos], threads_proceso_C[cantidad_hilos];
    int i = 0;
    while (i < cantidad_hilos)
    {
        pthread_create(&threads_proceso_A[i], NULL, proceso_A, NULL);
        pthread_create(&threads_proceso_B[i], NULL, proceso_B, NULL);
        pthread_create(&threads_proceso_C[i], NULL, proceso_C, NULL);
    }

    while (i < cantidad_hilos)
    {
        pthread_join(threads_proceso_A[i], NULL);
        pthread_join(threads_proceso_B[i], NULL);
        pthread_join(threads_proceso_C[i], NULL);
    }

    sem_destroy(&semaforo_impresora);
    sem_destroy(&semaforo_scanner);
    sem_destroy(&semaforo_variable);

    return 0;
}