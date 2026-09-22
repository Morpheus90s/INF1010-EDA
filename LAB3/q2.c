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
        Nodo* novo = (Nodo*) malloc(sizeof(Nodo));
        novo->chave = chave;
        novo->fb = 0;
        novo->esq = novo->dir = NULL;
        return novo;
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
            printf(" → Rotação à esquerda (RE) no nó %d\n", r->chave);
            return rotacao_esquerda(r);
        } else {
            printf(" → Rotação dupla à esquerda (RDE) no nó %d\n", r->chave);
            return rotacao_dupla_esquerda(r);
        }
    } else if (r->fb == -2) {
        *rot = 1;
        if (calc_fb(r->esq) <= 0) {
            printf(" → Rotação à direita (RD) no nó %d\n", r->chave);
            return rotacao_direita(r);
        } else {
            printf(" → Rotação dupla à direita (RED) no nó %d\n", r->chave);
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
        if (r->esq == NULL || r->dir == NULL) {
            Nodo* temp = r->esq ? r->esq : r->dir;
            if (temp == NULL) {
                temp = r;
                r = NULL;
            } else {
                *r = *temp;
            }
            free(temp);
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
            printf(" → Rotação à esquerda (RE) no nó %d\n", r->chave);
            return rotacao_esquerda(r);
        } else {
            printf(" → Rotação dupla à esquerda (RDE) no nó %d\n", r->chave);
            return rotacao_dupla_esquerda(r);
        }
    } else if (r->fb == -2) {
        *rot = 1;
        if (calc_fb(r->esq) <= 0) {
            printf(" → Rotação à direita (RD) no nó %d\n", r->chave);
            return rotacao_direita(r);
        } else {
            printf(" → Rotação dupla à direita (RED) no nó %d\n", r->chave);
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

int main() {
    AVL arvore;
    // Início com a folha 50
    arvore.raiz = (Nodo*) malloc(sizeof(Nodo));
    arvore.raiz->chave = 50;
    arvore.raiz->fb = 0;
    arvore.raiz->esq = arvore.raiz->dir = NULL;

    int elementos_ins[] = {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 43, 16, 67, 39};
    int n_ins = sizeof(elementos_ins) / sizeof(elementos_ins[0]);

    printf("=== a) INSERÇÃO DE ELEMENTOS ===\n");
    for (int i = 0; i < n_ins; i++) {
        int rot = 0;
        printf("Inserir %d", elementos_ins[i]);
        arvore.raiz = avl_insere(arvore.raiz, elementos_ins[i], &rot);
        if (!rot) printf(" → sem rotação.\n");
    }

    printf("\nÁrvore AVL Completa após Inserções:\n");
    imprime_arvore(arvore.raiz, 0);

    int elementos_rem[] = {58, 59, 66, 18};
    int n_rem = sizeof(elementos_rem) / sizeof(elementos_rem[0]);

    printf("\n=== b) REMOÇÃO DE ELEMENTOS ===\n");
    for (int i = 0; i < n_rem; i++) {
        int rot = 0;
        printf("Remoção %d", elementos_rem[i]);
        arvore.raiz = avl_remove(arvore.raiz, elementos_rem[i], &rot);
        if (!rot) printf(" → sem rotação.\n");
    }

    printf("\nÁrvore AVL Final após Remoções:\n");
    imprime_arvore(arvore.raiz, 0);

    return 0;
}