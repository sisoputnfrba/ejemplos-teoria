Zombies
===============

- Significado del proceso "zombie" en linux

###### Para compilar
`gcc creando_zombies.c`

###### Pasos a seguir
1. Correr `watch ps -efo pid,ppid,stat,pmem,rss,cmd`
2. Correr en otra consola el programa: `./a.out`
3. Revisar el estado de los procesos

###### Preguntas
* ¿Como podemos definir entonces un proceso zombie?
* ¿Ocupa memoria en el sistema? ¿Cuanta?
* ¿Que sucede si se intenta matar al proceso usando el comando `kill`?
