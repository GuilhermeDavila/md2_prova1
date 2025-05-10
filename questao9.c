#include <stdio.h>

int mdc(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int eh_primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int inverso_modular(int g, int n, int *inverso) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = g;

    while (novo_r != 0) {
        int quociente = r / novo_r;
        int temp = novo_t;
        novo_t = t - quociente * novo_t;
        t = temp;

        temp = novo_r;
        novo_r = r - quociente * novo_r;
        r = temp;
    }

    if (r > 1) return 0;

    if (t < 0) t += n;
    *inverso = t;
    return 1;
}

int phi(int n) {
    int resultado = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            resultado -= resultado / i;
        }
    }
    if (n > 1)
        resultado -= resultado / n;
    return resultado;
}

int potencia_modular(int base, int expoente, int mod) {
    int resultado = 1;
    base = base % mod;
    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % mod;
        base = (base * base) % mod;
        expoente /= 2;
    }
    return resultado;
}

int main() {
    int H, G, n, x, n1;

    printf("Digite os valores de H, G, n, x, n1:\n");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    printf("\nPasso 1: Verificando se G e n sao primos:\n");
    if (!eh_primo(G) || !eh_primo(n)) {
        printf("G ou n nao sao primos. A divisao modular nao e possivel.\n");
        return 1;
    }
    printf("G e n sao primos.\n");

    printf("\nPasso 2: Calculando o inverso de G em Z%d:\n", n);
    int g_inv;
    if (!inverso_modular(G, n, &g_inv)) {
        printf("O inverso de G nao existe em Z%d. A divisao nao e possivel.\n", n);
        return 1;
    }
    printf("Inverso de G em Z%d e: %d\n", n, g_inv);

    printf("\nPasso 3: Calculando a = H / G em Z%d:\n", n);
    int a = (H * g_inv) % n;
    printf("a = %d\n", a);

    printf("\nPasso 4: Verificando se a e n1 sao coprimos:\n");
    if (mdc(a, n1) != 1) {
        printf("a e n1 nao sao coprimos.\n");
    } else {
        printf("a e n1 sao coprimos.\n");
    }

    printf("\nPasso 5: Verificando se n1 e primo:\n");
    int x1;
    if (eh_primo(n1)) {
        printf("n1 e primo. Aplicando Pequeno Teorema de Fermat.\n");
        x1 = n1 - 1;
    } else {
        printf("n1 nao e primo. Aplicando Teorema de Euler.\n");
        x1 = phi(n1);
        printf("phi(%d) = %d\n", n1, x1);
    }

    printf("\nPasso 6: Decompondo x = x1 * q + r:\n");
    int q = x / x1;
    int r = x % x1;
    printf("x = %d = %d * %d + %d\n", x, x1, q, r);

    printf("\nPasso 7: Calculando valores intermediarios:\n");
    int x2 = potencia_modular(a, x1, n1);
    printf("x2 = a^x1 mod n1 = %d^%d mod %d = %d\n", a, x1, n1, x2);

    int x2q = potencia_modular(x2, q, n1);
    printf("x2^q mod n1 = %d^%d mod %d = %d\n", x2, q, n1, x2q);

    int ar = potencia_modular(a, r, n1);
    printf("a^r mod n1 = %d^%d mod %d = %d\n", a, r, n1, ar);

    printf("\nPasso 8: Resultado final:\n");
    int resultado = (x2q * ar) % n1;
    printf("Resultado final: ((%d^%d)^%d * %d^%d) mod %d = %d\n", a, x1, q, a, r, n1, resultado);

    return 0;
}
