#include <stdio.h>
#include <string.h>
void gets(char * buffer);



void main(void) {
	char logueado = 'N';
	char password[7];


	printf("\nIngrese el password para acceder al repositorio de parciales: ");
	gets(password);

	if(!strcmp(password, "zungri")) {
		logueado = 'S';
	}

	printf("\nVariable 'logueado':\n\tDireccion de memoria: %p\n\tValor: '%c'", &logueado, logueado);
	printf("\nVariable 'password':\n\tDireccion de memoria: %p\n\tValor: %s\n\n", password, password);


	if(logueado == 'S') {
		printf("***** Bienvenido al sistema! *****");
		printf("\n\t- 1er parcial.doc: Error al leer el contenido.");
		printf("\n\t- 2do parcial.doc: Error al leer el contenido.\n");
	} else {
		printf("***** El password ingresado es invalido *****\n");
	}
	fflush(0);
}

