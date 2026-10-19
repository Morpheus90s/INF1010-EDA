// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

#include <stdio.h>
#include "fila.h"

int main(void)
{
    Fila* fila = fila_cria();
    char operacao, categoria;
    int id;

    int ultimo = 0;
    int entrada = 0; 

    while (scanf(" %c-%d-%c", &operacao, &id, &categoria) == 3)
    {
        entrada = 1; 

        if (operacao == 'i')
        {
            fila_insere(fila, id, categoria);
            ultimo = 0;
        } 
        else if (operacao == 'e')
        {
            fila_remove(fila, id, categoria);
            fila_imprime(fila); 
            ultimo = 1;
        }
    }
    if (entrada && !ultimo)
    {
        fila_imprime(fila);
    }
    fila_libera(fila);
    return 0;
}