#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_handler(int signo)
{
	if (signo == SIGSEGV) printf("received SIGSEGV\n");
}

int main(void)
{
	signal(SIGSEGV, sig_handler);
	sleep(5);
	__asm__ __volatile__ ("cli");

	return 0;
}
