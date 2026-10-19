// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

#include <stdio.h>
#include "fila.h"

int main(void) {
    Fila* fila = fila_cria();
    char operacao, categoria;
    int id;
    
    int ultima = 0;
    int leu = 0; 

    while (scanf(" %c-%d-%c", &operacao, &id, &categoria) == 3) {
        leu = 1; 

        if (operacao == 'i') {
            fila_insere(fila, id, categoria);
            ultima = 0;
        } 
        else if (operacao == 'e') {
            fila_remove(fila, id, categoria);
            fila_imprime(fila); 
            ultima = 1;
        }
    }

    if (leu && !ultima) {
        fila_imprime(fila);
    }

    fila_libera(fila);
    return 0;
}