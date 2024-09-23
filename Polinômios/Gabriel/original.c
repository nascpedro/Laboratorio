#include <stdio.h>
#include <stdlib.h>
#define N 10

// Funções auxiliares para impressão de vetores
void printv(int* v, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void printvf(float* v, int n) {
    for (int i = 0; i < n; i++)
        printf("%.1f ", v[i]);
    printf("\n");
}

// Função para calcular potência
int ex(int base, int expoente) {
    int total = 1;
    for (int i = 0; i < expoente; i++)
        total *= base;
    return total;
}

// Função para criar vetor de coeficientes e sinais a partir de um polinômio
void cria_vetor(char* p, int* v, char* s) {
    int i, coe, exp, chave = 0, inf = 0, sup = 0, f_coe = 0;

    // Zera os vetores
    for (i = 0; i < N; i++) {
        v[i] = 0;
        s[i] = '0';
    }

    while (p[chave] != '\0') {
        if ((p[chave] == '+' || p[chave] == '-') && chave > 0) {
            sup = chave;
            exp = 0;
            coe = 1;

            for (i = inf; i < sup; i++) {
                if (p[i] == 'x')
                    exp = 1;
                if (p[i] == '^')
                    exp = p[i + 1] - '0';
                if (p[i] == '*')
                    f_coe = 1;
            }

            if (p[inf] == '+' || p[inf] == '-') {
                s[exp] = p[inf];
                if (f_coe)
                    coe = p[inf + 1] - '0';
            } else {
                s[exp] = '+';
                if (exp == 0)
                    coe = p[inf] - '0';
            }

            inf = sup;
            v[exp] = coe;
            f_coe = 0;
        }
        chave++;
    }

    // Para o último termo
    exp = 0;
    coe = 1;
    f_coe = 0;
    for (i = inf; i < chave; i++) {
        if (p[i] == 'x')
            exp = 1;
        if (p[i] == '^')
            exp = p[i + 1] - '0';
        if (p[i] == '*')
            f_coe = 1;
    }

    if (p[inf] == '+' || p[inf] == '-') {
        s[exp] = p[inf];
        if (f_coe)
            coe = p[inf + 1] - '0';
    } else {
        s[exp] = '+';
        if (exp == 0)
            coe = p[inf] - '0';
    }
    v[exp] = coe;

    // Teste para ver os vetores
    printf("Vetor v[]: ");
    for (i = 0; i < N; i++) {
            printf("%d ", v[i]);
    }
    printf("\n");

    printf("Vetor s[]: ");
    for (i = 0; i < N; i++) {
            printf("%c ", s[i]);
    }
    printf("\n");

    printf("Polinômio de entrada p[]: %s\n", p);
}

// Função para calcular o valor do polinômio para um dado x (n)
float valor_float(int n, float* v, char* s) {
    float resultado = v[0];

    for (int i = 1; i < N; i++) {
        printf("%c ", s[i]);
    }
    
    for (int i = 1; i < N + 1; i++) {
        
        if (s[i] == '+'){
            resultado += v[i] * ex(n, i);
            printf("\n%f\n", resultado);
        }
        else if (s[i] == '-'){
            resultado -= v[i] * ex(n, i);
            printf("\n%f\n", resultado);
        }
    }
    return resultado;
}

// Função para calcular a integral definida
float integral(int a, int b, int* v, char* s) {
    float primitiva[N + 1];
    char s_primitiva[N + 1];
    float area;

    primitiva[0] = 0;
    s_primitiva[0] = '0';

    for (int i = 1; i < N + 1; i++) {
        primitiva[i] = (float)v[i - 1] / i;
        s_primitiva[i] = s[i - 1];
    }

    printf("\nA primitiva é: ");
    printvf(primitiva, N + 1);
    printf("\nOs sinais são: %s\n", s_primitiva);

    printf("\nO valor em %d é %.1f\n", b, valor_float(b, primitiva, s_primitiva));
    printf("O valor em %d é %.1f\n", a, valor_float(a, primitiva, s_primitiva));

    area = valor_float(b, primitiva, s_primitiva) - valor_float(a, primitiva, s_primitiva);

    return area;
}

// Função para calcular o valor do polinômio inteiro
int valor(int n, int* v, char* s) {
    int resultado = v[0];
    for (int i = 1; i < N; i++) {
        if (s[i] == '+')
            resultado += v[i] * ex(n, i);
        else
            resultado -= v[i] * ex(n, i);
    }
    return resultado;
}

int main() {
    int v[N], val, n, a = 1, b = 2;
    float area;
    char p[50], s[N];

    printf("Digite um polinômio: \nP(x) = ");
    scanf("%49s", p);
    cria_vetor(p, v, s);

    printf("\nDigite o intervalo a ser calculada a área de P(x)\n");
    printf("\nPonto inicial: ");
    scanf("%d", &a);
    printf("\nPonto final: ");
    scanf("%d", &b);

    area = integral(a, b, v, s);
    printf("\nO valor é: %.1f\n", area);

    return 0;
}
