# Ejercicio

Sincronice el siguiente código, correspondiente a un proceso que genera procesos hijos, para evitar inconsistencias,
deadlocks e inanición. Además debe tener en cuenta lo siguiente:

- El archivo donde se escriben los logs es único.
- No debe haber más de 50 procesos en ejecución
- El padre debe escribir en el log antes que el hijo
  recién creado.

```C
int main() {
    while (true) {
        pid = fork();
        if (pid < 0) {
            log(‘Error’);
        } else if (pid == 0) {
            log(“Y yo soy el hijo”);
            realizarTarea();
            // Finaliza el proceso hijo
            exit(0);
        } else { // Padre
            log(pid + “ soy tu padre”);
        }
    }
}
```

Para compilar el ejercicio, utilizar el siguiente comando:

```
gcc main.c -o main.out -lpthread
```
