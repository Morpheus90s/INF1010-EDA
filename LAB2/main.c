#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 10

void exibe(int v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", v[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
}

void bubble(int v[], int n)
{
    printf("\nbubble\n");
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (v[j] > v[j + 1])
            {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
        printf("Iteracao %d: ", i + 1);
        exibe(v, n);
    }
}

void selection(int v[], int n)
{
    printf("\nselection\n");
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (v[j] < v[min])
            {
                min = j;
            }
        }
        int temp = v[i];
        v[i] = v[min];
        v[min] = temp;
        printf("Iteracao %d: ", i + 1);
        exibe(v, n);
    }
}

int main(void)
{
    int v1[TAM], v2[TAM];
    srand(time(NULL));
    printf("Vetor Inicial: ");
    for (int i = 0; i < TAM; i++)
    {
        v1[i] = rand() % 101;
        v2[i] = v1[i];
    }
    exibe(v1, TAM);
    bubble(v1, TAM);
    selection(v2, TAM);
    return 0;
}
