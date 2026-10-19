// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct no
{
    int id;
    char categoria;
    struct no* prox;
} No;

struct fila
{
    No* prim;
    int qtd_A;
    int qtd_B;
    int qtd_G;
    int total;
};

Fila* fila_cria(void)
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f == NULL)
    {
        printf("erro ao alocar memoria");
        exit(1);
    }
    f->prim = NULL;
    f->qtd_A = 0;
    f->qtd_B = 0;
    f->qtd_G = 0;
    f->total = 0;
    return f;
}

static int prioridade(char categoria)
{
    if (categoria == 'A') return 3;
    if (categoria == 'B') return 2;
    if (categoria == 'G') return 1;
    return 0;
}

void fila_insere(Fila* f, int id, char categoria)
{
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) 
    {
        printf("erro ao alocar memoria");
        exit(1);
    }
    novo->id = id;
    novo->categoria = categoria;
    novo->prox = NULL;

    if (categoria == 'A') f->qtd_A++;
    else if (categoria == 'B') f->qtd_B++;
    else if (categoria == 'G') f->qtd_G++;
    f->total++;

    if (f->prim == NULL)
    {
        f->prim = novo;
        return;
    }

    int prio_novo = prioridade(categoria);
    No* ant = NULL;
    No* p = f->prim;

    while (p != NULL && prioridade(p->categoria) >= prio_novo)
    {
        ant = p;
        p = p->prox;
    }

    if (ant == NULL)
    { 
        novo->prox = f->prim;
        f->prim = novo;
    }
    else
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }
}

void fila_remove(Fila* f, int id, char categoria)
{
    No* ant = NULL;
    No* p = f->prim;

    while (p != NULL && (p->id != id || p->categoria != categoria))
    {
        ant = p;
        p = p->prox;
    }

    if (p == NULL)
    {
        return;
    }

    if (ant == NULL)
    {
        f->prim = p->prox;
    }
    else
    {
        ant->prox = p->prox;
    }

    if (p->categoria == 'A')
    {
        f->qtd_A--;
    }
    else if (p->categoria == 'B')
    {
        f->qtd_B--;
    }
    else if (p->categoria == 'G')
    {
        f->qtd_G--;
    }
    f->total--;
    free(p);
}

void fila_imprime(Fila* f)
{
    printf("Total: %d - A: %d - B: %d - G: %d\n", f->total, f->qtd_A, f->qtd_B, f->qtd_G);
    No* p = f->prim;
    while (p != NULL)
    {
        printf("%d-%c\n", p->id, p->categoria);
        p = p->prox;
    }
}

void fila_libera(Fila* f)
{
    No* p = f->prim;
    while (p != NULL)
    {
        No* t = p->prox;
        free(p);
        p = t;
    }
    free(f);
}