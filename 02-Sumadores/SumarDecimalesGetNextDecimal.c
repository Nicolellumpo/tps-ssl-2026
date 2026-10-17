#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef enum {
    INICIO,
    SIGNO,
    DIGITO,
    SEPARADOR,
    FIN,
    ERROR
} Estado;

static bool EsDigitoDecimal(int c) {
    return c >= '0' && c <= '9';
}

static bool EsDigitoDecimalNoNulo(int c) {
    return c >= '1' && c <= '9';
}

static bool EsEspacio(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static int ValorDigito(int c) {
    return c - '0';
}

static bool HayOverflowPositivo(int valor, int c) {
    return valor > INT_MAX / 10 || (valor == INT_MAX / 10 && ValorDigito(c) > INT_MAX % 10);
}

static bool HayOverflowNegativo(int valor, int c) {
    return valor < INT_MIN / 10 || (valor == INT_MIN / 10 && ValorDigito(c) > -(INT_MIN % 10));
}

static bool HayOverflow(int valor, int c, int signo) {
    if (signo == 1)
        return HayOverflowPositivo(valor, c);

    if (signo == -1)
        return HayOverflowNegativo(valor, c);

    return false;
}

bool GetNextDecimal(FILE *s, int *p) {
    Estado estado = INICIO;
    int signo = 1;
    int valor = 0;

    for (int c; estado != FIN && estado != ERROR; ) {
        c = fgetc(s);

        switch (estado) {
            case INICIO:
                if (EsDigitoDecimalNoNulo(c)) {
                    valor = ValorDigito(c);
                    estado = DIGITO;
                } else if (c == '+') {
                    estado = SIGNO;
                } else if (c == '-') {
                    signo = -1;
                    estado = SIGNO;
                } else if (EsEspacio(c)) {
                    // IGNORAR
                } else {
                    estado = ERROR;
                    if (c != EOF)
                        ungetc(c, s);
                }
                break;

            case SIGNO:
                if (EsDigitoDecimalNoNulo(c)) {
                    valor = ValorDigito(c);
                    estado = DIGITO;
                } else {
                    estado = ERROR;
                    if (c != EOF)
                        ungetc(c, s);
                }
                break;

            case DIGITO:
                if (EsDigitoDecimal(c)) {
                    if (HayOverflow(valor, c, signo)) {
                        fprintf(stderr, "Error: Overflow\n");
                        estado = ERROR;
                    } else {
                        valor = valor * 10 + ValorDigito(c);
                    }
                } else if (c == '\'') {
                    estado = SEPARADOR;
                } else {
                    if (c != EOF)
                        ungetc(c, s);
                    estado = FIN;
                }
                break;

            case SEPARADOR:
                if (EsDigitoDecimal(c)) {
                    if (HayOverflow(valor, c, signo)) {
                        fprintf(stderr, "Error: Overflow\n");
                        estado = ERROR;
                    } else {
                        valor = valor * 10 + ValorDigito(c);
                        estado = DIGITO;
                    }
                } else {
                    estado = ERROR;
                    if (c != EOF)
                        ungetc(c, s);
                }
                break;

            default:
                break;
        }
    }

    if (estado == FIN) {
        *p = signo * valor;
        return true;
    }

    return false;
}

int main(void) {
    int total = 0;

    for (int n; GetNextDecimal(stdin, &n); ) {
        if (n > 0 && total > INT_MAX - n) {
            fprintf(stderr, "Error: Overflow\n");
            return 1;
        }

        if (n < 0 && total < INT_MIN - n) {
            fprintf(stderr, "Error: Overflow\n");
            return 1;
        }

        total += n;
        printf("%d\n", total);
    }

    return 0;
}
