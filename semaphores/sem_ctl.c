#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int s_open(sem_t** semaphore, char * sem_name);

int main(int argc, char** argv) {
	
	char *sem_name = argv[1];
	char *operation = argv[2];

	if (argc != 2){
		printf("Uso incorrecto\n\tEjemplo: ./a.out un_semaforo get_value|wait|post\n");
		return EXIT_FAILURE;
	}

	sem_t* semaphore;
	int failed = s_open(&semaphore, sem_name);

	if (failed) {
		return EXIT_FAILURE;
	}

	if (!strcmp(operation,"wait")){
		puts("- Doing wait...");
		sem_wait(semaphore);
		puts("- Wait done");
	}
	if (!strcmp(operation,"post")){
		puts("- Doing post...");
		sem_post(semaphore);
		puts("- Post done");
	}

	if (!strcmp(operation,"get_value")){
		puts("- Getting current value...");
		int current_value;
		sem_getvalue(semaphore, &current_value);
		printf("- Current value: %d\n", current_value);
	}

	return EXIT_SUCCESS;
}

int s_open(sem_t** semaphore, char * sem_name){
	// O_CREAT significa "Crear el semaforo si no existe, y si existe abrirlo"
	// S_IRWU significa "Si se crea el semaforo, hacerlo con permisos Read Write eXecute para el propietario del semaforo"
	int initial_value = 1;
	sem_t * openned_semaphore = sem_open(sem_name, O_CREAT, S_IRWXU, initial_value);

	if (openned_semaphore == SEM_FAILED){
		perror("sem_open");
		return -1;
		}
	else {
		printf("Semaphore [%s] openned successfully\n", sem_name);
		*semaphore = openned_semaphore;
		return 0;
	}
}

