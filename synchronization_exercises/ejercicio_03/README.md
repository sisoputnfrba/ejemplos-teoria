# Ejercicio:

Dado un sistema con los siguientes tipos de procesos, sincronice su código mediante semáforos sabiendo que hay tres
impresoras, dos scanners y una variable compartida.

```C
variables_compartidas a = b = 1;

// tiene N instancias
proceso_A {

    While (TRUE) {

        usar_impresora();
        variable_compartida++;

    }
}

// tiene N instancias
proceso_B {

    While (TRUE) {

        variable_compartida++;
        usar_scanner();

    }
}

// tiene N instancias
proceso_C {

    While (TRUE) {

        usar_scanner();
        usar_impresora();

    }
}

```

Para compilar el ejercicio, utilizar el siguiente comando:

```
gcc main.c -o main.out -lpthread
```
