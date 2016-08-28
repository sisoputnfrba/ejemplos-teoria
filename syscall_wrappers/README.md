SysCall Wapper
===============
Diferenciacion de una syscall de un wrapper (envoltorio) a la hora de solicitar un servicio a sistema operativo

El programa realiza una llamada a una función de la libreria estandar de c para imprimir en pantalla un mensaje. Sin embargo, dado que eso implica escribir en un dispositivo de entrada/salida, si la misma no es una llamada al sistema, deberia en algun momento terminar convocando a alguna otra syscall. Se utilizara el comando `strace` para descubrirlo.

###### Para compilar
`gcc -g hello_world.c`


###### Pasos a seguir
* Ejecutar el programa una vez normalmente para validar su funcionamiento: `./a.out`
* Intentar suponer cuantas llamadas al sistema podria estar realizando este programa
* Investigar brevemente la funcionalidad del comando strace: `man strace`
* Ejecutar nuevamente el programa a traves del comando strace: `strace ./a.out` (analizar el resultado impreso, correspondiente a todas las llamadas al sistema realizadas por dicho programa, comparar con la supocisión inicial)
* Buscar cual llamada al sistema se corresponde con la llamada a la funcion `printf()`
* Investigar un poco la llamada al sistema: `man nombre_llamada_al_sistema`
* Cambiar el programa, llamando directamente a la llamada al sistema en lugar de printf.
* Compilarlo y ejecutarlo a ver si se obtiene el mismo resultado (el comportamiento deberia ser el mismo)
* Correrlo con strace y analizar la salida (deberia ser igual a la original)



###### Preguntas
* ¿Encuentra algo inesperado en relacion al codigo del programa y la cantidad de llamadas al sistema efectivamente ocurridas?
* ¿Que ventajas/desventajas tendria usar pŕintf versus usar directamente la llamada al sistema de linux?
* Seguramente encuentre al menos un llamado a la syscall `brk()`. Investigue su utilidad.
* Analize la ultima llamada al sistema realizada por el programa (probablemente sea `exit_group()`.
