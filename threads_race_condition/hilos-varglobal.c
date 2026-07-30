#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void mifuncion(int *numero);

int VARIABLE_GLOBAL;

int main(void) {

	int i;
	int hilos = 3;
	VARIABLE_GLOBAL = 0;

	pthread_t thread[hilos];
	int tid[hilos];

	for (i = 0; i < hilos; i++) {
		tid[i] = i+1;
		pthread_create(&thread[i], NULL, (void*) mifuncion, &tid[i]);
	}

	// Espero finalizacion de todos los hilos para continuar
	for (i = 0; i < hilos; i++) {
		pthread_join(thread[i], NULL);
	}

	printf("\n\n Main: Terminaron todos los hilos\n\tVARIABLE_GLOBAL: %d\n\n", VARIABLE_GLOBAL);

	return EXIT_SUCCESS;
}

void mifuncion(int *numero) {
	int i, aux;

	for (i = 0; i < 10000; i++) {

		VARIABLE_GLOBAL++;
		printf("Hilo %d - VARIABLE_GLOBAL: %d\n", *numero, VARIABLE_GLOBAL);
		fflush(stdout);
	}

	printf("Hilo %d - %d TERMINE!\n\n", *numero, i);

	fflush(stdout);
}
