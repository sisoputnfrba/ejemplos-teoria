# Ejercicio:

Se tiene un programa para simular la ejecución de penales de un partido de fútbol, el cual consta de tres procesos: árbitro, jugador y arquero.

El pseudo­código es el siguiente:

```C
arbitro {
  while(1) {
    dar_orden();
    validar_tiro();
  }
}

jugador {
  while(1) {
    posicionarse();
    patear();

    if (GOL==TRUE){
    festejar();
    else {
    lamentarse();
  }
}

arquero {
  while(1) {
    posicionarse();
    atajar();

    if (GOL==FALSE){
    festejar();
    else {
    lamentarse();
  }
}
```

Las reglas que se deben cumplir son las siguientes:

- Existen cinco procesos jugadores, un proceso árbitro y un proceso arquero.
- Los jugadores no pueden patear si el árbitro no lo indicó.
- El arquero no puede atajar si el jugador no pateó.
- El árbitro sólo puede dar la orden cuando el jugador y el arquero están posicionados.
- Existe una variable global GOL, la cual es modificada por la función validar_tiro(),que indica si el último penal pateado
  fue gol o no.
- Una vez que se valide el penal, se le pasará el turno al próximo jugador.
- Los jugadores siempre patean en un orden definido (ej: jug1, jug2, …, jug5, jug1, jug2, etc).
- Existe a disposición la función actual() que retorna el id del pateador actual, y la función siguiente() que retorna el id del
  próximo pateador.

Provea una solución que sincronice los tres procesos usando solamente semáforos, asegurándose que se cumplan las
reglas establecidas sin producirse deadlock ni starvation. Se deberá inicializar cada semáforo, indicando también su tipo.

Para compilar el ejercicio, utilizar el siguiente comando:

```
gcc main.c -o main.out -lpthread
```
