#define CANTIDAD_JUGADORES 5
#include <semaphore.h>

typedef struct semaforo_id_jugador
{
    int id_jugador;
    sem_t semaforo_jugador;
} semaforo_id_jugador;

int gol = 0;

sem_t semaforo_orden;
sem_t semaforo_ataje;
sem_t semaforo_jugador_posicionado;
sem_t semaforo_arquero_posicionado;
sem_t semaforo_fin_penal;
sem_t semaforo_validacion_tiro;
sem_t semaforo_validacion_jugador;
sem_t semaforo_validacion_arquero;

sem_t semaforo_lista_jugadores;
semaforo_id_jugador semaforos_jugadores[CANTIDAD_JUGADORES];