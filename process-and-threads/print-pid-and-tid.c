/*
 * print-pid-and-tid.c
 *
 * Forkea un proceso y lanza dos hilos por cada uno, imprime PID, Parent PId, y TID de cada uno.
 *
 * Compilar con: gcc -o print-pid-and-tid main.c -lpthread
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void* printData();
void* printDataAndWait();

int main(int argc, char** argv){

	int pid = fork();
	pthread_t t1, t2;

	if (pid == 0){ // HIJO
		printData();
		pthread_create(&t1, NULL, printDataAndWait, NULL);
		pthread_create(&t2, NULL, printDataAndWait, NULL);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	}else if (pid > 0){ // PADRE
		printData();
		pthread_create(&t1, NULL, printDataAndWait, NULL);
		pthread_create(&t2, NULL, printDataAndWait, NULL);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		waitpid(pid, NULL, 0);
	} else { //Error
		perror("forkeando");
	}

	return EXIT_SUCCESS;
}

void* printDataAndWait(){

	printData();

	sleep(120);

	return EXIT_SUCCESS;
}

void* printData(){

	pid_t pid, parent_pid, tid;

	pid = getpid();
	parent_pid = getppid();
	tid = syscall(SYS_gettid);

	printf("PID: %d\nPARENT PID: %d\nTID: %d\n\n", pid, parent_pid, tid);

	return EXIT_SUCCESS;
}
