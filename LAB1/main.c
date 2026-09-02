#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "pilha.h"

int main(void) {
    char tipo;
    int valor;

    FILE* arq_f = fopen("entrada_fila.txt", "r");
    if (arq_f != NULL) {
        Fila* fila = fila_cria();
        if(fila==NULL)
        {
            printf("erro ao alocar memoria");
            exit(1);
        }
        while (fscanf(arq_f, "%c", &tipo) != EOF) {  
            if (tipo == 'a') {
                fscanf(arq_f, "%d", &valor); 
                ARMAZENA(fila, valor);
                fila_imprime(fila);
            } 
            else if (tipo == 'r') {
                RETIRA(fila);
                fila_imprime(fila);
            } 
            else if (tipo == '\n') {
                printf("----------\n");
                fila_libera(fila);
                fila = fila_cria();
            }
        } 
        fclose(arq_f);
        fila_libera(fila);
    }

    printf("\n\n----------------------PILHA-----------------\n\n");
    FILE* arq_p = fopen("entrada_pilha.txt", "r");
    
    if (arq_p != NULL) {
        Pilha* p = pilha_cria();
        while (fscanf(arq_p, "%c", &tipo) != EOF) {  
            if (tipo == 'e') {
                fscanf(arq_p, "%d", &valor);
                PUSH(p, valor);
                pilha_imprime(p);
            } 
            else if (tipo == 'r') {
                POP(p);
                pilha_imprime(p);
            }
            else if (tipo == '\n') {
                printf("----------\n");
                pilha_libera(p);
                p = pilha_cria();
            }
        }
        
        fclose(arq_p);
        pilha_libera(p);
    }
    
    return 0;
}