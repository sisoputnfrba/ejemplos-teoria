Processes and Threads
============================
Diferenciar procesos, procesos padre e hilos en linux.


Al iniciar, el programa crea un nuevo proceso usando `fork()` y ambos procesos imprimen `PID`, `PPID`, y `TID`. Luego el proceso hijo crea dos hilos, los cuales imprimen por pantalla la misma información.

###### Compilar
`gcc  print-pid-and-tid.c -lpthread`


###### Preguntas
* Con esa info, podes darte cuenta que proceso creó a quien? Y que proceso es dueño de cada hilo? Comandos sugeridos para analisis:
* *  `htop`, podes usar `F4` para filtrar por nombre de programa y `F5` para mostrar en forma de arbol.
* * `pstree -p pidProceso`
* Mirar bien los PIDS y TIDs. Investigar como Linux implementa los hilos a nivel kernel.
* Descomentar las lineas de codigo correspondientes al padre luego de realizar la llamada `fork()`, permitiendo que cree otros dos hilos con el mismo comportamiento. Repetir el paso anterior
