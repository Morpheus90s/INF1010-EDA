// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct no { int info; struct no* prox; } No;
struct fila { No *ini; No *fim; };

Fila* fila_cria(void) {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

void ARMAZENA(Fila* f, int v) {
    No* novo = (No*)malloc(sizeof(No));
    novo->info = v; 
    novo->prox = NULL;
    if (f->fim != NULL) f->fim->prox = novo;
    else f->ini = novo;
    f->fim = novo;
}

int RETIRA(Fila* f) {
    if (f->ini == NULL) return -1;
    No* t = f->ini; 
    int v = t->info;
    f->ini = t->prox;
    if (f->ini == NULL) f->fim = NULL;
    free(t); 
    return v;
}

void fila_imprime(Fila* f) {
    printf("[");
    for (No* q = f->ini; q != NULL; q = q->prox) {
        printf("%d", q->info);
        if (q->prox != NULL) printf(", ");
    }
    printf("]\n");
}

void fila_libera(Fila* f) {
    No* q = f->ini;
    while (q != NULL) { 
        No* t = q->prox; 
        free(q); 
        q = t; 
    }
    free(f);
}