#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
    pid_t pid = fork();
    if(pid > 0) 
    {
        puts("Soy el padre");
    }
    else if(pid == 0)
    {
	execv("dummy", NULL); // Proceso dummy
    }
    else
    {
        puts("Fallo el fork");
        return 1;
    }

    /* Codigo de nuestro programa */
    sleep(5);
    /* ... */
    /* Haciendo cosas */
    /* ... */

    /* Finalizo el proceso padre */
    puts("Matando al hijo");
    kill(pid, 9);

    return 0;
}
