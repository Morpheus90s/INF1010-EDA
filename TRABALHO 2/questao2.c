// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct l Vizinho;
struct l
{
    int bairro;
    int peso;
    Vizinho* prox;
};

typedef struct grafo
{
    int qntd;
    Vizinho** l;
} Grafo;

typedef struct
{
    int v;
    long long dist;
} NoHeap;

typedef struct
{
    NoHeap* dados;
    int tam;
    int cap;
} Heap;

Vizinho* cria_viz(int bairro, int peso, Vizinho* prox)
{
    Vizinho* novo = (Vizinho*)malloc(sizeof(Vizinho));
    novo->bairro = bairro;
    novo->peso = peso;
    novo->prox = prox;
    return novo;
}

Grafo* cria_grafo(int qntd)
{
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    g->qntd = qntd;
    g->l = (Vizinho**)malloc(qntd * sizeof(Vizinho*));
    for (int i = 0; i < qntd; i++)
    {
        g->l[i] = NULL;
    }
    return g;
}

void insere_aresta(Grafo* g, int u, int v, int peso)
{
    g->l[u] = cria_viz(v, peso, g->l[u]);
    g->l[v] = cria_viz(u, peso, g->l[v]);
}

void libera_grafo(Grafo* g)
{
    for (int i = 0; i < g->qntd; i++) 
    {
        Vizinho* p = g->l[i];
        while (p != NULL)
        {
            Vizinho* t = p->prox;
            free(p);
            p = t;
        }
    }
    free(g->l);
    free(g);
}

Heap* cria_heap(int cap)
{
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->tam = 0;
    if (cap > 0)
    {
        h->cap = cap;
    }
    else
    {
        h->cap = 4;
    }
    h->dados = (NoHeap*)malloc(h->cap * sizeof(NoHeap));
    return h;
}

void troca(NoHeap* a, NoHeap* b)
{
    NoHeap atual = *a;
    *a = *b;
    *b = atual;
}

void sobe(Heap* h, int i)
{
    while (i > 0)
    {
        int pai = (i - 1) / 2;
        if (h->dados[i].dist < h->dados[pai].dist)
        {
            troca(&h->dados[i], &h->dados[pai]);
            i = pai;
        } else
        {
            break;
        }
    }
}

void desce(Heap* h, int i)
{
    while (1)
    {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int menor = i;

        if (esq < h->tam && h->dados[esq].dist < h->dados[menor].dist)
        {
            menor = esq;
        }
        if (dir < h->tam && h->dados[dir].dist < h->dados[menor].dist)
        {
            menor = dir;
        }

        if (menor != i)
        {
            troca(&h->dados[i], &h->dados[menor]);
            i = menor;
        }
        else
        {
            break;
        }
    }
}

void insere_heap(Heap* h, int v, long long dist)
{
    if (h->tam == h->cap)
    {
        h->cap *= 2;
        h->dados = (NoHeap*)realloc(h->dados, h->cap * sizeof(NoHeap));
    }
    h->dados[h->tam].v = v;
    h->dados[h->tam].dist = dist;
    sobe(h, h->tam);
    h->tam++;
}

NoHeap retira_min(Heap* h)
{
    NoHeap topo = h->dados[0];
    h->tam--;
    if (h->tam > 0)
    {
        h->dados[0] = h->dados[h->tam];
        desce(h, 0);
    }
    return topo;
}

void libera_heap(Heap* h)
{
    free(h->dados);
    free(h);
}

void dijkstra(Grafo* g, int origem, long long* dist, int* ant)
{
    int n = g->qntd;
    for (int i = 0; i < n; i++)
    {
        dist[i] = LLONG_MAX;
        ant[i] = -1;
    }

    Heap* prioridade = cria_heap(n + 1);
    dist[origem] = 0;
    insere_heap(prioridade, origem, 0);

    while (prioridade->tam > 0)
    {
        NoHeap atual = retira_min(prioridade);
        int u = atual.v;

        if (atual.dist > dist[u])
        {
            continue;
        }
        for (Vizinho* p = g->l[u]; p != NULL; p = p->prox)
        {
            int v = p->bairro;
            long long nova_dist = dist[u] + p->peso;

            if (nova_dist < dist[v])
            {
                dist[v] = nova_dist;
                ant[v] = u;
                insere_heap(prioridade, v, nova_dist);
            }
            else if (nova_dist == dist[v] && u < ant[v])
            {
                ant[v] = u;
            }
        }
    }
    libera_heap(prioridade);
}

int main(void)
{
    int n, m, h;
    if (scanf("%d %d", &n, &m) != 2) return 1;

    char** bairros = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        bairros[i] = (char*)malloc(32 * sizeof(char));
        if (scanf("%31s", bairros[i]) != 1)
        {
            return 1;
        }
    }

    Grafo* g = cria_grafo(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, d;
        if (scanf("%d %d %d", &u, &v, &d) != 3)
        {
            return 1;
        }
        insere_aresta(g, u, v, d);
    }

    if (scanf("%d", &h) != 1)
    {
        return 1;
    }

    long long* dist = (long long*)malloc(n * sizeof(long long));
    int* ant = (int*)malloc(n * sizeof(int));
    int* caminho = (int*)malloc(n * sizeof(int));

    dijkstra(g, h, dist, ant);
    printf("ROTAS DA AMBULANCIA (DIJKSTRA) - origem: %s\n", bairros[h]);
    for (int i = 0; i < n; i++)
    {
        int tam = 0;
        int atual = i;
        while (atual != -1)
        {
            caminho[tam++] = atual;
            atual = ant[atual];
        }

        printf("%s: %lld km | ", bairros[i], dist[i]);
        for (int j = tam - 1; j >= 0; j--)
        {
            printf("%s", bairros[caminho[j]]);
            if (j > 0)
            {
                printf(" -> ");
            }
        }
        printf("\n");
    }
    free(caminho);
    free(ant);
    free(dist);
    libera_grafo(g);
    for (int i = 0; i < n; i++)
    {
        free(bairros[i]);
    }
    free(bairros);
    return 0;
}