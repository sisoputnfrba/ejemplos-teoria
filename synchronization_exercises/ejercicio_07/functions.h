#define LIMITE_LISTA 2

typedef struct resultados
{
    int resultado_depositado;
    int resultado;
} resultados;

resultados lista_resultados[LIMITE_LISTA];

int obtener_nuevo_programa()
{
    printf("%d - El compilador esta obteniendo un nuevo programa...\n", (int)syscall(__NR_gettid));
    return (rand() % 100) + 1;
}

int compilar_programa(int id_programa)
{
    printf("%d - El compilador esta compilando el programa %d...\n", (int)syscall(__NR_gettid), id_programa);
    return rand() % id_programa;
}

void depositar_resultado(int resultado, resultados lista_resultados[])
{
    int i = 0;
    while (i < LIMITE_LISTA)
    {
        if (!lista_resultados[i].resultado_depositado)
        {
            lista_resultados[i].resultado_depositado = 1;
            lista_resultados[i].resultado = resultado;

            printf("%d - el compilador deposito el resultado %d en la lista de resultados...\n", (int)syscall(__NR_gettid), resultado);
            return;
        }
        i++;
    }
}

int retirar_resultado(resultados lista_resultados[])
{
    int i = 0;
    while (i < LIMITE_LISTA)
    {
        if (lista_resultados[i].resultado_depositado)
        {
            lista_resultados[i].resultado_depositado = 0;
            printf("%d - el notificador retira el resultado %d...\n", (int)syscall(__NR_gettid), lista_resultados[i].resultado);
            return lista_resultados[i].resultado;
        }
        i++;
    }
}

void enviar_email(int resultado)
{
    printf("%d - el notificador envia mail del resultado %d...\n", (int)syscall(__NR_gettid), resultado);
}