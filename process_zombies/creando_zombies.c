#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(void)
{
	pid_t pid_hijo;

	pid_hijo = fork();

	if(pid_hijo > 0){
		puts("Padre: Empezando a dormir");
		sleep(20);
		puts("Padre: Fin programa");
	} else 
	{
		puts("Hijo: Empezando a dormir");
		sleep(10);
		puts("Hijo: Fin programa");

	}

	return 0;
}
