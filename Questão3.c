#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  QUESTÃO 03 – "A Razão de Eficiência de um Número"
  Aluna: Giovana de Souza Fontes
  Matrícula: 231038644

  Objetivo:
  Calcular a razão de eficiência de um número N, utilizando:
  - τ(N): quantidade de divisores de N
  - σ(N): soma dos divisores de N

  A razão é dada por τ(N) / σ(N).
  O programa também exibe os divisores e a fatoração prima de N.
*/

int eh_primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n;
    printf("Digite um número inteiro entre 1 e 100000: ");
    scanf("%d", &n);

    if (n < 1 || n > 100000) {
        printf("Número fora do intervalo permitido.\n");
        return 0;
    }

    float tau = 0;   // quantidade de divisores
    float sigma = 0; // soma dos divisores
    int fatores[20];
    int qtd = 0;

    int copia = n;

    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            tau++;
            sigma += i;
            if (eh_primo(i)) {
                while (copia % i == 0) {
                    fatores[qtd++] = i;
                    copia /= i;
                }
            }
        }
    }

    printf("\nDivisores de %d encontrados.\n", n);
    printf("Total de divisores (τ): %.0f\n", tau);
    printf("Soma dos divisores (σ): %.0f\n", sigma);

    printf("\nFatoração prima de %d:\n", n);
    if (eh_primo(n)) {
        printf("%d^1\n", n);
    } else {
        int atual = fatores[0];
        int cont = 1;
        for (int i = 1; i < qtd; i++) {
            if (fatores[i] == atual) cont++;
            else {
                printf("%d^%d\n", atual, cont);
                atual = fatores[i];
                cont = 1;
            }
        }
        printf("%d^%d\n", atual, cont);
    }

    printf("\nRazão de Eficiência: %.2f\n", tau / sigma);

    return 0;
}
