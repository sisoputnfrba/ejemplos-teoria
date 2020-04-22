/*
 * main.c
 *
 *  Created on: 18/4/2017
 *      Author: alejandrokrumkamp
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaforo_a;
sem_t semaforo_b;

void *imprimirA()
{
	while (1)
	{

		sem_wait(&semaforo_a);
		printf("A \n");
		sem_post(&semaforo_b);

		sleep(1);
	}
}

void *imprimirB()
{
	while (1)
	{

		sem_wait(&semaforo_b);
		printf("B \n");
		sem_post(&semaforo_a);

		sleep(1);
	}
}

int main(void)
{

	sem_init(&semaforo_a, 0, 1);
	sem_init(&semaforo_b, 0, 0);

	pthread_t hiloA;
	pthread_t hiloB;

	pthread_create(&hiloA, NULL, imprimirA, NULL);
	pthread_create(&hiloB, NULL, imprimirB, NULL);

	pthread_join(hiloA, NULL);
	pthread_join(hiloB, NULL);

	return 0;
}
