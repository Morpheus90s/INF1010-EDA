// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

struct pagina
{
    struct pagina *pai;
    int n_chaves;
    int chave[MAX - 1];

    struct pagina *ramo_esq;
    struct pagina *ramos[MAX];
};

struct b_tree
{
    Pagina *raiz;
    int ordem;
};

/* ---------- Questão 1 ---------- */

Pagina *cria(int n, int *chaves)
{
    Pagina *pag = malloc(sizeof(Pagina));
    if (pag == NULL)
    {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    pag->pai = NULL;
    pag->ramo_esq = NULL;
    pag->n_chaves = n;

    for (int i = 0; i < MAX; i++)
    {
        pag->ramos[i] = NULL;
    }
    for (int i = 0; i < n; i++)
    {
        pag->chave[i] = chaves[i];
    }
    return pag;
}

B_Tree *monta(void)
{
    Pagina *f1 = cria(2, (int[]){10, 40});
    Pagina *f2 = cria(2, (int[]){60, 70});
    Pagina *f3 = cria(2, (int[]){80, 90});
    Pagina *f4 = cria(2, (int[]){110, 115});
    Pagina *f5 = cria(4, (int[]){130, 135, 140, 170});
    Pagina *f6 = cria(4, (int[]){220, 230, 240, 250});

    Pagina *n1 = cria(2, (int[]){50, 75});
    Pagina *n2 = cria(2, (int[]){120, 200});

    Pagina *raiz  = cria(1, (int[]){100});

    n1->ramo_esq = f1;
    n1->ramos[0] = f2;
    n1->ramos[1] = f3;
    n2->ramo_esq = f4;
    n2->ramos[0] = f5;
    n2->ramos[1] = f6;

    raiz->ramo_esq = n1;
    raiz->ramos[0] = n2;

    f1->pai = n1;
    f2->pai = n1;
    f3->pai = n1;
    f4->pai = n2;
    f5->pai = n2;
    f6->pai = n2;

    n1->pai = raiz;
    n2->pai = raiz;

    B_Tree *arvore = malloc(sizeof(B_Tree));
    if (arvore == NULL)
    {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    arvore->raiz = raiz;
    arvore->ordem = 5;
    return arvore;
}

/* ---------- Questão 2 ---------- */

void intervalo(Pagina *pagina, int lim_inf, int lim_sup)
{
    if (pagina == NULL)
    {
        return;
    }
    intervalo(pagina->ramo_esq, lim_inf, lim_sup);

    for (int i = 0; i < pagina->n_chaves; i++)
    {
        if (pagina->chave[i] > lim_inf && pagina->chave[i] < lim_sup)
        {
            printf("%d ", pagina->chave[i]);
        }
        intervalo(pagina->ramos[i], lim_inf, lim_sup);
    }
}
int main(void)
{
    B_Tree *arvore = monta();
    intervalo(arvore->raiz, 45, 135);
    printf("\n");
    return 0;
}