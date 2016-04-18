SysCall
===============

Compilarlo de la siguiente manera:

```gcc -g -static open_syscall.c -o open_syscall ```
<br><br>

Debuggear el programa con gdb:

```gdb ./open_syscall ```
<br><br>

Una vez dentro del debugger hacer lo siguiente:

* Insertar un breakpoint en la función open(): ```break open ```
* Indicar al gdb que imprima, cada vez que alcance un breakpoint, las próximas 10 instrucciones a partir del instruction pointer:```display/10i $rip``` (Si la arquitectura es de 32 bits, reemplazar $rip por $eip)
* Ejecutar el programa:```run ```
* El breakpoint debería haber sido alcanzado, lo cual nos indica que cuando se invoca a la función fopen() ésta termina llamando a open() (también en la libc). Recuerden que todavía estamos en modo usuario. Lo que ven es el desensamblado de la función open(). Probablemente no se entienda nada, pero si se hace un esfuerzo se debería poder entender que la función open(), es un envoltorio/wrapper de la llamada al sistema.
<br><br>
* Ejecutar instrucción por instrucción hasta llegar a la que dispara la llamada al sistema:```stepi ``` (repetirlo hasta ver SYSCALL/INT 0x80/SYSENTER).
* Una vez llegado a la instrucción, efectivamente se está a punto de invocar al kernel. Cómo sabe el kernel qué función ejecutar? Esto se indica en el registro rax (o eax en 32 bits):```info registers ```
* Si buscan el valor de rax en el archivo:```/usr/include/x86_64-linux-gnu/asm/unistd_64.h (Si su sistema es de 64 bits)``` o ```/usr/include/i386-linux-gnu/asm/unistd_32.h (Si su sistema es de 32 bits) ``` deberían poder corroborar que se trata de la función del kernel sys_open.
<br><br>
 
Entonces, qué ocurre al ejecutar fopen()?: Se llama a open() de la libc, la cual dispara la llamada al sistema que hace que se termine ejecutando la función sys_open del kernel. Esto último en modo kernel, por supuesto.

¿Por qué la llamada a gcc para compilar el programa recibe el parámetro ```static```?

