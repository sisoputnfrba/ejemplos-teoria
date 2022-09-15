#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void* pido_recurso_ab();
void* pido_recurso_ba();

sem_t* mutex_recurso_a;
sem_t* mutex_recurso_b;


int main(void){

    pthread_t hilo1;
    pthread_t hilo2;

    mutex_recurso_a = malloc(sizeof(sem_t));
    mutex_recurso_b = malloc(sizeof(sem_t));

    sem_init(mutex_recurso_a, 0, 1);
    sem_init(mutex_recurso_b, 0, 1);

    pthread_create(&hilo1, NULL, pido_recurso_ab, NULL);
    pthread_create(&hilo2, NULL, pido_recurso_ba, NULL);
    
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("Termine!!!!");

    free(mutex_recurso_a);
    free(mutex_recurso_b);


    return 0;
}



void* pido_recurso_ab(){

    

    printf("Thread:1 Estoy por pedir recurso a\n");
    sem_wait(mutex_recurso_a);
    printf("Thread:1 Ya pedi el recurso a \n");

    sleep(1);

    printf("Thread:1 Estoy por pedir recurso b \n");
    sem_wait(mutex_recurso_b);
    printf("Thread:1 Ya pedi el recurso b\n");

    sem_post(mutex_recurso_a);
    sem_post(mutex_recurso_b);

}

void* pido_recurso_ba(){

    printf("Thread:2 Estoy por pedir recurso b \n");
    sem_wait(mutex_recurso_b);
    printf("Thread:2 Ya pedi el recurso b\n");

    sleep(1);

    printf("Thread:2 Estoy por pedir recurso a\n");
    sem_wait(mutex_recurso_a);
    printf("Thread:2 Ya pedi el recurso a \n");

    sem_post(mutex_recurso_b);
    sem_post(mutex_recurso_a);

}