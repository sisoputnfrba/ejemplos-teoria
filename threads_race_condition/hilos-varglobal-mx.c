#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void mifuncion(int *numero);

int VARIABLE_GLOBAL;
pthread_mutex_t MXVARGLOBAL;

int main(void) {

	int i;
	int hilos = 3;

	pthread_t tid[hilos][2];

	// Inicializo semaforo
	pthread_mutex_init(&MXVARGLOBAL, NULL);

	for (i = 0; i < hilos; i++) {
		tid[i][1] = i+1;

		pthread_create(&tid[i][0], NULL, (void*) mifuncion, &tid[i][1]);
	}

	// Espero finalizacion de todos los hilos para continuar
	for (i = 0; i < hilos; i++) {
		pthread_join(tid[i][0], NULL);
	}

	printf("\n\n Main: Terminaron todos los hilos\n\tVARIABLE_GLOBAL: %d\n\n", VARIABLE_GLOBAL);

	pthread_mutex_destroy(&MXVARGLOBAL);

	return EXIT_SUCCESS;
}

void mifuncion(int *numero) {
	int i;

	for (i = 0; i < 10000; i++) {

		pthread_mutex_lock(&MXVARGLOBAL);

		VARIABLE_GLOBAL++;
		printf("Hilo %d - VARIABLE_GLOBAL: %d\n", *numero, VARIABLE_GLOBAL);
		fflush(stdout);

		pthread_mutex_unlock(&MXVARGLOBAL);
	}

	printf("Hilo %d - %d TERMINE!\n\n", *numero, i);

	fflush(stdout);
}
