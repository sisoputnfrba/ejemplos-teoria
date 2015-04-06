SysCall - Leandro Zungri
===============

Creen un archivo llamado open_syscall.c con el siguiente programa:

```#include <stdio.h>```

```void main(void) { ```

```fopen("open_syscall.c", "r"); ```

```} ```
<br><br>

Compilarlo de la siguiente manera:

```gcc -g -static open_syscall.c -o open_syscall ```
<br><br>

Debuggear el programa con gdb:

```gdb ./open_syscall ```
<br><br>

Una vez dentro del debugger hacer lo siguiente:

* Insertar un breakpoint en la función open():

```break open ```
<br><br>

* Indicar al gdb que imprima, cada vez que alcance un breakpoint, las próximas 10 instrucciones a partir del instruction pointer:

```display/10i $rip```

Si la arquitectura es de 32 bits, reemplazar $rip por $eip)
<br><br>

* Ejecutar el programa:

```run ```
<br><br>

* El breakpoint debería haber sido alcanzado, lo cual nos indica que cuando se invoca a la función fopen() ésta termina llamando a open() (también en la libc). Recuerden que todavía estamos en modo usuario. Lo que ven es el desensamblado de la función open(). Sí, no se entiende nada, hagan un esfuerzo. La función open(), tal como habíamos visto, es un envoltorio/wrapper/"mamushka" de la llamada al sistema.
<br><br>

A partir de ahora vamos a ejecutar instrucción por instrucción hasta llegar a la que finalmente dispara la llamada al sistema. Recuerden que las dos formas más populares de realizar una llamada eran: Mediante la instrucción SYSCALL/SYSENTER o mediante interrupciones (en el caso de Linux se usa la INT 0x80). El mecanismo que se use dependerá principalmente del procesador que tengan. Entonces ahora sí, ejecuten:

```stepi ```


Tantas veces como sea necesario hasta que vean la instrucción SYSCALL o INT 0x80.
<br><br>

Se está a punto de invocar al kernel. Cómo sabe el kernel qué función ejecutar? Esto se indica en el registro rax (o eax en 32 bits):

```info registers ```
<br><br>

Si buscan el valor de rax en el archivo:

```/usr/include/x86_64-linux-gnu/asm/unistd_64.h (Si su sistema es de 64 bits) ```

```/usr/include/i386-linux-gnu/asm/unistd_32.h (Si su sistema es de 32 bits) ```

Van a corroborar que se trata de la función del kernel sys_open.
<br><br>
 
Entonces, qué ocurre al ejecutar fopen()?: Se llama a open() de la libc, la cual dispara la llamada al sistema que hace que se termine ejecutando la función sys_open del kernel. Esto último en modo kernel, por supuesto.

