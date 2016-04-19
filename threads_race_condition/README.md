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
4. Correr varias veces el programa hilos-varglobal.out y ver el resultado final de la variable
5. Compare ambos códigos y vea la diferencia
6. Decompile el programa en instrucciones de assembler, usando el comando `objdump -d hilos-varglobal.out | less`
7. Navegue por el codigo assembler usando los cursores, y busque el codigo correspondiente a "mifuncion" (puede buscar texto tipeando `/mifuncion <enter>`
8. Intente encontrar las instrucciones correspondientes a la manipulación de la variable global


