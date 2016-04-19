/*
 ============================================================================
 Name        : hilos-varlocal.c
 Author      : elyzabeth
 Description : Hilos con variable local.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void mifuncion(int *numero);

int main(void) {

	int i;
	int hilos = 3;
	pthread_t tid[hilos][2];

	for (i = 0; i < hilos; i++) {
		tid[i][1] = i+1;

		pthread_create(&tid[i][0], NULL, (void*) mifuncion, &tid[i][1]);
	}

	// Espero finalizacion de todos los hilos para continuar
	for (i = 0; i < hilos; i++) {
		pthread_join(tid[i][0], NULL);
	}

	printf("\n\n Main: Terminaron todos los hilos\n");
	printf("\n\n Main: Goodbye cruel world!... \nFIN\n\n");

	return EXIT_SUCCESS;
}

void mifuncion(int *numero) {
	int i;

	for (i = 0; i < 10000; i++) {
		printf("Hilo %d - %d\n", *numero, i);
		fflush(stdout);
	}

	printf("Hilo %d - %d TERMINE!\n\n", *numero, i);

	fflush(stdout);
}
