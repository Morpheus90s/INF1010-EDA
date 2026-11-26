/*
 * Trabalho 2 - INF1010 (Estruturas de Dados Avancadas) - 2026.2
 * Questao 1: Rede de Fibra Optica (Algoritmo de Kruskal)
 * Nome: Pedro Augusto Beserra da Silva
 * Matricula: [Sua Matricula]
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, d;
} Aresta;

typedef struct {
    int* pai;
    int* rank;
} UF;

int cmp(const void* a, const void* b) {
    Aresta* e1 = (Aresta*)a;
    Aresta* e2 = (Aresta*)b;
    if (e1->d != e2->d) return (e1->d < e2->d) ? -1 : 1;
    if (e1->u != e2->u) return (e1->u < e2->u) ? -1 : 1;
    if (e1->v != e2->v) return (e1->v < e2->v) ? -1 : 1;
    return 0;
}

UF* cria_uf(int n) {
    UF* uf = (UF*)malloc(sizeof(UF));
    uf->pai = (int*)malloc(n * sizeof(int));
    uf->rank = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        uf->pai[i] = i;
    }
    return uf;
}

int find(UF* uf, int x) {
    if (uf->pai[x] != x) {
        uf->pai[x] = find(uf, uf->pai[x]);
    }
    return uf->pai[x];
}

int unir(UF* uf, int x, int y) {
    int rx = find(uf, x);
    int ry = find(uf, y);
    if (rx == ry) return 0;

    if (uf->rank[rx] < uf->rank[ry]) {
        uf->pai[rx] = ry;
    } else if (uf->rank[rx] > uf->rank[ry]) {
        uf->pai[ry] = rx;
    } else {
        uf->pai[ry] = rx;
        uf->rank[rx]++;
    }
    return 1;
}

void libera_uf(UF* uf) {
    free(uf->pai);
    free(uf->rank);
    free(uf);
}

int main(void) {
    int n, m, h;
    if (scanf("%d %d", &n, &m) != 2) return 1;

    char** bairros = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        bairros[i] = (char*)malloc(32 * sizeof(char));
        if (scanf("%31s", bairros[i]) != 1) return 1;
    }

    Aresta* arestas = (Aresta*)malloc((m > 0 ? m : 1) * sizeof(Aresta));
    for (int i = 0; i < m; i++) {
        int u, v, d;
        if (scanf("%d %d %d", &u, &v, &d) != 3) return 1;
        if (u > v) {
            int aux = u;
            u = v;
            v = aux;
        }
        arestas[i].u = u;
        arestas[i].v = v;
        arestas[i].d = d;
    }

    if (scanf("%d", &h) != 1) return 1;

    if (m > 0) {
        qsort(arestas, m, sizeof(Aresta), cmp);
    }

    UF* uf = cria_uf(n);
    long long total = 0;
    int cont = 0;

    printf("REDE DE FIBRA OPTICA (KRUSKAL)\n");
    for (int i = 0; i < m && cont < n - 1; i++) {
        if (unir(uf, arestas[i].u, arestas[i].v)) {
            printf("%s %s: %d km\n", bairros[arestas[i].u], bairros[arestas[i].v], arestas[i].d);
            total += arestas[i].d;
            cont++;
        }
    }
    printf("Total de cabo: %lld km\n", total);

    libera_uf(uf);
    free(arestas);
    for (int i = 0; i < n; i++) {
        free(bairros[i]);
    }
    free(bairros);

    return 0;
}