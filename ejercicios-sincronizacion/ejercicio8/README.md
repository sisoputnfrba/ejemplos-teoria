# Ejercicio:

_Mil gracias a [alekrumkamp](https://github.com/alekrumkamp) por haber hecho y resuelto este ejercicio!_

Existe un aeropuerto que se utiliza como base de operaciones de una flota de aviones. Existen muchos aviones, diez
pistas de aterrizaje / despegue y dos controladores aéreos. Cada vez que un avión desea despegar o aterrizar, debe
utilizar una pista. Para ello, la misma es solicitada al controlador de entrada, y luego de ser utilizada se le notifica al
controlador de salida para que vuelva a estar disponible.

Se pide que sincronice el siguiente pseudo­código respetando las reglas establecidas, sin que se produzca deadlock ni
starvation (cuando el avión ya pidió pista). Para ello solamente debe utilizar semáforos, indicando el tipo de los mismos
y sus valores iniciales.

```C
pistasLibres = 10; // variable compartida

AVIÓN {

  while(TRUE) {
    mantenimiento();
    despegar();
    volar();
    aterrizar();
  }

}

CONTROLADOR ENTRADA {

  while(TRUE) {
    otorgarUnaPista();
    pistasLibres();
    log(pistasLibres);
  }

}

CONTROLADOR SALIDA {

  while(TRUE) {
    liberarUnaPista();
    pistasLibres++;
    log(pistasLibres);
  }

}
```

Nota: La función log() imprime por pantalla el valor actual de pistas libres.

Para compilar el ejercicio, utilizar el siguiente comando:

```
gcc main.c -o main.out -lpthread
```
