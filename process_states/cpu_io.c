#include<stdio.h>
#include <unistd.h>


int main(void){
	puts("Starting program!\n");
	while (1){
		int i = 0;
		printf("Starting i/o...");fflush(stdout);
		for (i = 0;i<1000000;i++){
			printf(".\b");
			//if (i % 100 == 0){ printf("\33[2K\r"); }
			}
		printf("done\n");fflush(stdout);
		printf("Starting sleeping...");fflush(stdout);
		sleep(5);
		printf("done\n");fflush(stdout);
		printf("Starting cpu usage...");fflush(stdout);
		int j = 0;
		int r = 0;
		for (i = 0;i<1000000;i++){
			for (j = 0;j<1000;j++){
				r += 1 + 3 + i + j;
				}
			}
		printf("done\n");fflush(stdout);
		//printf("Starting getchar...");fflush(stdout);
                //getchar();
		//printf("done\n");fflush(stdout);
		sleep(1);
	}

return 0;
}
