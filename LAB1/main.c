#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "pilha.h"

int main(void) {
    char tipo;
    int valor;

    FILE* arq_f = fopen("entrada_fila.txt", "r");
    if (arq_f != NULL) {
        Fila* f = fila_cria();
        while (fscanf(arq_f, " %c", &tipo) != EOF) {
            if (tipo == 'a') {
                fscanf(arq_f, "%d", &valor);
                ARMAZENA(f, valor);
                fila_imprime(f);
            } else if (tipo == 'r') {
                RETIRA(f);
                fila_imprime(f);
            }
        }
        fclose(arq_f); 
        fila_libera(f);
    }

    FILE* arq_p = fopen("entrada_pilha.txt", "r");
    if (arq_p != NULL) {
        Pilha* p = pilha_cria();
        while (fscanf(arq_p, " %c", &tipo) != EOF) {
            if (tipo == 'e') {
                fscanf(arq_p, "%d", &valor);
                PUSH(p, valor);
                pilha_imprime(p);
            } else if (tipo == 'r') {
                POP(p);
                pilha_imprime(p);
            }
        }
        fclose(arq_p); 
        pilha_libera(p);
    }
    return 0;
}