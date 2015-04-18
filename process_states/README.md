Process states - Esteban
===============

Para compilar en linux ejecutar:
gcc -o <nombre_archivo> <nombre_archivo>.c

Ej: gcc -o cpu_io cpu_io.c

El programa cpu_io.c realiza alterna su tiempo tareas de cpu de i/o. La idea es ejecutar el programa e ir revisando los diferentes estados por los cuales va pasando el programa en Linux.

1- Compilar el programa
2- Ejecutarlo
3- Abrir otra terminal, ejecutar: "ps f" y observar la columna STAT (Para ejecutar el mismo comando repetidas veces de manera automatica, ejecutar: "watch ps f")
4- Investigar el significado de los estados revisando la pagina del manual ("man ps", seccion "PROCESS STATE CODES")
5. "Frenar" el programa a traves del comando "kill -SIGSTOP pid" (donde pid es el process id del programa en ejecucion)
6- "Continuar" la ejecuion del proceso frenado (investigar como!)
7- Ejecutar el comando para debuguear con gdb: "gdb cpu_io" (y luego tipear "start para iniciar el programa y luego frenarlo en un breakpoint inicial")
8- Corroborar el estado asignado al proceso que esta siendo debugueado  
9- <pendiente>: agregar el caso del proceso zombie
10- <pendiente>: ver el caso de mas procesos running que procesadores (posible justificacion: /proc)
