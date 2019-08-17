Getdents
===============
Ejemplo de cómo realizar una lectura del directorio con [getdents](http://man7.org/linux/man-pages/man2/getdents.2.html), usando directamente la syscall en vez de usar un wrapper.

###### Para compilar
`gcc getdents.c -o getdents`

Usando `strace` podemos ver qué syscalls ejecuta el proceso.
```
open("dir/", O_RDONLY|O_DIRECTORY)      = 3
getdents(3, /* 3 entries */, 5242880)   = 80
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fd23a32e000
write(1, "..\n", 3..
)                     = 3
write(1, "example\n", 8example
)                = 8
write(1, ".\n", 2.
)                      = 2
getdents(3, /* 0 entries */, 5242880)   = 0
exit_group(0)                           = ?
```