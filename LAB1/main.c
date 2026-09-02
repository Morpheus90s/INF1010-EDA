#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "pilha.h"

int main(void) {
    char tipo;
    int valor;

    // ==========================================
    // PARTE 1: PROCESSANDO A FILA
    // ==========================================
    FILE* arq_f = fopen("entrada_fila.txt", "r");
    
    if (arq_f != NULL) { // Proteção contra travamentos
        Fila* f = fila_cria(); // Cria a fila antes de começar
        
        // Radar sensível: "%c" SEM espaço captura tudo, até o \n
        while (fscanf(arq_f, "%c", &tipo) != EOF) {
            
            if (tipo == 'a') {
                fscanf(arq_f, "%d", &valor); 
                ARMAZENA(f, valor);
                fila_imprime(f);
            } 
            else if (tipo == 'r') {
                RETIRA(f);
                fila_imprime(f);
            } 
            else if (tipo == '\n') {
                printf("----------\n");
                fila_libera(f);      // Faxina: destrói a fila da linha anterior
                f = fila_cria();     // Nasce uma nova fila para a nova linha
            }
        }
        
        fclose(arq_f);      // Fecha o arquivo
        fila_libera(f);     // Libera a última fila que sobrou na memória
    }

    printf("\n\n----------------------PILHA-----------------\n\n");
    FILE* arq_p = fopen("entrada_pilha.txt", "r");
    
    if (arq_p != NULL) {
        Pilha* p = pilha_cria();
        
        // Radar sensível idêntico ao da fila para detectar o \n
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
                pilha_libera(p);     // Faxina da pilha
                p = pilha_cria();    // Pilha nova
            }
        }
        
        fclose(arq_p);
        pilha_libera(p);
    }
    
    return 0;
}