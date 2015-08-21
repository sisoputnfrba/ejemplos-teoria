Compilar con: `gcc -o print-pid-and-tid main.c -lpthread`
Ejecutar con `./print-pid-and-tid`

Al iniciar, crea un nuevo proceso usando `fork()` y ambos procesos imprimen `PID`, `PPID`, y `TID`. Luego los dos crean dos hilos e imprimen por pantalla la misma información.

Con esa info, podes darte cuenta que proceso creó a quien? Y que proceso es dueño de cada hilo?

Comparalo con la informacion que te da el comando `htop`, podes usar `F4` para filtrar por nombre de programa y `F5` para mostrar en forma de arbol.

Hay algo que te suene extraño?
