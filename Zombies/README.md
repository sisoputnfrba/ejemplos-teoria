Zombies - Hernan Erasmo
===============

Lo que pudimos observar:

* Un proceso zombie es aquel que ha finalizado, pero cuyo padre aún no ha leído su estado de salida.
* Ocupa una entrada en la tabla de procesos, pero prácticamente todos los recursos que se le asignaron han sido devueltos al SO.
* Los procesos huérfanos son aquellos que siguen en ejecución al momento de finalizar su padre (básicamente, lo contrario a un proceso zombie)1
* Los huérfanos son heredados por el proceso padre de su padre (su proceso abuelo, para los amigos), que asume la responsabilidad de leer su estado de salida cuando finalicen.
* Ejecutar 'kill' sobre un zombie no hace nada. Es lógico, es complicado matar a un zombie (si no me creen, pregúntenle a Jill Valentine)

¿Cómo podemos reproducir lo que vimos en el proyector?

* Abrimos dos consolas.
* En la primera compilamos y ejecutamos el archivo creando_zombies.c, (gcc /ruta/a/creando_zombies.c -o creando_zombies && ./creando_zombies)
* Cambiamos a la otra y ejecutamos el comando ps -eo pid,ppid,stat,cmd (sin las comillas). (*)
* Cerca del final de la lista vamos a observar que hay un proceso con el valor Z en la tercer columna, lo que indica que está en estado zombie (mas info sobre los estados en el manual de ps, que se invoca con el comando 'man ps')

Cuando ejecutamos ps con la opción 'e' podemos ver todos los procesos del sistema, y la opcion 'o' toma una lista de parámetros y nos muestra sólo esos atributos para cada proceso. En nuestro caso, le indicamos que queremos ver el pid (process id), el ppid (parent process id), stat (el estado del proceso) y cmd (el comando completo que hizo que ese proceso se ejecute). Hay más características que puede mostrar ps, y las pueden ver en el manual del comando (man ps)
