#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    const char *nombre;
    int demora_llegada_ms;
    int tiene_pasaje;
} Pasajero;

// Es el último asiento del vuelo. Una lectura o escritura individual es
// atómica, pero consultar y reservar siguen siendo DOS operaciones separadas.
atomic_int asiento_disponible = 1;
pthread_mutex_t mutex_reserva = PTHREAD_MUTEX_INITIALIZER;

void esperar_ms(int milisegundos) {
    struct timespec demora = {
        .tv_sec = milisegundos / 1000,
        .tv_nsec = (milisegundos % 1000) * 1000000L
    };
    while (nanosleep(&demora, &demora) == -1 && errno == EINTR) {
        // Si una señal interrumpe la espera, completar el tiempo restante.
    }
}

void verificar_hilo(int error) {
    if (error != 0) {
        fprintf(stderr, "Error de pthread: %s\n", strerror(error));
        exit(EXIT_FAILURE);
    }
}

void *reservar(void *argumento) {
    Pasajero *pasajero = argumento;
    esperar_ms(pasajero->demora_llegada_ms);
    printf("%s solicita el asiento 12A.\n", pasajero->nombre);

    // Protegemos toda la operación: consultar Y ocupar el asiento.
    verificar_hilo(pthread_mutex_lock(&mutex_reserva));
    if (asiento_disponible) {
        printf("%s ve el asiento libre; está procesando la reserva...\n",
               pasajero->nombre);
        esperar_ms(70); // Simula el procesamiento de una reserva.
        asiento_disponible = 0;
        pasajero->tiene_pasaje = 1;
        printf("Reserva confirmada para %s: vuelo SO-101, asiento 12A.\n",
               pasajero->nombre);
    } else {
        printf("%s no puede reservar: el asiento ya está ocupado.\n",
               pasajero->nombre);
    }

    verificar_hilo(pthread_mutex_unlock(&mutex_reserva));
    return NULL;
}

int main(void) {
    struct timespec ahora;
    if (clock_gettime(CLOCK_REALTIME, &ahora) == -1) {
        perror("clock_gettime");
        return EXIT_FAILURE;
    }
    srand((unsigned int)ahora.tv_sec ^ (unsigned int)ahora.tv_nsec);

    // Generamos las demoras antes de crear los hilos: rand no se comparte.
    Pasajero pasajeros[2] = {
        {.nombre = "Ana", .demora_llegada_ms = rand() % 201},
        {.nombre = "Bruno", .demora_llegada_ms = rand() % 201}
    };
    pthread_t hilos[2];

    printf("Vuelo SO-101: queda un solo asiento, el 12A.\n\n");
    for (int i = 0; i < 2; i++) {
        verificar_hilo(pthread_create(&hilos[i], NULL, reservar, &pasajeros[i]));
    }
    for (int i = 0; i < 2; i++) {
        verificar_hilo(pthread_join(hilos[i], NULL));
    }

    // Con los hilos finalizados, mostramos los pasajes que recibió cada uno.
    int pasajes_emitidos = 0;
    printf("\nPasajes emitidos:\n");
    for (int i = 0; i < 2; i++) {
        if (pasajeros[i].tiene_pasaje) {
            printf("  %s: vuelo SO-101, asiento 12A\n", pasajeros[i].nombre);
            pasajes_emitidos++;
        }
    }
    printf("Total: %d pasaje(s) para un solo asiento.\n", pasajes_emitidos);
    if (pasajes_emitidos == 2) {
        printf("¡DOBLE RESERVA! Dos personas tienen el mismo asiento.\n");
    } else {
        printf("Sin doble reserva en esta ejecución.\n");
    }

    verificar_hilo(pthread_mutex_destroy(&mutex_reserva));
    return EXIT_SUCCESS;
}
