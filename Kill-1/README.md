Kill -1 - Adriano
===============

Para compilar en linux ejecutar:
gcc -o <nombre_archivo> <nombre_archivo>.c

Ej: gcc -o dummy dummy.c

En este ejemplo vemos el codigo tipico de un fork (en fork.c). Puede verse un proceso creando un hijo (dummy) y matandolo unos segundos despues. Para correr el codigo, compilamos dummy y fork y corremos fork:

* gcc -o dummy dummy.c
* gcc -o fork fork.c
* ./fork

El resultado es sencillo. La funcion fork devuelve 0 al hijo y un valor >0 al padre en casi todos los casos. El else del final (para valores <0) practicamente no es necesario. Pero que sucederia si el fork devolviera un error (pid = -1) y no hubiesemos contemplado ese escenario? 

Corramos el ejemplo kill.c (no sin antes guardar todos los archivos que tengamos abiertos ;))

* gcc -o kill kill.c
* ./kill
