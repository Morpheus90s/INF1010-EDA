#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10

void exibe(int v[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

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

void selectionSort(int v[], int n) {
    printf("\n--- SELECTION SORT ---\n");
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min]) {
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

int main(void) {
    int v1[TAM], v2[TAM];
    
    srand(time(NULL)); // Garante uma lista inédita toda vez que o programa roda
    
    printf("Vetor Inicial (Sem repeticoes): ");
    for (int i = 0; i < TAM; i++) {
        int numero_valido = 0;
        int num;

        // Fica no loop até achar um número que não esteja no vetor
        while (!numero_valido) {
            num = rand() % 101; 
            numero_valido = 1; // Assume que é válido até provar o contrário

            // Verifica se o número já foi inserido nas posições anteriores
            for (int j = 0; j < i; j++) {
                if (v1[j] == num) {
                    numero_valido = 0; // Se achou repetido, quebra a validação
                    break;
                }
            }
        }

        v1[i] = num; 
        v2[i] = v1[i];       
    }
    exibe(v1, TAM);

    bubbleSort(v1, TAM);
    selectionSort(v2, TAM);

    return 0;
}

