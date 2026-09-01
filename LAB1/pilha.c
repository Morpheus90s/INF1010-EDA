#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct no { int info; struct no* prox; } No;
struct pilha { No* prim; };

Pilha* pilha_cria(void) {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->prim = NULL; 
    return p;
}

void PUSH(Pilha* p, int v) {
    No* novo = (No*)malloc(sizeof(No));
    novo->info = v; 
    novo->prox = p->prim;
    p->prim = novo;
}

int POP(Pilha* p) {
    if (p->prim == NULL) return -1;
    No* t = p->prim; 
    int v = t->info;
    p->prim = t->prox; 
    free(t); 
    return v;
}

static void imprime_rec(No* no, int* prim) {
    if (no == NULL) return;
    imprime_rec(no->prox, prim);
    if (!(*prim)) printf(", ");
    printf("%d", no->info); 
    *prim = 0;
}

void pilha_imprime(Pilha* p) {
    printf("["); 
    int prim = 1;
    imprime_rec(p->prim, &prim);
    printf("]\n");
}

void pilha_libera(Pilha* p) {
    No* q = p->prim;
    while (q != NULL) { 
        No* t = q->prox; 
        free(q); 
        q = t; 
    }
    free(p);
}