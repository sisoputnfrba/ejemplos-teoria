#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "named_semaphores.h"

int main(void)
{
    liberar_semaforos();

    while (1)
    {
        wait_semaforo_procesos_disponibles();
        pid_t pid = fork();
        if (pid < 0)
        {
            wait_semaforo_log();
            printf("Error\n");
            post_semaforo_log();
        }
        else if (pid == 0)
        {
            wait_semaforo_logueo_padre();
            wait_semaforo_log();

            printf("Y yo soy el hijo\n");
            sleep(1);

            post_semaforo_log();
            post_semaforo_logueo_hijo();
            realizarTarea();

            // Finaliza el proceso hijo
            post_semaforo_procesos_disponibles();
            exit(0);
        }
        else
        { // Padre

            wait_semaforo_logueo_hijo();
            wait_semaforo_log();

            printf("%d soy tu padre\n", pid);
            sleep(1);

            post_semaforo_log();
            post_semaforo_logueo_padre();
        }
    }

    return 0;
}
