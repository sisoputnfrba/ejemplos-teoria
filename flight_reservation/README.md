# Reserva del último asiento de un avión

Ana y Bruno quieren viajar en el vuelo SO-101. Solo queda el asiento **12A**.
Cada persona hace su reserva desde un hilo distinto. El sistema consulta si el
asiento está libre y, después de procesar la solicitud, confirma la reserva.
¿Qué pasa si ambos consultan antes de que alguno lo ocupe?

Todo es simulado: no hay red, pagos ni base de datos. El estado compartido es
`asiento_disponible`, y cada pasajero guarda si recibió un pasaje.

## Compilar y ejecutar

Se necesita un compilador de C con soporte C11 y pthreads. En Ubuntu,
instalar las herramientas de compilación con:

```sh
sudo apt update
sudo apt install build-essential
```

Luego, desde esta carpeta (los mismos comandos también funcionan en macOS):

```sh
gcc -std=c11 -Wall -Wextra -pedantic -pthread reservas.c -o reservas.out
gcc -std=c11 -Wall -Wextra -pedantic -pthread reservas-mx.c -o reservas-mx.out

./reservas.out
```

Repetir varias veces para observar distintos resultados:

```sh
for i in $(seq 1 10); do ./reservas.out; done
```

Cada solicitud llega después de una demora aleatoria de entre 0 y 200 ms.
Procesar la reserva tarda 70 ms. Estas esperas representan tiempos de llegada
y procesamiento, y hacen más fácil observar distintos entrelazamientos.
**No se sortea el resultado**: depende de cuándo cada hilo consulte y ocupe el
asiento. No se garantiza que aparezcan ambos resultados en una cantidad fija
de ejecuciones; también influye la planificación del sistema operativo.

## La condición de carrera

En `reservas.c`, consultar y reservar son pasos separados:

```c
if (asiento_disponible) {
    // ... procesar la reserva ...
    asiento_disponible = 0;
    pasajero->tiene_pasaje = 1;
}
```

Un orden posible es:

1. Ana consulta el asiento y lo ve libre.
2. Mientras Ana procesa su reserva, Bruno consulta y también lo ve libre.
3. Ana ocupa el asiento y recibe su pasaje.
4. Bruno ocupa el mismo asiento y también recibe su pasaje: no vuelve a consultar.

El resumen en ese caso muestra:

```text
Pasajes emitidos:
  Ana: vuelo SO-101, asiento 12A
  Bruno: vuelo SO-101, asiento 12A
Total: 2 pasaje(s) para un solo asiento.
¡DOBLE RESERVA! Dos personas tienen el mismo asiento.
```

Si una persona termina de reservar antes de que la otra consulte, se emite
un solo pasaje. Que una ejecución termine bien no significa que el código
sea correcto. Además, en ambos casos el asiento termina ocupado: mirar solo
esa variable escondería el error. Por eso mostramos los pasajes emitidos.

### ¿Por qué usar `atomic_int`?

Permite leer o escribir el estado compartido desde distintos hilos sin una
carrera de datos que produzca comportamiento indefinido en C. No hace atómico
el conjunto **consultar → procesar → reservar**: dos hilos todavía pueden leer
que el asiento está libre. Esa es la condición de carrera que queremos mostrar.
No reemplazarlo por un `int` común o por `volatile`.

## La solución con mutex

```sh
./reservas-mx.out
for i in $(seq 1 10); do ./reservas-mx.out; done
diff -u reservas.c reservas-mx.c
```

La segunda versión mantiene la misma simulación y protege con un mutex toda
la operación, desde la consulta hasta la confirmación. Mientras un hilo está
dentro de esa sección crítica, el otro espera. Cuando entra, el asiento ya
está ocupado: se emite un solo pasaje. Puede ganar cualquiera de los dos.

La espera de procesamiento queda dentro de la sección crítica para mantener
el ejemplo simple. No es un diseño de producción para procesar pagos o hacer
llamadas de red mientras se mantiene un mutex.

Para discutir en clase:

1. ¿Alcanza con proteger únicamente `asiento_disponible = 0` con el mutex?
2. ¿Qué sucede si cada hilo usa un mutex diferente?
3. ¿Eliminar la demora de procesamiento corrige el error o dificulta observarlo?
4. ¿Por qué el `pthread_join` del hilo principal no evita la doble reserva?
5. ¿Qué operaciones deben formar parte de la misma sección crítica?
