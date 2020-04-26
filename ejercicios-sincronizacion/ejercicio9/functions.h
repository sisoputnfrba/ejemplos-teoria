#include <sys/types.h>
#include <sys/syscall.h>
#include <semaphore.h>
#include "global_variables.h"

int actual()
{
    int i = 0;
    while (i < CANTIDAD_JUGADORES)
    {
        sem_wait(&semaforo_lista_jugadores);
        if (semaforos_jugadores[i].id_jugador == (int)syscall(__NR_gettid))
        {
            sem_post(&semaforo_lista_jugadores);
            return i;
        }
        sem_post(&semaforo_lista_jugadores);
        i++;
    }
}

int siguiente(int id_actual)
{
    return (id_actual + 1) % CANTIDAD_JUGADORES;
}

void dar_orden()
{
    printf("%d - El arbitro da la orden de tiro...\n", (int)syscall(__NR_gettid));
    sleep(1);
}

void validar_tiro()
{
    gol = rand() % 2;
}

void posicionarse_jugador()
{
    printf("%d - El jugador se posiciona...\n", (int)syscall(__NR_gettid));
    sleep(1);
}

void posicionarse_arquero()
{
    printf("%d - El arquero se posiciona...\n", (int)syscall(__NR_gettid));
    sleep(1);
}

void patear()
{
    printf("%d - El jugador patea...\n", (int)syscall(__NR_gettid));
    sleep(1);
}

void atajar()
{
    printf("%d - El arquero intentara atajar...\n", (int)syscall(__NR_gettid));
    sleep(1);
}

void festejarGol()
{
    printf("%d - GOLAZO DEL JUGADOR!!!!\n", (int)syscall(__NR_gettid));
    sleep(1);
}

void lamentarAtajada()
{
    printf("%d - El jugador se lamenta la atajada...\n", (int)syscall(__NR_gettid));
    sleep(1);
}

void festejarAtajada()
{
    printf("%d - QUE ATAJADA DEL ARQUERO!!!!\n", (int)syscall(__NR_gettid));
    sleep(1);
}

void lamentarGol()
{
    printf("%d - No pudo atajar semejante tiro....\n", (int)syscall(__NR_gettid));
    sleep(1);
}