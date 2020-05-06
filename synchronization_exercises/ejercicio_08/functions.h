int pistasLibres = 10;

void mantenimiento()
{
    printf("%i [Avion] Mantenimiento Realizado \n", (int)syscall(__NR_gettid));
}

void despegar()
{
    usleep(1000);
    printf("%i [Avion] Despegue Realizado \n", (int)syscall(__NR_gettid));
}

void volar()
{
    sleep(1);
    printf("%i [Avion] Vuelo Realizado \n", (int)syscall(__NR_gettid));
}

void aterrizar()
{
    usleep(1000);
    printf("%i [Avion] Aterrizaje Realizado \n", (int)syscall(__NR_gettid));
}

void otorgarUnaPista()
{
    printf("%i [Controlador Entrada] Pista Otorgada \n", (int)syscall(__NR_gettid));
}

void liberarUnaPista()
{
    printf("%i [Controlador Salida] Pista Liberada \n", (int)syscall(__NR_gettid));
}
void logger()
{
    printf("%i [Log] Pistas libres: %i \n", (int)syscall(__NR_gettid), pistasLibres);
}