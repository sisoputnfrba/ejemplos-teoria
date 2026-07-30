# Ejercicio:

­Dado un sistema con N procesos del mismo programa, sincronice su código mediante semáforos para respetar los siguientes límites:

- A) 3 recursos con M instancias
- B) M recursos con 3 instancias

```C
programa() {
    while (TRUE){
        id_recurso = pedir_recurso();
        usar_recurso(id_recurso);
    }
}
```

Para compilar el ejercicio, utilizar el siguiente comando:

```
gcc main.c -o main.out -lpthread
```
