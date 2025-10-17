#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
  QUESTÃO 01 – RSA com Pollard Rho
  Aluna: Giovana de Souza Fontes
  Matrícula: 231038644

  Objetivo:
  Este programa realiza uma simulação do processo de geração e uso de chaves RSA.
  Ele inclui três etapas principais:
  1) Fatoração dos números compostos usando o método de Pollard Rho.
  2) Geração das chaves pública e privada a partir dos fatores encontrados.
  3) Criptografia e descriptografia de uma palavra informada pelo usuário.

  Saída esperada:
  O programa mostra detalhadamente cada passo, exibindo os fatores encontrados,
  as chaves geradas, o processo de codificação e o resultado final da
  descriptografia (comparando com a mensagem original).
*/

// Função para calcular o MDC (Algoritmo de Euclides)
int calcular_mdc(int a, int b) {
    int resto;
    while (b != 0) {
        resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

// Verifica se o número é primo
int eh_primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Retorna 1 se forem coprimos, 0 caso contrário
int sao_coprimos(int a, int b) {
    return (calcular_mdc(a, b) == 1);
}

// Algoritmo Estendido de Euclides (para achar o inverso modular)
int inverso_modular(int a, int b) {
    int a_inicial = a, b_inicial = b;
    int x0 = 1, y0 = 0, x1 = 0, y1 = 1;

    while (b != 0) {
        int quociente = a / b;
        int resto = a % b;

        int x_temp = x0 - quociente * x1;
        int y_temp = y0 - quociente * y1;

        a = b;
        b = resto;
        x0 = x1;
        y0 = y1;
        x1 = x_temp;
        y1 = y_temp;
    }

    if (a != 1) {
        printf("Não há inverso de %d módulo %d (MDC != 1)\n", b_inicial, a_inicial);
        return 0;
    }

    int inverso = (y0 % a_inicial + a_inicial) % a_inicial;
    printf("Inverso de %d mod %d = %d\n", b_inicial, a_inicial, inverso);
    return inverso;
}

// Método de Pollard Rho para fatoração
int pollard_rho(int x0, int n) {
    if (n % 2 == 0) return 2;

    int x = x0;
    int y = x0;
    int d = 1;
    int iter = 1;

    printf("\nExecutando método de Pollard Rho para N = %d...\n", n);

    while (d == 1) {
        x = (x * x + 1) % n;
        y = (y * y + 1) % n;
        y = (y * y + 1) % n;

        d = calcular_mdc(abs(x - y), n);
        printf("Iteração %d: x=%d, y=%d, fator=%d\n", iter++, x, y, d);
    }

    if (d == n)
        printf("Fator não encontrado.\n");
    else
        printf("Fator encontrado: %d\n", d);

    return d;
}

// Exponenciação modular simples
int exp_modular(int base, int exp, int mod) {
    int resultado = 1;
    for (int i = 0; i < exp; i++) {
        resultado = (resultado * base) % mod;
    }
    return resultado;
}

int main() {
    printf("=== Questão 01 - RSA com Pollard Rho ===\n");

    int n1, n2;
    do {
        printf("Digite dois números compostos entre 100 e 9999 (ex: 143 e 221):\n");
        scanf("%d %d", &n1, &n2);
    } while (n1 < 100 || n2 < 100 || n1 > 9999 || n2 > 9999 || eh_primo(n1) || eh_primo(n2));

    int semente = 2;
    int p = pollard_rho(semente, n1);
    int q = pollard_rho(semente, n2);

    printf("\nFatores encontrados:\n");
    printf("p = %d\n", p);
    printf("q = %d\n", q);

    int n = p * q;
    int z = (p - 1) * (q - 1);

    printf("\nCálculo das chaves:\n");
    printf("n = %d\n", n);
    printf("z = %d\n", z);

    int e = 2;
    while (e < z && !sao_coprimos(e, z)) e++;
    printf("Expoente público e = %d\n", e);

    int d = inverso_modular(z, e);
    if (d == 0) {
        printf("Erro ao calcular d.\n");
        return 0;
    }
    printf("Expoente privado d = %d\n", d);

    printf("\nChave pública: (e = %d, n = %d)\n", e, n);
    printf("Chave privada: (d = %d, n = %d)\n", d, n);

    char mensagem[100];
    printf("\nDigite uma palavra em maiúsculas (sem espaços): ");
    scanf("%99s", mensagem);

    int len = strlen(mensagem);
    int *cript = malloc(len * sizeof(int));
    char *decript = malloc(len + 1);

    printf("\nCriptografando...\n");
    for (int i = 0; i < len; i++) {
        int m = mensagem[i] - 54;
        cript[i] = exp_modular(m, e, n);
        printf("%c -> %d\n", mensagem[i], cript[i]);
    }

    printf("\nMensagem criptografada:\n");
    for (int i = 0; i < len; i++) printf("%d ", cript[i]);
    printf("\n");

    printf("\nDescriptografando...\n");
    for (int i = 0; i < len; i++) {
        int dec = exp_modular(cript[i], d, n);
        decript[i] = dec + 54;
        printf("%d -> %c\n", cript[i], decript[i]);
    }
    decript[len] = '\0';

    printf("\nMensagem final: %s\n", decript);

    if (strcmp(mensagem, decript) == 0)
        printf("\nVerificação: SUCESSO - mensagem restaurada corretamente!\n");
    else
        printf("\nVerificação: FALHA - mensagem diferente da original.\n");

    free(cript);
    free(decript);

    return 0;
}
