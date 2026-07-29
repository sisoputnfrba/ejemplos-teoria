#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

pthread_mutex_t mutex;

// Funcion para obtener el TID real del sistema operativo
pid_t get_tid(void) {
    return syscall(SYS_gettid);
}

// Lee la prioridad real directamente desde el kernel y la imprime
void imprimir_prioridad_real_kernel(const char *nombre_hilo) {
    pid_t tid = get_tid();
    char path[64];
    char buffer[1024];
    
    // Construye la ruta al archivo de estadisticas de scheduling del hilo actual en procfs
    snprintf(path, sizeof(path), "/proc/self/task/%d/sched", tid);
    
    FILE *f = fopen(path, "r");
    if (f) {
        // Descarta la primer linea (que es la del nombre del programa)
        if (fgets(buffer, sizeof(buffer), f) != NULL) {
            // Recorremos solo las lineas de metricas
            while (fgets(buffer, sizeof(buffer), f) != NULL) {
                // Buscamos la linea que contiene "prio"
                if (strstr(buffer, "prio") != NULL) {
                    printf("  [%s] TID: %d | Kernel sched -> %s", nombre_hilo, tid, buffer);
                    break;
                }
            }
        }
        fclose(f);
    } else {
        // Si procfs no esta montado estandar devuelve la prioridad seteada de posix (pero esta no se actualiza)
        int politica;
        struct sched_param param;
        pthread_getschedparam(pthread_self(), &politica, &param);
        printf("  [%s] TID: %d | Prioridad nominal POSIX: %d\n", nombre_hilo, tid, param.sched_priority);
    }
}

// Hilo de Baja Prioridad
void *hilo_uno(void *arg) {
    pthread_mutex_lock(&mutex); 
    
    imprimir_prioridad_real_kernel("Hilo 1");

    sleep(30); 

    imprimir_prioridad_real_kernel("Hilo 1");

    pthread_mutex_unlock(&mutex);

    imprimir_prioridad_real_kernel("Hilo 1");
    return NULL;
}

// Hilo de Alta Prioridad
void *hilo_dos(void *arg) {
    // Espera corta para que el hilo 1 tome seguro el mutex primero
    usleep(100000); 

    imprimir_prioridad_real_kernel("Hilo 2");

    pthread_mutex_lock(&mutex);

    sleep(3);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

pthread_t primer_hilo, segundo_hilo;

int main() {  
    pthread_attr_t atributos_primero, atributos_segundo;
    pthread_mutexattr_t atributos_mutex;
    struct sched_param parametros;

    // Configura al Mutex para herencia de prioridades
    pthread_mutexattr_init(&atributos_mutex);
    pthread_mutexattr_setprotocol(&atributos_mutex, PTHREAD_PRIO_INHERIT);
    pthread_mutex_init(&mutex, &atributos_mutex); // Inicializamos la variable global
    pthread_mutexattr_destroy(&atributos_mutex);

    // HILO 1, baja prioridad (SCHED_FIFO, Prioridad 10)
    pthread_attr_init(&atributos_primero);
    pthread_attr_setinheritsched(&atributos_primero, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&atributos_primero, SCHED_FIFO);
    parametros.sched_priority = 10;
    pthread_attr_setschedparam(&atributos_primero, &parametros);
    
    pthread_create(&primer_hilo, &atributos_primero, hilo_uno, NULL);
    pthread_attr_destroy(&atributos_primero);

    // HILO 2, alta prioridad (SCHED_FIFO, Prioridad 30)
    pthread_attr_init(&atributos_segundo);
    pthread_attr_setinheritsched(&atributos_segundo, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&atributos_segundo, SCHED_FIFO);
    parametros.sched_priority = 30;
    pthread_attr_setschedparam(&atributos_segundo, &parametros);
    
    pthread_create(&segundo_hilo, &atributos_segundo, hilo_dos, NULL);
    pthread_attr_destroy(&atributos_segundo);

    pthread_join(primer_hilo, NULL);
    pthread_join(segundo_hilo, NULL);

    // Limpieza final
    pthread_mutex_destroy(&mutex);
    return 0;
}
