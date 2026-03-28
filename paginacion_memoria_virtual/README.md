# Ejemplo paginación con memoria virtual
Un programa simple que inicializa un par de variables y muestra las direcciones virtuales en las que se encuentran, la página correspondiente a esa dirección y el frame correspondiente a esa página.

## Output esperado
```sh
$ sudo ./32

PID: 39381

La memoria física está dividida en 4.074.737 frames de 4.096 (2^12) bytes cada uno.

Variable en el stack                  :	0xffb74cb0 (0xffb74000 + 0xcb0)		página 1.047.412  ->  frame 3.976.206 (0x3cac0e)
(...)
'Makefile' mapeado a memoria (read)   :	0xf7f5a000 (0xf7f5a000 + 0x0)		página 1.015.642  ->  frame 3.950.442 (0x3c476a)
'Makefile' mapeado a memoria (r+w)    :	0xf7f59000 (0xf7f59000 + 0x0)		página 1.015.641  ->  frame 3.950.442 (0x3c476a)
Función de librería compartida        :	0xf7d4db80 (0xf7d4d000 + 0xb80)		página 1.015.117  ->  frame 1.690.976 (0x19cd60)
(...)
Variable en la heap                   :	0x56a17ef0 (0x56a17000 + 0xef0)		página 354.839  ->  frame 3.742.707 (0x391bf3)
Global inicializada                   :	0x565b0060 (0x565b0000 + 0x60)		página 353.712  ->  frame 1.719.627 (0x1a3d4b)
Global no inicializada                :	0x565b007c (0x565b0000 + 0x7c)		página 353.712  ->  frame 1.719.627 (0x1a3d4b)
String literal ("string literal")     :	0x565ae0c6 (0x565ae000 + 0xc6)		página 353.710  ->  frame 2.453.215 (0x256edf)
Función del programa (printPointer)   :	0x565ad9b0 (0x565ad000 + 0x9b0)		página 353.709  ->  frame 3.653.556 (0x37bfb4)
```

## Compilar
Está hecho para linux, debería compilar en cualquier distro más o menos directo, yo lo probé en las VMs de la cátedra. Ejecutar `make` compila dos ejecutables: uno que se llama '32' y otro que se llama '64'. Se pueden compilar por separado con `make 32` y `make 64`. Son el mismo ejecutable, compilado para 32 y 64 bits. Cualquiera de los dos anda en una arquitectura de 64 bits.

Nota: Para compilar la versión de 32 bits (desde una computadora de 64), se necesitan las librerias libc de 32 bits. Sin estas librerías, al compilar nos da este error:
```
/usr/include/features-time64.h:20:10: fatal error: bits/wordsize.h: No such file or directory
   20 | #include <bits/wordsize.h>
```
En ubuntu las librerías se instalan con `sudo apt install build-essential gcc-multilib libc6-dev-i386`.

De todas formas, dejo los dos ejecutables ya compilados para que sea más fácil.

## Ejecutar
La gracia sería ejecutarlo con `sudo`, para poder ver los marcos asignados. Sin los permisos necesarios, solo va a imprimir el número de página. 

El programa tiene una única flag: `--wait` o `-w`, que hace que el programa quede esperando una vez que terminó de imprimir todo. Esto es para probar otras cosas sin que el programa muera inmediatamente.

## Caveats
### 32 bits
Si no están disponibles las librerías de desarrollo para 32 bits en el sistema, el compilador va a dar error cuando se trate de compilar la versión de 32 bits. Igual, en una arquitectura de 64 bits, debería poder compilarse tranquilamente la versión de 64 bits con `make 64`.

### Locale
El programa setea el locale (la configuración regional) `es_AR.UTF-8`, está bueno porque pone los números con puntos y se pueden leer más fácil. Pero es totalmente opcional. 

Para instalar el locale: 
```sh
sudo locale-gen es_AR.UTF-8 
sudo update-locale LANG=es_AR.UTF-8
```

### kptr_restrict
Probando el programa en diferentes distros encontré que hay un parámetro que limita las direcciones que podemos leer con [/proc/{id}/pagemap](https://www.kernel.org/doc/Documentation/vm/pagemap.txt). [/proc/sys/kernel/kptr_restrict](https://docs.kernel.org/admin-guide/sysctl/kernel.html#kptr-restrict) setea restricciones para /proc y otras interfaces.

## Conclusiones
Cosas que noté jugando con el programa

- Si ejecutamos varias veces el programa; el código, la cadena literal, la librería compartida y el archivo mapeado a memoria siempre terminan quedando en el mismo frame. Lo de la librería compartida tiene todo el sentido, lo otro entiendo que es una optimización de Linux, porque son todos segmentos de memoria estáticos.
- La versión de 64 bits en general no comparte ningún frame con la versión de 32 bits. Salvo por el archivo mapeado a memoria.
- Un mismo archivo mapeado a memoria como escritura y como lecto-escritura termina en el mismo frame.
- El offset dentro de una página para una misma variable siempre es el mismo a menos que sea una variable de stack. Pero esos mismos offsets cambian según la distro.
- No sé por qué pasa esto pero probé el programa en xfce y hay veces que la página que contiene la librería compartida no está presente pero en Ubuntu y Arch siempre está presente.

## How?
El tamaño de página se obtiene con [sysconf\(_SC_PAGESIZE\)](https://man7.org/linux/man-pages/man3/sysconf.3.html).

La página dada una dirección virtual se consigue dividiendo la dirección por el tamaño de página.

El frame que corresponde a cada página se obtiene con el archivo [/proc/{id}/pagemap](https://www.kernel.org/doc/Documentation/vm/pagemap.txt). Es una interfaz que expone linux y permite a procesos en modo usuario leer las tablas de páginas.

