Memory Stack 
===============
Entendimiento del funcionamiento del Stack a traves de una super hackeada.


Se tiene un programa que permite visualizar el contenido de los "próximos parciales" a tomar. Para acceder al sistema se requiere de una contraseña, la cual se puede descubrir fácilmente mirando el código fuente.


###### Para compilar
`gcc parciales.c -o parciales -fno-stack-protector -fsyntax-only`



###### Pasos a seguir

1. Compilar el programa
2. Encontrar una forma de acceder a los parciales sin tipear la contraseña correcta
3. Sentirse Carlin Calvo en "El hacker"

###### Ayudas
1. La cuestion consiste en ingresar otra contraseña, que permita tomar provecho de una vulnerabilidad de memoria que se encuentra presente en este programa
2. Compile nuevamente pero sin el parametro `-fsyntax-only`

- ¿Que significa el parametro `-fno-stack-protector`? Compile sin dicho parametro y repita el hackeo
