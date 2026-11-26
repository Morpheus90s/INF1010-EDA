/*
 * Trabalho 2 - INF1010 (Estruturas de Dados Avancadas) - 2026.2
 * Questao 2: Rotas da Ambulancia (Algoritmo de Dijkstra)
 * Nome: Pedro Augusto Beserra da Silva
 * Matricula: [Sua Matricula]
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct viz Viz;
struct viz {
    int noj;
    int peso;
    Viz* prox;
};

typedef struct _grafo {
    int nv;
    int na;
    Viz** viz;
} Grafo;

typedef struct {
    int v;
    long long dist;
} NoHeap;

typedef struct {
    NoHeap* dados;
    int tam;
    int cap;
} Heap;

Viz* cria_viz(int noj, int peso, Viz* prox) {
    Viz* novo = (Viz*)malloc(sizeof(Viz));
    novo->noj = noj;
    novo->peso = peso;
    novo->prox = prox;
    return novo;
}

Grafo* cria_grafo(int nv) {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    g->nv = nv;
    g->na = 0;
    g->viz = (Viz**)calloc(nv, sizeof(Viz*));
    return g;
}

void insere_aresta(Grafo* g, int u, int v, int peso) {
    g->viz[u] = cria_viz(v, peso, g->viz[u]);
    g->viz[v] = cria_viz(u, peso, g->viz[v]);
    g->na++;
}

void libera_grafo(Grafo* g) {
    for (int i = 0; i < g->nv; i++) {
        Viz* p = g->viz[i];
        while (p != NULL) {
            Viz* t = p->prox;
            free(p);
            p = t;
        }
    }
    free(g->viz);
    free(g);
}

Heap* cria_heap(int cap) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->tam = 0;
    h->cap = cap > 0 ? cap : 4;
    h->dados = (NoHeap*)malloc(h->cap * sizeof(NoHeap));
    return h;
}

void troca(NoHeap* a, NoHeap* b) {
    NoHeap aux = *a;
    *a = *b;
    *b = aux;
}

void sobe(Heap* h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h->dados[i].dist < h->dados[pai].dist) {
            troca(&h->dados[i], &h->dados[pai]);
            i = pai;
        } else {
            break;
        }
    }
}

void desce(Heap* h, int i) {
    while (1) {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int menor = i;

        if (esq < h->tam && h->dados[esq].dist < h->dados[menor].dist) {
            menor = esq;
        }
        if (dir < h->tam && h->dados[dir].dist < h->dados[menor].dist) {
            menor = dir;
        }

        if (menor != i) {
            troca(&h->dados[i], &h->dados[menor]);
            i = menor;
        } else {
            break;
        }
    }
}

void insere_heap(Heap* h, int v, long long dist) {
    if (h->tam == h->cap) {
        h->cap *= 2;
        h->dados = (NoHeap*)realloc(h->dados, h->cap * sizeof(NoHeap));
    }
    h->dados[h->tam].v = v;
    h->dados[h->tam].dist = dist;
    sobe(h, h->tam);
    h->tam++;
}

NoHeap retira_min(Heap* h) {
    NoHeap topo = h->dados[0];
    h->tam--;
    if (h->tam > 0) {
        h->dados[0] = h->dados[h->tam];
        desce(h, 0);
    }
    return topo;
}

void libera_heap(Heap* h) {
    free(h->dados);
    free(h);
}

void dijkstra(Grafo* g, int origem, long long* dist, int* ant) {
    int n = g->nv;
    for (int i = 0; i < n; i++) {
        dist[i] = LLONG_MAX;
        ant[i] = -1;
    }

    Heap* pq = cria_heap(n + 1);
    dist[origem] = 0;
    insere_heap(pq, origem, 0);

    while (pq->tam > 0) {
        NoHeap atual = retira_min(pq);
        int u = atual.v;

        if (atual.dist > dist[u]) continue;

        for (Viz* p = g->viz[u]; p != NULL; p = p->prox) {
            int v = p->noj;
            long long nova_dist = dist[u] + p->peso;

            if (nova_dist < dist[v]) {
                dist[v] = nova_dist;
                ant[v] = u;
                insere_heap(pq, v, nova_dist);
            } else if (nova_dist == dist[v] && u < ant[v]) {
                ant[v] = u;
            }
        }
    }

    libera_heap(pq);
}

int main(void) {
    int n, m, h;
    if (scanf("%d %d", &n, &m) != 2) return 1;

    char** bairros = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        bairros[i] = (char*)malloc(32 * sizeof(char));
        if (scanf("%31s", bairros[i]) != 1) return 1;
    }

    Grafo* g = cria_grafo(n);
    for (int i = 0; i < m; i++) {
        int u, v, d;
        if (scanf("%d %d %d", &u, &v, &d) != 3) return 1;
        insere_aresta(g, u, v, d);
    }

    if (scanf("%d", &h) != 1) return 1;

    long long* dist = (long long*)malloc(n * sizeof(long long));
    int* ant = (int*)malloc(n * sizeof(int));
    int* cam = (int*)malloc(n * sizeof(int));

    dijkstra(g, h, dist, ant);

    printf("ROTAS DA AMBULANCIA (DIJKSTRA)\n");
    printf("origem: %s\n", bairros[h]);

    for (int i = 0; i < n; i++) {
        int tam = 0;
        int aux = i;
        while (aux != -1) {
            cam[tam++] = aux;
            aux = ant[aux];
        }

        printf("%s: %lld km | ", bairros[i], dist[i]);
        for (int j = tam - 1; j >= 0; j--) {
            printf("%s", bairros[cam[j]]);
            if (j > 0) printf(" -> ");
        }
        printf("\n");
    }

    free(cam);
    free(ant);
    free(dist);
    libera_grafo(g);
    for (int i = 0; i < n; i++) {
        free(bairros[i]);
    }
    free(bairros);

    return 0;
}