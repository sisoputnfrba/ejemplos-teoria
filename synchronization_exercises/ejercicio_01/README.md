# Ejercicio:

Dados los siguientes procesos con variables compartidas, sincronizarlos para garantizar la mutua exclusión sobre ellas:

```C
variables_compartidas a = b = 1;

proceso1 {
    variable_local d = 1;
    while (TRUE){
        a = a + d;
        d = d * d;
        b = b – d;
    }
}

proceso2 {
        variable_local e = 2;
        while (TRUE){
        b = b * e;
        e = e ^ e;
        a++;
    }
}
```

Para compilar el ejercicio, utilizar el siguiente comando:

```
gcc main.c -o main.out -lpthread -lm
```
