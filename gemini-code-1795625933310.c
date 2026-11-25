/*
 * Trabalho 2 - INF1010 (Estruturas de Dados Avancadas) - 2026.2
 * Questao 2: Rotas da Ambulancia (Algoritmo de Dijkstra)
 * Nome: [Seu Nome Completo]
 * Matricula: [Sua Matricula]
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} HeapNo;

typedef struct {
    HeapNo* dados;
    int tam;
    int cap;
} HeapMin;

static Viz* cria_viz(int noj, int peso, Viz* prox) {
    Viz* novo = (Viz*)malloc(sizeof(Viz));
    if (!novo) exit(1);
    novo->noj = noj;
    novo->peso = peso;
    novo->prox = prox;
    return novo;
}

static Grafo* grafo_cria(int nv) {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    if (!g) exit(1);
    g->nv = nv;
    g->na = 0;
    g->viz = (Viz**)calloc(nv, sizeof(Viz*));
    if (!g->viz) exit(1);
    return g;
}

static void grafo_insere_aresta(Grafo* g, int u, int v, int peso) {
    g->viz[u] = cria_viz(v, peso, g->viz[u]);
    g->viz[v] = cria_viz(u, peso, g->viz[v]);
    g->na++;
}

static void grafo_libera(Grafo* g) {
    if (!g) return;
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

static HeapMin* heap_cria(int cap_inicial) {
    HeapMin* h = (HeapMin*)malloc(sizeof(HeapMin));
    if (!h) exit(1);
    h->tam = 0;
    h->cap = (cap_inicial > 0) ? cap_inicial : 4;
    h->dados = (HeapNo*)malloc(h->cap * sizeof(HeapNo));
    if (!h->dados) exit(1);
    return h;
}

static void heap_troca(HeapNo* a, HeapNo* b) {
    HeapNo tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heap_subir(HeapMin* h, int idx) {
    while (idx > 0) {
        int pai = (idx - 1) / 2;
        if (h->dados[idx].dist < h->dados[pai].dist) {
            heap_troca(&h->dados[idx], &h->dados[pai]);
            idx = pai;
        } else {
            break;
        }
    }
}

static void heap_descer(HeapMin* h, int idx) {
    while (1) {
        int esq = 2 * idx + 1;
        int dir = 2 * idx + 2;
        int menor = idx;

        if (esq < h->tam && h->dados[esq].dist < h->dados[menor].dist) {
            menor = esq;
        }
        if (dir < h->tam && h->dados[dir].dist < h->dados[menor].dist) {
            menor = dir;
        }

        if (menor != idx) {
            heap_troca(&h->dados[idx], &h->dados[menor]);
            idx = menor;
        } else {
            break;
        }
    }
}

static void heap_insere(HeapMin* h, int v, long long dist) {
    if (h->tam == h->cap) {
        h->cap *= 2;
        HeapNo* novo = (HeapNo*)realloc(h->dados, h->cap * sizeof(HeapNo));
        if (!novo) exit(1);
        h->dados = novo;
    }
    h->dados[h->tam].v = v;
    h->dados[h->tam].dist = dist;
    heap_subir(h, h->tam);
    h->tam++;
}

static HeapNo heap_retira_min(HeapMin* h) {
    HeapNo topo = h->dados[0];
    h->tam--;
    if (h->tam > 0) {
        h->dados[0] = h->dados[h->tam];
        heap_descer(h, 0);
    }
    return topo;
}

static int heap_vazio(const HeapMin* h) {
    return h->tam == 0;
}

static void heap_libera(HeapMin* h) {
    if (h) {
        free(h->dados);
        free(h);
    }
}

static void dijkstra(const Grafo* g, int origem, long long* dist, int* ant) {
    int n = g->nv;
    for (int i = 0; i < n; i++) {
        dist[i] = LLONG_MAX;
        ant[i] = -1;
    }

    HeapMin* pq = heap_cria(n + 1);
    dist[origem] = 0;
    heap_insere(pq, origem, 0);

    while (!heap_vazio(pq)) {
        HeapNo atual = heap_retira_min(pq);
        int u = atual.v;

        if (atual.dist > dist[u]) {
            continue;
        }

        for (Viz* p = g->viz[u]; p != NULL; p = p->prox) {
            int v = p->noj;
            long long nova_dist = dist[u] + p->peso;

            if (nova_dist < dist[v]) {
                dist[v] = nova_dist;
                ant[v] = u;
                heap_insere(pq, v, nova_dist);
            } else if (nova_dist == dist[v] && u < ant[v]) {
                ant[v] = u;
            }
        }
    }

    heap_libera(pq);
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

    Grafo* g = grafo_cria(n);

    for (int i = 0; i < m; i++) {
        int u, v, d;
        if (scanf("%d %d %d", &u, &v, &d) != 3) {
            grafo_libera(g);
            free(bairros);
            return 1;
        }
        grafo_insere_aresta(g, u, v, d);
    }

    int h;
    if (scanf("%d", &h) != 1) {
        grafo_libera(g);
        free(bairros);
        return 1;
    }

    long long* dist = (long long*)malloc(n * sizeof(long long));
    int* ant = (int*)malloc(n * sizeof(int));
    int* caminho = (int*)malloc(n * sizeof(int));
    if (!dist || !ant || !caminho) {
        free(caminho);
        free(ant);
        free(dist);
        grafo_libera(g);
        free(bairros);
        return 1;
    }

    dijkstra(g, h, dist, ant);

    printf("ROTAS DA AMBULANCIA (DIJKSTRA)\n");
    printf("origem: %s\n", bairros[h]);

    for (int i = 0; i < n; i++) {
        int tam_caminho = 0;
        for (int curr = i; curr != -1; curr = ant[curr]) {
            caminho[tam_caminho++] = curr;
        }

        printf("%s: %lld km | ", bairros[i], dist[i]);
        for (int k = tam_caminho - 1; k >= 0; k--) {
            printf("%s", bairros[caminho[k]]);
            if (k > 0) {
                printf(" -> ");
            }
        }
        printf("\n");
    }

    free(caminho);
    free(ant);
    free(dist);
    grafo_libera(g);
    free(bairros);

    return 0;
}