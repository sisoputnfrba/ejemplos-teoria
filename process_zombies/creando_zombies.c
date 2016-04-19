#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid_hijo;

	pid_hijo = fork();

	if(pid_hijo > 0){
		sleep(300);
	}

	return 0;
}
