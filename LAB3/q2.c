// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int chave;
    int fb;
    struct nodo *esq;
    struct nodo *dir;
};
typedef struct nodo Nodo;

struct avl {
    Nodo * raiz;
};
typedef struct avl AVL;

Nodo* cria_nodo_avl(int chave) {
    Nodo* novo = (Nodo*) malloc(sizeof(Nodo));
    if (!novo) {
        printf("Erro de alocacao.\n");
        exit(1);
    }
    novo->chave = chave;
    novo->fb = 0;
    novo->esq = novo->dir = NULL;
    return novo;
}

int altura(Nodo* n) {
    if (n == NULL) return -1;
    int alt_esq = altura(n->esq);
    int alt_dir = altura(n->dir);
    return (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
}

int calc_fb(Nodo* n) {
    if (n == NULL) return 0;
    return altura(n->dir) - altura(n->esq);
}

void atualiza_fb(Nodo* n) {
    if (n != NULL) {
        n->fb = calc_fb(n);
    }
}

Nodo* rotacao_esquerda(Nodo* p) {
    Nodo* q = p->dir;
    p->dir = q->esq;
    q->esq = p;
    atualiza_fb(p);
    atualiza_fb(q);
    return q;
}

Nodo* rotacao_direita(Nodo* p) {
    Nodo* q = p->esq;
    p->esq = q->dir;
    q->dir = p;
    atualiza_fb(p);
    atualiza_fb(q);
    return q;
}

Nodo* rotacao_dupla_esquerda(Nodo* p) {
    p->dir = rotacao_direita(p->dir);
    return rotacao_esquerda(p);
}

Nodo* rotacao_dupla_direita(Nodo* p) {
    p->esq = rotacao_esquerda(p->esq);
    return rotacao_direita(p);
}

Nodo* avl_insere(Nodo* r, int chave, int* rot) {
    if (r == NULL) {
        return cria_nodo_avl(chave);
    }

    if (chave < r->chave)
        r->esq = avl_insere(r->esq, chave, rot);
    else if (chave > r->chave)
        r->dir = avl_insere(r->dir, chave, rot);
    else
        return r;

    atualiza_fb(r);

    if (r->fb == 2) {
        *rot = 1;
        if (calc_fb(r->dir) >= 0) {
            printf(" -> Rotacao a esquerda no no %d\n", r->chave);
            return rotacao_esquerda(r);
        } else {
            printf(" -> Rotacao dupla a esquerda no no %d\n", r->chave);
            return rotacao_dupla_esquerda(r);
        }
    } else if (r->fb == -2) {
        *rot = 1;
        if (calc_fb(r->esq) <= 0) {
            printf(" -> Rotacao a direita no no %d\n", r->chave);
            return rotacao_direita(r);
        } else {
            printf(" -> Rotacao dupla a direita no no %d\n", r->chave);
            return rotacao_dupla_direita(r);
        }
    }

    return r;
}

Nodo* maior_nodo(Nodo* r) {
    Nodo* atual = r;
    while (atual->dir != NULL) atual = atual->dir;
    return atual;
}

Nodo* avl_remove(Nodo* r, int chave, int* rot) {
    if (r == NULL) return NULL;

    if (chave < r->chave) {
        r->esq = avl_remove(r->esq, chave, rot);
    } else if (chave > r->chave) {
        r->dir = avl_remove(r->dir, chave, rot);
    } else {
        if (r->esq == NULL) {
            Nodo* temp = r->dir;
            free(r);
            return temp;
        } else if (r->dir == NULL) {
            Nodo* temp = r->esq;
            free(r);
            return temp;
        } else {
            Nodo* temp = maior_nodo(r->esq);
            r->chave = temp->chave;
            r->esq = avl_remove(r->esq, temp->chave, rot);
        }
    }

    if (r == NULL) return NULL;

    atualiza_fb(r);

    if (r->fb == 2) {
        *rot = 1;
        if (calc_fb(r->dir) >= 0) {
            printf(" -> Rotacao a esquerda no no %d\n", r->chave);
            return rotacao_esquerda(r);
        } else {
            printf(" -> Rotacao dupla a esquerda no no %d\n", r->chave);
            return rotacao_dupla_esquerda(r);
        }
    } else if (r->fb == -2) {
        *rot = 1;
        if (calc_fb(r->esq) <= 0) {
            printf(" -> Rotacao a direita no no %d\n", r->chave);
            return rotacao_direita(r);
        } else {
            printf(" -> Rotacao dupla a direita no no %d\n", r->chave);
            return rotacao_dupla_direita(r);
        }
    }

    return r;
}

void imprime_arvore(Nodo* r, int nivel) {
    if (r != NULL) {
        imprime_arvore(r->dir, nivel + 1);
        for (int i = 0; i < nivel; i++) printf("   ");
        printf("%d (FB:%d)\n", r->chave, r->fb);
        imprime_arvore(r->esq, nivel + 1);
    }
}

void libera_arvore_avl(Nodo* r) {
    if (r != NULL) {
        libera_arvore_avl(r->esq);
        libera_arvore_avl(r->dir);
        free(r);
    }
}

int main() {
    AVL arvore;
    arvore.raiz = cria_nodo_avl(50);

    int elementos_ins[] = {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 43, 16, 67, 39};
    int n_ins = sizeof(elementos_ins) / sizeof(elementos_ins[0]);

    printf("=== a) INSERCAO DE ELEMENTOS ===\n");
    for (int i = 0; i < n_ins; i++) {
        int rot = 0;
        printf("Inserir %d", elementos_ins[i]);
        arvore.raiz = avl_insere(arvore.raiz, elementos_ins[i], &rot);
        if (!rot) printf(" -> sem rotacao.\n");
    }

    printf("\nArvore AVL Completa apos Insercoes:\n");
    imprime_arvore(arvore.raiz, 0);

    int elementos_rem[] = {58, 59, 66, 18};
    int n_rem = sizeof(elementos_rem) / sizeof(elementos_rem[0]);

    printf("\n=== b) REMOCAO DE ELEMENTOS ===\n");
    for (int i = 0; i < n_rem; i++) {
        int rot = 0;
        printf("Remocao %d", elementos_rem[i]);
        arvore.raiz = avl_remove(arvore.raiz, elementos_rem[i], &rot);
        if (!rot) printf(" -> sem rotacao.\n");
    }

    printf("\nArvore AVL Final apos Remocoes:\n");
    imprime_arvore(arvore.raiz, 0);

    libera_arvore_avl(arvore.raiz);

    return 0;
}