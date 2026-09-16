#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10

// Função auxiliar para exibir o vetor na tela
void exibe(int v[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

// Algoritmo Bubble Sort clássico
void bubbleSort(int v[], int n) {
    printf("\n--- BUBBLE SORT ---\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
        printf("Iteracao %d: ", i + 1);
        exibe(v, n);
    }
}

// Algoritmo Selection Sort clássico
void selectionSort(int v[], int n) {
    printf("\n--- SELECTION SORT ---\n");
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        // Troca o elemento atual pelo menor encontrado
        int temp = v[i];
        v[i] = v[min];
        v[min] = temp;

        printf("Iteracao %d: ", i + 1);
        exibe(v, n);
    }
}

int main(void) {
    int v1[TAM], v2[TAM];
    
    srand(time(NULL));
    
    printf("Vetor Inicial: ");
    for (int i = 0; i < TAM; i++) {
        v1[i] = rand() % 101; // Gera valores de 0 a 100
        v2[i] = v1[i];        // Clona para testar o segundo algoritmo
    }
    exibe(v1, TAM);

    bubbleSort(v1, TAM);
    selectionSort(v2, TAM);

    return 0;
}
