Playing with Linux Semaphores 
===============

###### Para compilar:
```
gcc sem_ctl.c -lpthread
```
###### Pasos a seguir
1. Compilar el programa
2. Correr `./a.out semaforo1 get_value` (deberia crear un semaforo y leer su valor, inicialmente en 1)
3. Correr el programa pero esta vez enviando la operacion "wait". Verificar que sucede. Repetir la operacion una vez mas. Que sucedio?
4. Correr desde otra terminal el mismo programa con la operacion "post". Verificar que sucedio con el programa anterior.
5. En una tercer terminal, ejecute el comando `watch ./a.out semaforo1 get_value` (esto ejecutara el comando permanentemente). Repita todos los pasos previos y vaya validando como cambia el valor del semaforo
6. Que sucedio con el valor mostrado por la operacion get_value cuando al menos un proceso se encontraba bloqueado? Investigue una forma de averiguar cuantos procesos se encuentran bloqueados en linux por un semaforo (tip: recuerde que los semaforos en linux son archivos)
7. En linux existen los "named semaphores" y los "unnamed sepahores". De cual tipo son los usados en el ejemplo? Cuando convendria usar un tipo o el otro?


