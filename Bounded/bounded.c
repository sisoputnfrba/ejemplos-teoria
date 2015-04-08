#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();

    if(pid > 0) 
    {
        while(1);
    }
    else if(pid == 0)
    {
	FILE* fd = 0;
	while(1) {
	    fd = fopen("bounded.c", "r");
	    sleep(1);
	    puts("Soy IO bound");
	    fclose(fd);
	}
    }
    else
    {
        puts("Fallo el fork");
        return 1;
    }


    return 0;
}
