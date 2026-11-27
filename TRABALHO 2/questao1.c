// Aluno A: Eduardo Canton - 2410837 
// Aluno B: Pedro Augusto - 2321374

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int origem, destino, peso;
} Aresta;

typedef struct
{
    int* pai;
    int* rank;
} UF;

int cmp(const void* a, const void* b)
{
    Aresta* e1 = (Aresta*)a;
    Aresta* e2 = (Aresta*)b;
    if (e1->peso != e2->peso)
    {
        if (e1->peso < e2->peso)
            return -1;
        else
            return 1;
    }
    if (e1->origem != e2->origem)
    {
        if (e1->origem < e2->origem)
            return -1;
        else
            return 1;
    }
    if (e1->destino != e2->destino)
    {
        if (e1->destino < e2->destino)
            return -1;
        else
            return 1;
    }
    return 0;
}

UF* cria_uf(int n)
{
    UF* uf = (UF*)malloc(sizeof(UF));
    uf->pai = (int*)malloc(n * sizeof(int));
    uf->rank = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        uf->pai[i] = i;
        uf->rank[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        uf->pai[i] = i;
    }
    return uf;
}

int busca(UF* uf, int x)
{
    if (uf->pai[x] != x)
    {
        uf->pai[x] = busca(uf, uf->pai[x]);
    }
    return uf->pai[x];
}

int unir(UF* uf, int x, int y)
{
    int rx = busca(uf, x);
    int ry = busca(uf, y);
    if (rx == ry)
    {
        return 0;
    }
    if (uf->rank[rx] < uf->rank[ry])
    {
        uf->pai[rx] = ry;
    }
    else if (uf->rank[rx] > uf->rank[ry])
    {
        uf->pai[ry] = rx;
    }
    else
    {
        uf->pai[ry] = rx;
        uf->rank[rx]++;
    }
    return 1;
}

void libera_uf(UF* uf)
{
    free(uf->pai);
    free(uf->rank);
    free(uf);
}

int main(void)
{
    int n, m, h;
    if (scanf("%d %d", &n, &m) != 2)
    {
        return 1;
    }
    char** bairros = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        bairros[i] = (char*)malloc(32 * sizeof(char));
        if (scanf("%31s", bairros[i]) != 1)
        {
            return 1;
        }
    }

    Aresta* arestas = (Aresta*)malloc((m > 0 ? m : 1) * sizeof(Aresta));
    for (int i = 0; i < m; i++)
    {
        int origem, destino, peso;
        if (scanf("%d %d %d", &origem, &destino, &peso) != 3)
        {
            return 1;
        }
        if (origem > destino)
        {
            int aux = origem;
            origem = destino;
            destino = aux;
        }
        arestas[i].origem = origem;
        arestas[i].destino = destino;
        arestas[i].peso = peso;
    }

    if (scanf("%d", &h) != 1)
    {
        return 1;
    } 
    if (m > 0)
    {
        qsort(arestas, m, sizeof(Aresta), cmp);
    }

    UF* uf = cria_uf(n);
    long long total = 0;
    int qntd = 0;

    printf("REDE DE FIBRA OPTICA (KRUSKAL)\n");
    for (int i = 0; i < m && qntd < n - 1; i++)
    {
        if (unir(uf, arestas[i].origem, arestas[i].destino))
        {
            printf("%s - %s: %d km\n", bairros[arestas[i].origem], bairros[arestas[i].destino], arestas[i].peso);
            total += arestas[i].peso;
            qntd++;
        }
    }
    printf("Total de cabo: %lld km\n", total);
    libera_uf(uf);
    free(arestas);
    for (int i = 0; i < n; i++)
    {
        free(bairros[i]);
    }
    free(bairros);
    return 0;
}