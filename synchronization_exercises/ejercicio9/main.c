#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include "initializations.h"

void definirse_como_jugador();

void *arbitro()
{
	while (1)
	{
		sem_wait(&semaforo_jugador_posicionado);
		sem_wait(&semaforo_arquero_posicionado);
		dar_orden();
		sem_post(&semaforo_orden);

		sem_wait(&semaforo_fin_penal);
		validar_tiro();
		sem_post(&semaforo_validacion_jugador);
		sem_post(&semaforo_validacion_arquero);
	}
}

void *jugador()
{
	definirse_como_jugador();
	int mi_id = actual();
	while (1)
	{
		sem_wait(&semaforos_jugadores[mi_id].semaforo_jugador);
		posicionarse_jugador();
		sem_post(&semaforo_jugador_posicionado);

		sem_wait(&semaforo_orden);
		patear();
		sem_post(&semaforo_ataje);
		sem_wait(&semaforo_validacion_jugador);
		if (gol)
		{
			festejarGol();
		}
		else
		{
			lamentarAtajada();
		}
		sem_post(&semaforos_jugadores[siguiente(mi_id)].semaforo_jugador);
	}
}

void *arquero()
{
	while (1)
	{

		posicionarse_arquero();
		sem_post(&semaforo_arquero_posicionado);

		sem_wait(&semaforo_ataje);
		atajar();
		sem_post(&semaforo_fin_penal);

		sem_wait(&semaforo_validacion_arquero);
		if (!gol)
		{
			festejarAtajada();
		}
		else
		{
			lamentarGol();
		}
	}
}

void crear_y_esperar_hilos()
{
	pthread_t hilo_arquero, hilo_arbitro, hilos_jugadores[CANTIDAD_JUGADORES];

	pthread_create(&hilo_arquero, NULL, arquero, NULL);
	pthread_create(&hilo_arbitro, NULL, arbitro, NULL);
	int i = 0;
	while (i < CANTIDAD_JUGADORES)
	{
		pthread_create(&hilos_jugadores[i], NULL, jugador, NULL);
		i++;
	}

	pthread_join(hilo_arquero, NULL);
	pthread_join(hilo_arbitro, NULL);

	i = 0;
	while (i < CANTIDAD_JUGADORES)
	{
		pthread_join(hilos_jugadores[i], NULL);
		i++;
	}
	return;
}

int main(void)
{

	inicializar_semaforos();
	inicializar_semaforo_id_jugadores();

	crear_y_esperar_hilos();

	return 0;
}
