Processes and Threads
============================
Diferenciar procesos, procesos padre e hilos en linux.


Al iniciar, el programa crea un nuevo proceso usando `fork()` y ambos procesos imprimen `PID`, `PPID`, y `TID`. Luego los dos crean dos hilos cada uno e imprimen por pantalla la misma información.

###### Compilar
`gcc  main.c -lpthread`


###### Preguntas
* Con esa info, podes darte cuenta que proceso creó a quien? Y que proceso es dueño de cada hilo? Comandos sugeridos para analisis:
**  comando `htop`, podes usar `F4` para filtrar por nombre de programa y `F5` para mostrar en forma de arbol.
** pstree -p pidProceso
- Hay algo que te suene extraño?
