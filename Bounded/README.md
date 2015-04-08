Bounded - Adriano
===============

Para compilar en linux ejecutar:
gcc -o <nombre_archivo> <nombre_archivo>.c

Ej: gcc -o bounded bounded.c

En este ejemplo vemos un proceso padre creando un hijo. El padre ejecutara como CPU bound y el hijo como IO bound. Si corremos el programa, y abrimos otra terminal, podremos observar mediante el comando ps -fa que el padre (tip: mirar el PPID - parent pid) tiene un uso muy grande de la CPU (cercano al 99%), mientras que el hijo tiene un consumo minimo.

Si comentamos el sleep que realiza el hijo (usando //linea o /* linea */), veremos que el consumo de CPU aumenta, pero igualmente sigue siendo bajo en comparacion al padre.
