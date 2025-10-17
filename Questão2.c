#include <stdio.h>

#define VERBOSE 1 // Define se programa vai exibir detalhes das etapas

/*
  QUESTÃO 02 – "Chaves Periódicas"
  Aluna: Giovana de Souza Fontes
  Matrícula: 231038644

  Objetivo:
  Este programa recebe o número de chaves e seus ciclos de ativação e
  calcula o primeiro ano (de 1 a 50) em que todas podem ser ativadas
  simultaneamente. Para isso, utiliza o cálculo do MMC entre os ciclos
  fornecidos, com base no algoritmo de Euclides (para o MDC).

  Saída esperada:
  - Caso o ano de sincronização esteja dentro do limite (≤ 50), o programa
    mostra esse valor.
  - Caso contrário, exibe a mensagem de que não é possível sincronizar
    todas as chaves nesse intervalo.
*/

// Função auxiliar para exibir o vetor de ciclos
void mostrar_ciclos(const long long v[], int n) {
    if (!VERBOSE) return;
    printf("Ciclos informados: [");
    for (int i = 0; i < n; i++) {
        printf("%lld", v[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

// Cálculo do MDC usando o algoritmo de Euclides
long long calcular_mdc(long long a, long long b) {
    long long resto;
    while (b != 0) {
        resto = a % b;
        printf("Etapa MDC: %lld mod %lld = %lld\n", a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}

// Cálculo do MMC usando a relação: mmc(a,b) = (a / mdc(a,b)) * b
long long calcular_mmc(long long a, long long b) {
    if (VERBOSE)
        printf("\n[MMC] Calculando MMC de %lld e %lld\n", a, b);
    
    long long divisor = calcular_mdc(a, b);
    long long resultado = (a / divisor) * b;

    if (VERBOSE)
        printf("[MMC] Resultado: (%lld / %lld) * %lld = %lld\n", a, divisor, b, resultado);

    return resultado;
}

int main(void) {
    int N;
    long long ciclos[10];
    long long resultado = 1;

    printf("Giovana de Souza Fontes - Matrícula: 231038644\n");
    printf("=== Questão 02 - Chaves Periódicas ===\n\n");

    printf("Digite o número de chaves (1 a 10): ");
    if (scanf("%d", &N) != 1 || N < 1 || N > 10) {
        printf("Entrada inválida. O valor de N deve estar entre 1 e 10.\n");
        return 0;
    }

    printf("Digite os ciclos de ativação (2 a 20): ");
    for (int i = 0; i < N; i++) {
        if (scanf("%lld", &ciclos[i]) != 1 || ciclos[i] < 2 || ciclos[i] > 20) {
            printf("Entrada inválida. Os ciclos devem estar entre 2 e 20.\n");
            return 0;
        }
    }

    if (VERBOSE) {
        printf("\n--- Etapa 1: Identificação dos ciclos ---\n");
        printf("Cada chave é ativada em múltiplos do seu ciclo (0, Ci, 2*Ci, ...).\n");
        mostrar_ciclos(ciclos, N);
    }

    if (VERBOSE)
        printf("\n--- Etapa 2: Cálculo acumulado do MMC ---\n");

    for (int i = 0; i < N; i++) {
        long long antes = resultado;
        resultado = calcular_mmc(resultado, ciclos[i]);
        if (VERBOSE)
            printf("Após incluir C%d = %lld: novo MMC = %lld\n", i + 1, ciclos[i], resultado);
    }

    if (VERBOSE) {
        printf("\n--- Etapa 3: Verificação do limite de 50 anos ---\n");
        printf("MMC calculado = %lld\n", resultado);
    }

    if (resultado > 50) {
        printf("Não é possível sincronizar todas as chaves dentro de 50 anos.\n");
        if (VERBOSE)
            printf("(O primeiro encontro ocorre no ano %lld, acima do limite.)\n", resultado);
    } else {
        printf("%lld\n", resultado);
        if (VERBOSE)
            printf("(As chaves sincronizam no ano %lld.)\n", resultado);
    }

    if (VERBOSE) {
        printf("\n--- Resumo ---\n");
        printf("• O MDC foi calculado com o algoritmo de Euclides.\n");
        printf("• O MMC foi obtido pela relação MMC = (a / MDC) * b.\n");
        printf("• O resultado final é o menor múltiplo comum de todos os ciclos.\n");
    }

    return 0;
}
