Race Condition 
===============

###### Para compilar:
```
gcc -o hilos-varglobal.out hilos-varglobal.c -lpthread
gcc -o hilos-varglobal-mx.out hilos-varglobal-mx.c -lpthread
```
###### Pasos a seguir
1. Compilar ambos programas
2. Correr varias veces el programa hilos-varglobal.out y ver el resultado final de la variable
3. Segun el código, el valor final de la variable deberia ser siempre 30000. Verifique que no siempre sucede eso
4. Decompile el programa en instrucciones de assembler, usando el comando `objdump -d hilos-varglobal.out | less`
5. Navegue por el codigo assembler usando los cursores, y busque el codigo correspondiente a "mifuncion" (puede buscar texto tipeando `/mifuncion <enter>`
6. Intente encontrar las instrucciones correspondientes a la manipulación de la variable global
7. Correr varias veces el programa hilos-varglobal-mx.out y ver el resultado final de la variable. Verifique que el resultado es siempre el correcto
8. Compare ambos códigos en C vea la diferencia
9. ¿Cual de los dos programas es mas rapido?

