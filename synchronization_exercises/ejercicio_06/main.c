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
sem_t semaforo_c;
sem_t semaforo_bc;

void * imprimirA(){
	while(1){
		sem_wait(&semaforo_a);

		printf("A \n");

		sem_post(&semaforo_bc);
		sleep(1);
	}
}

void * imprimirB(){
	while(1){
		sem_wait(&semaforo_b);
		sem_wait(&semaforo_bc);

		printf("B \n");

		sem_post(&semaforo_a);
		sem_post(&semaforo_c);

		sleep(1);
	}
}

void * imprimirC(){
	while(1){
		sem_wait(&semaforo_c);
		sem_wait(&semaforo_bc);

		printf("C \n");

		sem_post(&semaforo_b);
		sem_post(&semaforo_a);

		sleep(1);
	}
}

int main(void){

	sem_init(&semaforo_a, 0, 0);
	sem_init(&semaforo_b, 0, 1);
	sem_init(&semaforo_c, 0, 0);
	sem_init(&semaforo_bc, 0, 1);

	pthread_t hiloA;
	pthread_t hiloB;
	pthread_t hiloC;

	pthread_create(&hiloA, NULL, imprimirA, NULL);
	pthread_create(&hiloB, NULL, imprimirB, NULL);
	pthread_create(&hiloC, NULL, imprimirC, NULL);

	pthread_join(hiloA, NULL);
	pthread_join(hiloB, NULL);
	pthread_join(hiloC, NULL);

	return 0;
}
