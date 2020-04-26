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
#include <sys/types.h>
#include <sys/syscall.h>

sem_t semaforo_disponible;
sem_t semaforo_pedido;
sem_t semaforo_pistas;
sem_t semaforo_pista_liberada;

pthread_mutex_t mutex_pistas;

int cantidadAviones = 100;
int pistasLibres = 10;

void mantenimiento(){
	printf("%i [Avion] Mantenimiento Realizado \n", (int)syscall(__NR_gettid));
}

void despegar(){
	usleep(1000);
	printf("%i [Avion] Despegue Realizado \n", (int)syscall(__NR_gettid));
}

void volar(){
	sleep(1);
	printf("%i [Avion] Vuelo Realizado \n", (int)syscall(__NR_gettid));
}

void aterrizar(){
	usleep(1000);
	printf("%i [Avion] Aterrizaje Realizado \n", (int)syscall(__NR_gettid));
}

void otorgarUnaPista(){
	printf("%i [Controlador Entrada] Pista Otorgada \n", (int)syscall(__NR_gettid));
}

void liberarUnaPista(){
	printf("%i [Controlador Salida] Pista Liberada \n", (int)syscall(__NR_gettid));
}
void logger(){
	printf("%i [Log] Pistas libres: %i \n",(int)syscall(__NR_gettid),pistasLibres);
}

void * avion(){
	while(1){

		mantenimiento();

		//pedir una pista y esperar
		sem_post(&semaforo_pedido);
		sem_wait(&semaforo_disponible);
		despegar();
		sem_post(&semaforo_pista_liberada);

		volar();

		sem_post(&semaforo_pedido);
		sem_wait(&semaforo_disponible);
		aterrizar();
		sem_post(&semaforo_pista_liberada);


	}
}

void * controladorEntrada(){
	while(1){
		sem_wait(&semaforo_pedido);
		sem_wait(&semaforo_pistas);

		otorgarUnaPista();

		pthread_mutex_lock(&mutex_pistas);
		pistasLibres--;
		pthread_mutex_unlock(&mutex_pistas);

		logger();
		sem_post(&semaforo_disponible);

	}
}

void * controladorSalida(){
	while(1){

		sem_wait(&semaforo_pista_liberada);

		liberarUnaPista();

		pthread_mutex_lock(&mutex_pistas);
		pistasLibres++;
		pthread_mutex_unlock(&mutex_pistas);

		logger();
		sem_post(&semaforo_pistas);

	}
}

void generarAviones() {
	int cantidadAvionesCreados = 0;
	pthread_t hiloAvion;
	while (cantidadAvionesCreados <= cantidadAviones) {
		pthread_create(&hiloAvion, NULL, avion, NULL);
		printf("Cantidad aviones creados: %i|", cantidadAvionesCreados);
		cantidadAvionesCreados++;
	}
}

void generarControladoresAereos() {
	pthread_t hiloControladorEntrada, hiloControladorSalida;
	pthread_create(&hiloControladorEntrada, NULL, controladorEntrada, NULL);
	pthread_create(&hiloControladorSalida, NULL, controladorSalida, NULL);

	// Los joins se agregar para que main no termine.
	pthread_join(hiloControladorEntrada, NULL);
	pthread_join(hiloControladorSalida, NULL);
}

int main(void){

	sem_init(&semaforo_disponible, 0, 0);
	sem_init(&semaforo_pedido, 0, 0);
	sem_init(&semaforo_pistas, 0, 10);
	sem_init(&semaforo_pista_liberada, 0, 0);


	generarAviones(cantidadAviones);
	generarControladoresAereos();
	return 0;
}
