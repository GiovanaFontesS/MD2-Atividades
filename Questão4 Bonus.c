#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

/*
  QUESTÃO 04 – Bônus: Cálculo Modular com Inverso e Potência
  Aluna: Giovana de Souza Fontes
  Matrícula: 231038644

  Objetivo:
  Este programa realiza operações modulares relacionadas à aritmética
  modular, incluindo:
  - cálculo do inverso modular,
  - multiplicação modular,
  - e exponenciação modular rápida.

  Saída esperada:
  Mostra o inverso encontrado, a multiplicação modular e o resultado final
  da congruência.
*/

// Cálculo do MDC com exibição dos passos
int calcular_mdc(int a, int b) {
    int resto;
    while (b != 0) {
        resto = a % b;
        printf("MDC: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}

// Algoritmo estendido de Euclides para encontrar o inverso modular
int inverso_modular(int a, int m) {
    int m_original = m, q, t;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m_original;

    printf("O inverso de %d em relação a %d é %d\n", A, B, x1);
    return x1;
}

// Exponenciação modular rápida
long long potencia_modular(long long base, long long exp, long long mod) {
    long long resultado = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            resultado = (resultado * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return resultado;
}

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    int H, G, Zn, x, n1;

    printf("Giovana de Souza Fontes - Matrícula: 231038644\n");
    printf("=== Questão 04 - Bônus ===\n");

    printf("Digite o valor de H: ");
    scanf("%d", &H);
    printf("Digite o valor de G: ");
    scanf("%d", &G);
    printf("Digite o valor de Zn: ");
    scanf("%d", &Zn);
    printf("Digite o valor de x: ");
    scanf("%d", &x);
    printf("Digite o valor de n1: ");
    scanf("%d", &n1);

    int inverso = inverso_modular(G, Zn);
    int a = (H * inverso) % Zn;

    printf("Multiplicação modular: (%d * %d) mod %d = %d\n", H, inverso, Zn, a);

    int resultado = potencia_modular(a, x, n1);

    printf("O inverso de %d é %d\n", G, inverso);
    printf("Resultado final da congruência: %d\n", resultado);

    return 0;
}
