#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int a = 1;
int b = 1;
sem_t semA, semB;

void *proceso2()
{
    int d = 1;
    while (1)
    {
        sleep(1);
        printf("datos en proceso2: a=%d, b=%d, d=%d\n", a, b, d);
        sem_wait(&semA);
        a += d;
        sem_post(&semA);

        d *= d;

        sem_wait(&semB);
        b -= d;
        sem_post(&semB);

        printf("datos en proceso2 finales: a=%d, b=%d, d=%d\n", a, b, d);
    }
    return 0;
}
void *proceso1()
{
    int e = 2;

    while (1)
    {

        sleep(1);
        printf("datos en proceso1: a=%d, b=%d, e=%d\n", a, b, e);
        sem_wait(&semB);
        b *= e;
        sem_post(&semB);

        e = pow(e, e);

        sem_wait(&semA);
        a++;
        sem_post(&semA);

        printf("datos en proceso1 finales: a=%d, b=%d, e=%d\n", a, b, e);
    }
    return 0;
}
int main()
{
    sem_init(&semA, 0, 1);
    sem_init(&semB, 0, 1);

    pthread_t threadProceso1, threadProceso2;
    pthread_create(&threadProceso1, NULL, proceso1, NULL);
    pthread_create(&threadProceso2, NULL, proceso2, NULL);

    pthread_join(threadProceso1, NULL);
    pthread_join(threadProceso2, NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);

    return 0;
}