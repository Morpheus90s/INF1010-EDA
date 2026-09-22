#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int chave;
    int altura;
    struct nodo * esq;
    struct nodo * dir;
};
typedef struct nodo Nodo;

struct abb {
    Nodo * raiz;
};
typedef struct abb ABB;

Nodo* cria_nodo(int chave) {
    Nodo* novo = (Nodo*) malloc(sizeof(Nodo));
    novo->chave = chave;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

Nodo* insere_abb(Nodo* r, int chave) {
    if (r == NULL) return cria_nodo(chave);
    if (chave < r->chave)
        r->esq = insere_abb(r->esq, chave);
    else if (chave > r->chave)
        r->dir = insere_abb(r->dir, chave);
    return r;
}

int calcula_altura(Nodo* r) {
    if (r == NULL) return -1;
    int alt_esq = calcula_altura(r->esq);
    int alt_dir = calcula_altura(r->dir);
    r->altura = (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
    return r->altura;
}

void pre_ordem(Nodo* r) {
    if (r != NULL) {
        printf("%d(%d) ", r->chave, r->altura);
        pre_ordem(r->esq);
        pre_ordem(r->dir);
    }
}

void ordem_simetrica(Nodo* r) {
    if (r != NULL) {
        ordem_simetrica(r->esq);
        printf("%d(%d) ", r->chave, r->altura);
        ordem_simetrica(r->dir);
    }
}

void por_nivel(Nodo* r) {
    if (r == NULL) return;
    Nodo* fila[100];
    int inicio = 0, fim = 0;
    
    fila[fim++] = r;
    while (inicio < fim) {
        Nodo* atual = fila[inicio++];
        printf("%d(%d) ", atual->chave, atual->altura);
        if (atual->esq != NULL) fila[fim++] = atual->esq;
        if (atual->dir != NULL) fila[fim++] = atual->dir;
    }
}

int main() {
    ABB arvore;
    arvore.raiz = NULL;

    FILE* file = fopen("entrada.txt", "r");
    if (!file) {
        printf("Erro ao abrir entrada.txt\n");
        return 1;
    }

    int chave;
    while (fscanf(file, "%d", &chave) == 1) {
        arvore.raiz = insere_abb(arvore.raiz, chave);
    }
    fclose(file);

    calcula_altura(arvore.raiz);

    printf("Pré-ordem: ");
    pre_ordem(arvore.raiz);
    printf("\nOrdem Simétrica: ");
    ordem_simetrica(arvore.raiz);
    printf("\nPor nível: ");
    por_nivel(arvore.raiz);
    printf("\n");

    return 0;
}