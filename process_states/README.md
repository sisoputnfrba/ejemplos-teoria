Process states 
===============
Verificación de los estados que usa linux para los procesos


El programa cpu_io.c alterna su tiempo tareas de cpu de i/o. La idea es ejecutar el programa e ir revisando los diferentes estados por los cuales va pasando el programa.


###### Para compilar
`gcc -g -o cpu_io.out cpu_io.c`


###### Pasos a seguir
1. Compilar el programa
2. Ejecutarlo
3. Abrir otra terminal, ejecutar: "ps f" y observar la columna STAT (Para ejecutar el mismo comando repetidas veces de manera automatica, ejecutar: "watch ps f")
4. Investigar el significado de los estados revisando la pagina del manual ("man ps", seccion "PROCESS STATE CODES")
5. "Frenar" el programa a traves del comando "kill -SIGSTOP pid" (donde pid es el process id del programa en ejecucion)
6. "Continuar" la ejecuion del proceso frenado (Investigar como!)
7. Ejecutar el comando para debuguear con gdb: "gdb cpu_io" (y luego tipear "start para iniciar el programa y luego frenarlo en un breakpoint inicial")
8. Corroborar el estado asignado al proceso que esta siendo debugueado  

###### Preguntas
- ¿Que significa la `s` (minúscula) y el `+` al lado del estado del proceso, en la columna STAT?

```
//TODO agregar el caso del proceso zombie
//TODO ver el caso de mas procesos running que procesadores (posible justificacion: /proc)
```

