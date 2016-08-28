SysCall
===============
Verificación de como el sistema operativo realiza una llamada al sistema

El programa realiza una llamada a una función que abre un archivo, la cual termina llamando a la syscall de linux `open()`. La idea es poder ver las intrucciones de assembler correspondientes con dicho código, para entender cómo se realizan las llamadas al sistema en linux.

###### Para compilar
`gcc -g -static open_syscall.c -o open_syscall`


###### Pasos a seguir
* Debuggear el programa con gdb: `gdb ./open_syscall`
* Insertar un breakpoint en la función open(): `break open`
* Indicar al gdb que imprima, cada vez que alcance un breakpoint, las próximas 10 instrucciones a partir del instruction pointer:`display/10i $rip`
* Ejecutar el programa hasta el próximo breakpoint: `run`
* El breakpoint debería haber sido alcanzado, lo cual nos indica que cuando se invoca a la función fopen() ésta termina llamando a open() (también en la libc). Recuerden que todavía estamos en modo usuario. Lo que ven es el desensamblado de la función open(). Probablemente no se entienda nada, pero si se hace un esfuerzo se debería poder entender que la función open(), es un envoltorio/wrapper de la llamada al sistema.
* Ejecutar instrucción por instrucción hasta llegar a la que dispara la llamada al sistema: `stepi` (repetirlo hasta ver "syscall" o "sysenter").
* Una vez llegado a la instrucción, efectivamente se está a punto de invocar al kernel. ¿Cómo sabe el kernel qué función ejecutar? Esto se indica en el registro rax (o eax en 32 bits):`info registers`
* Si buscan el valor de rax en el archivo:`/usr/include/x86_64-linux-gnu/asm/unistd_64.h` (Si su sistema es de 64 bits) deberían poder corroborar que se trata de la función del kernel sys_open.


¿Por qué la llamada a gcc para compilar el programa recibe el parámetro ```static```?

