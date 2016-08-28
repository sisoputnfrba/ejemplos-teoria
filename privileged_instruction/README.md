Privileged Instructions 
===============
Verificación de la imposibilidad de parte de un proceso comun, que corre en modo usuario, de poder ejecutar una instruccion privilegiada

El programa intenta ejecutar una instruccion privilegiada. Dado que no es posible a traves del lenguaje C de alto nivel realizar una llamada a una instruccion de asembler, el programa utiliza la keyword propia del compilador gcc `__asm__` [mas info aca](https://gcc.gnu.org/onlinedocs/gcc/Using-Assembly-Language-with-C.html#Using-Assembly-Language-with-C) para lograr insertar en el binario compilado una llamada directa a una instruccion deseada, la cual es privilegiada.


###### Para compilar
`gcc -g execute_privileged_instruction.c`


###### Pasos a seguir
* Abrir el codigo fuente para ver cual instruccion privilegiada se intentará ejecutar (averiguar que hace dicha instruccion). Ignorar temporalmente la funcion sig_handler() y llamada comentada a la función signal()
* Ejecutar el programa: `./a.out`
* Analizar el comportamiento ocurrido
* Validar que el programa compilado efectivamente tiene la instrucción deseada. Para ello, decompilar el programa con el comando: `objdump -d a.out` y luego analizar el assembler de la seccion correspondiente a la función main() (si la salida es muy larga, ejecute  `objdump -d a.out | less` para navegar el resultado usando las teclas arriba/abajo)
* Una vez encontrada la instrucción, salga de la vista tipeando "q"


###### Preguntas
* ¿Que comportamiento tuvo linux al encontrarse con un proceso que intento ejecutar una instrucción privilegiada?
* Descomente la llamada a la funcion signal(), para que el proceso capture la señal y ejecute el comportamiento indicado en sig_gandler(). Compile y ejecute el código (deberia llamar a la funcion, y luego finalizar el programa). Modifique el programa para que la funcion sig_handler() no llame a exit(), compile, vuelva a ejecutar y analice el comportamiento del programa.
