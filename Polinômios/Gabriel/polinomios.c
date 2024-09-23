#include <stdio.h>
#include <stdlib.h>

// Define os vetores globalmente
const int N = 10;
int v[N];
char p[50], s[N];

// Para integral
float primitiva[N + 1];
char s_primitiva[N + 1];

// Funções Básicas

int conversao(char c) {
    return c - '0';
}

int size(char *poli) {
    int len = 0;
    while (poli[len] != '\0') len++;
    return len;
}

// Funções da calculadora

void printv(int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void printvf(int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%.1f ", primitiva[i]);
    printf("\n");
}

int ex(int base, int expoente) {
    int i, total = 1;
    for (i = 0; i < expoente; i++)
        total = total * base;
    return total;
}

void cria_vetor() {
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

}

float valor_float(int n) { // int n, float* v, char* s
    float resultado = (float) primitiva[0];
    
    for (int i = 1; i < N + 1; i++) { 

        if (s_primitiva[i] == '+')
            resultado += primitiva[i] * ex(n, i);
    
        else if (s_primitiva[i] == '-')
            resultado -= primitiva[i] * ex(n, i); 
        
    }
    return resultado;
}


float integral(int a, int b) {
    float area;

    primitiva[0] = 0;
    s_primitiva[0] = '0';

    for (int i = 1; i < N + 1; i++) {
        primitiva[i] = (float)v[i - 1] / i;
        s_primitiva[i] = s[i - 1];
    }
    printf("\nA primitiva é: ");
    printvf(N + 1);
    printf("\nOs sinais são: %s\n", s_primitiva);

    printf("\nO valor em %d é %.1f\n", b, valor_float(b));
    printf("O valor em %d é %.1f\n", a, valor_float(a));

    area = valor_float(b) - valor_float(a);

    return area;
}

void deriva() {
    // Função derivada vazia. Pode ser implementada futuramente
}

int valor(int n) {
    int resultado = v[0], i;

    for (i = 1; i < N; i++) {
        if (s[i] == '+')
            resultado += v[i] * ex(n, i);
        else if (s[i] == '-')
            resultado -= v[i] * ex(n, i);
    }
    return resultado;
}

int main() {
    int val, n, a = 1, b = 2;
    float area;

    printf("Digite um polinômio: \nP(x) = ");
    scanf("%49s", p);
    cria_vetor();

    printf("\nDigite o intervalo a ser calculada a área de P(x)\n");
    printf("Ponto inicial: ");
    printf("\n");
    scanf("%d", &a);
    printf("Ponto final: ");
    printf("\n");
    scanf("%d", &b);

    area = integral(a, b);

    printf("\nO valor é: %.1f\n", area);

    return 0;
}
