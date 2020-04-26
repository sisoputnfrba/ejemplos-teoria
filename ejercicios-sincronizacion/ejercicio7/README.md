# Ejercicio

Suponga que un proceso tiene por tarea compilar un conjunto de programas y luego enviar el
resultado de cada compilación por email al encargado de ese proyecto. Dicho proceso está
organizado de la siguiente manera: N hilos de kernel compilan cada uno un programa distinto, y
luego cada uno de ellos depositan en una lista (compartida para todo el proceso) el resultado;
por otro lado, un hilo de kernel retira los resultados de las compilaciones y manda un email por
cada uno de ellos.

```C
// Estructura compartida
lista_resultados lista

// N instancias
compilador {
    while(1) {
        id_programa = obtener_nuevo_programa();
        r = compilar_programa(id_programa);
        depositar_resultado(r, lista);
    }
}

// 1 instancia
notificador {
    while(1) {
        r2 = retirar_resultado(lista);
        enviar_email(r2);
    }
}
```

Para compilar el ejercicio, utilizar el siguiente comando:

```
gcc main.c -o main.out -lpthread
```
