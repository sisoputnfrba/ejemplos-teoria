# Demostración de Herencia de Prioridades en POSIX Threads (PTHREAD_PRIO_INHERIT)

## 1. Descripción del Programa
Este programa en C muestra inversión de prioridades y cómo funciona el protocolo de herencia de prioridades (PTHREAD_PRIO_INHERIT) en semáforos mutex de POSIX (pthread_mutex_t). 

Objetivo: 
- Ilustrar cómo un hilo de baja prioridad que posee un recurso crítico (un mutex) hereda temporalmente la prioridad de un hilo de alta prioridad que se encuentra bloqueado esperando dicho recurso, evitando así que tareas de menor prioridad que el segundo hilo lo retrasen.
- Entender el funcionamiento de la herencia de prioridades de POSIX.

## 2. Comportamiento Esperado y Output
Al ejecutar el programa, se espera lo siguiente:
1. Hilo 1 (Baja Prioridad) adquiere el mutex e imprime su estado inicial, leído de las metricas del kernel.
2. Hilo 1 (Baja Prioridad) espera un largo tiempo.
3. Hilo 2 (Alta Prioridad) muestra su prioridad incial (mayor a la del Hilo 1), intenta adquirir el mismo mutex, pero al estar ocupado, se bloquea y queda en espera.
4. Al bloquearse el Hilo 2, el kernel de Linux aplica automáticamente la herencia de prioridades: el Hilo 1 eleva su prioridad temporalmente para terminar su sección crítica con mayor velocidad. Esto se puede ver en las métricas de planificación internas del kernel expuestas en '/proc', las cuales imprime el programa.
5. Una vez que el Hilo 1 finaliza su trabajo y libera el mutex, la prioridad del Hilo 1 desciende a su valor original, permitiendo que el Hilo 2 adquiera el recurso con éxito y finalice.

## 3. Instrucciones de Compilación y Ejecución
Como el programa utiliza políticas de planificación en tiempo real (SCHED_FIFO), es necesario compilarlo vinculando la biblioteca de hilos (-lpthread) y ejecutarlo con privilegios de superusuario (sudo) para que el sistema operativo permita modificar los parámetros de prioridad.

### Compilación:
```bash
$ gcc priority_inheritance.c -o priority_inheritance -lpthread
```

Ejecución:

```bash
$ sudo ./priority_inheritance
```

## 4. Funciones, Parámetros y Comandos Relevantes

### Funciones de la API POSIX utilizadas:
#### Gestión de Mutexes y sus Atributos:
- ```pthread_mutexattr_init(&atributos_mutex)```: Inicializa la estructura de atributos del mutex.
- ```pthread_mutexattr_setprotocol(&atributos_mutex, PTHREAD_PRIO_INHERIT)```: Configura el protocolo de herencia de prioridades sobre el mutex.
- ```pthread_mutex_init(&mutex, &atributos_mutex)```: Inicializa el mutex utilizando los atributos previamente configurados.
- ```pthread_mutexattr_destroy(&atributos_mutex)```: Libera el objeto de atributos del mutex.
- ```pthread_mutex_lock(&mutex)```: Bloquea (toma) el mutex. Si está ocupado, el hilo llamante se suspende.
- ```pthread_mutex_unlock(&mutex)```: Desbloquea (libera) el mutex para que otros hilos puedan tomarlo.
- ```pthread_mutex_destroy(&mutex)```: Destruye la estructura del mutex y libera sus recursos asociados.

#### Gestión de Hilos y sus Atributos:
- ```pthread_attr_init(&atributos_X)```: Inicializa el objeto de atributos para la creación de hilos.
- ```pthread_attr_setinheritsched(&atributos_X, PTHREAD_EXPLICIT_SCHED)```: Define que el hilo usará explícitamente los atributos de programación especificados y no los del hilo creador.
- ```pthread_attr_setschedpolicy(&atributos_X, SCHED_FIFO)```: Establece la política de planificación en tiempo real (FIFO) para el hilo.
- ```pthread_attr_setschedparam(&atributos_X, &parametros)```: Asigna el valor numérico de prioridad estática a través de la estructura struct sched_param.
- ```pthread_create(...)```: Crea un nuevo hilo de ejecución controlando sus atributos específicos y asignando su función rutina.
- ```pthread_attr_destroy(&atributos_X)```: Libera la estructura de atributos del hilo.
- ```pthread_join(hilo, NULL)```: Bloquea la ejecución del hilo principal hasta que el hilo especificado finalice.
- ```pthread_getschedparam(...)```: Consulta la política y los parámetros de planificación nominales del hilo.
- ```pthread_self()```: Obtiene el identificador (pthread_t) del hilo en ejecución actual.

### Comandos de terminal para corroborar el output:
Además de los mensajes impresos directamente por la consola durante la ejecución, se puede corroborar el estado de los hilos en tiempo real utilizando herramientas nativas de Linux:

1. Listar hilos, políticas y prioridades estáticas de un proceso en ejecución:
``` bash
$ ps -eLo pid,lwp,cls,ni,pri,comm | grep priority_inheritance
```
(Donde la columna 'cls' mostrará 'FF' indicando SCHED_FIFO y 'pri' reflejará el valor de la prioridad estática en el sistema).

2. Monitorear hilos individualmente de forma interactiva como en el TP:
``` bash
$ top -H -p $(pgrep priority_inheritance)
```
(Presionando 'H' en top para alternar la vista detallada por cada hilo creado)

### Demostración OUTPUT:

<img width="798" height="196" alt="Funcionamiento herencia de prioridades" src="https://github.com/user-attachments/assets/28f85b0b-7bf5-49d7-ab4a-3c3862ed8395" />

En la imagen vemos como la prioridad del hilo 1 en el kernel pasa a ser igual a la del hilo 2 (la priroidad se calcula en el sistema operativo como 99 - PRIORIDAD ACTUAL). Posteriormente, luego de liberar el mutex, vuelve a la original.
