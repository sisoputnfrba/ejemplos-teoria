#include <semaphore.h>
#include <sys/types.h>
#include <sys/syscall.h>

void inicializar_semaforo_id_jugadores()
{
    int i = 0;
    while (i < CANTIDAD_JUGADORES)
    {
        semaforos_jugadores[i].id_jugador = -1;
        i++;
    }
    return;
}

void inicializar_semaforos()
{
    sem_init(&semaforo_orden, 0, 0);
    sem_init(&semaforo_ataje, 0, 0);
    sem_init(&semaforo_jugador_posicionado, 0, 0);
    sem_init(&semaforo_arquero_posicionado, 0, 0);
    sem_init(&semaforo_fin_penal, 0, 0);
    sem_init(&semaforo_validacion_tiro, 0, 0);
    sem_init(&semaforo_validacion_jugador, 0, 0);
    sem_init(&semaforo_validacion_arquero, 0, 0);

    /* este semaforo no es necesario en el ejercicio pero si para la implementacion */
    sem_init(&semaforo_lista_jugadores, 0, 1);

    int i = 0;
    while (i < (CANTIDAD_JUGADORES - 1))
    {
        sem_init(&semaforos_jugadores[i].semaforo_jugador, 0, 0);
        i++;
    }
    sem_init(&semaforos_jugadores[CANTIDAD_JUGADORES - 1].semaforo_jugador, 0, 1);
}

void definirse_como_jugador()
{
    int i = 0;
    while (i < CANTIDAD_JUGADORES)
    {
        sem_wait(&semaforo_lista_jugadores);
        if (semaforos_jugadores[i].id_jugador == -1)
        {
            semaforos_jugadores[i].id_jugador = (int)syscall(__NR_gettid);
            sem_post(&semaforo_lista_jugadores);
            return;
        }
        sem_post(&semaforo_lista_jugadores);
        i++;
    }
}