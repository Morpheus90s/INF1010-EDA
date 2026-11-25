/*
 * Trabalho 2 - INF1010 (Estruturas de Dados Avancadas) - 2026.2
 * Questao 1: Rede de Fibra Optica (Algoritmo de Kruskal)
 * Nome: [Seu Nome Completo]
 * Matricula: [Sua Matricula]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int u;
    int v;
    int d;
} Aresta;

typedef struct {
    int* pai;
    int* rank;
    int n;
} UnionFind;

static int compara_arestas(const void* a, const void* b) {
    const Aresta* e1 = (const Aresta*)a;
    const Aresta* e2 = (const Aresta*)b;

    if (e1->d != e2->d) {
        return (e1->d < e2->d) ? -1 : 1;
    }
    if (e1->u != e2->u) {
        return (e1->u < e2->u) ? -1 : 1;
    }
    if (e1->v != e2->v) {
        return (e1->v < e2->v) ? -1 : 1;
    }
    return 0;
}

static UnionFind* uf_cria(int n) {
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    if (!uf) exit(1);

    uf->n = n;
    uf->pai = (int*)malloc(n * sizeof(int));
    uf->rank = (int*)calloc(n, sizeof(int));
    if (!uf->pai || !uf->rank) exit(1);

    for (int i = 0; i < n; i++) {
        uf->pai[i] = i;
    }
    return uf;
}

static int uf_find(UnionFind* uf, int x) {
    if (uf->pai[x] != x) {
        uf->pai[x] = uf_find(uf, uf->pai[x]);
    }
    return uf->pai[x];
}

static int uf_union(UnionFind* uf, int x, int y) {
    int raiz_x = uf_find(uf, x);
    int raiz_y = uf_find(uf, y);

    if (raiz_x == raiz_y) {
        return 0;
    }

    if (uf->rank[raiz_x] < uf->rank[raiz_y]) {
        uf->pai[raiz_x] = raiz_y;
    } else if (uf->rank[raiz_x] > uf->rank[raiz_y]) {
        uf->pai[raiz_y] = raiz_x;
    } else {
        uf->pai[raiz_y] = raiz_x;
        uf->rank[raiz_x]++;
    }
    return 1;
}

static void uf_libera(UnionFind* uf) {
    if (uf) {
        free(uf->pai);
        free(uf->rank);
        free(uf);
    }
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return 1;
    }

    char (*bairros)[32] = malloc(n * sizeof(*bairros));
    if (!bairros) return 1;

    for (int i = 0; i < n; i++) {
        if (scanf("%31s", bairros[i]) != 1) {
            free(bairros);
            return 1;
        }
    }

    Aresta* arestas = (Aresta*)malloc((m > 0 ? m : 1) * sizeof(Aresta));
    if (!arestas) {
        free(bairros);
        return 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v, d;
        if (scanf("%d %d %d", &u, &v, &d) != 3) {
            free(arestas);
            free(bairros);
            return 1;
        }
        if (u > v) {
            int tmp = u;
            u = v;
            v = tmp;
        }
        arestas[i].u = u;
        arestas[i].v = v;
        arestas[i].d = d;
    }

    int h;
    if (scanf("%d", &h) != 1) {
        free(arestas);
        free(bairros);
        return 1;
    }
    (void)h; /* Lido conforme formato da entrada, nao utilizado na Questao 1 */

    if (m > 1) {
        qsort(arestas, m, sizeof(Aresta), compara_arestas);
    }

    UnionFind* uf = uf_cria(n);

    printf("REDE DE FIBRA OPTICA (KRUSKAL)\n");
    long long total_cabo = 0;
    int arestas_aceitas = 0;

    for (int i = 0; i < m && arestas_aceitas < n - 1; i++) {
        if (uf_union(uf, arestas[i].u, arestas[i].v)) {
            printf("%s %s: %d km\n",
                   bairros[arestas[i].u],
                   bairros[arestas[i].v],
                   arestas[i].d);
            total_cabo += arestas[i].d;
            arestas_aceitas++;
        }
    }

    printf("Total de cabo: %lld km\n", total_cabo);

    uf_libera(uf);
    free(arestas);
    free(bairros);

    return 0;
}