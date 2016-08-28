#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void sig_handler(int signo)
{
	if (signo == SIGSEGV){ 
		printf("received SIGSEGV\n");
		exit(-1);
		}
}

int main(void)
{
	//signal(SIGSEGV, sig_handler);

	puts("A punto de ejecutar una instruccion privilegiada...");
	sleep(2);
	__asm__ __volatile__ ("cli");
	puts("Pude ejecutar la instruccion privilegiada?");
	return 0;
}



