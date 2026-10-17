#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

enum { SIMBOLOS_POR_DIGITO = 5 };

static bool EsEspacio(int c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static bool EsMorse(int c) {
    return c == '.' || c == '-';
}

static int CalcularDigito(int primer_simbolo, int cantidad_primer_tramo) {
    if (primer_simbolo == '.')
        return cantidad_primer_tramo;

    if (cantidad_primer_tramo == SIMBOLOS_POR_DIGITO)
        return 0;

    return cantidad_primer_tramo + 5;
}

static bool AcumularDigito(int *numero, int digito) {
    if (*numero > INT_MAX / 10 || (*numero == INT_MAX / 10 && digito > INT_MAX % 10))
        return false;

    *numero = *numero * 10 + digito;
    return true;
}

bool GetNextX(FILE *s, int *p) {
    int c;
    int digito;
    int numero = 0;
    int total_simbolos = 0;
    int cantidad_primer_tramo = 0;
    int primer_simbolo = '\0';
    bool en_segundo_tramo = false;
    bool hubo_digitos = false;

    inicio:
        total_simbolos = 0;
        cantidad_primer_tramo = 0;
        primer_simbolo = '\0';
        en_segundo_tramo = false;
        goto leer_caracter;

    leer_caracter:
        c = fgetc(s);

        if (c == EOF || EsEspacio(c))
            goto fin_numero;

        if (EsMorse(c))
            goto procesar_simbolo;

        goto error_caracter;

    procesar_simbolo:
        if (total_simbolos == SIMBOLOS_POR_DIGITO) {
            digito = CalcularDigito(primer_simbolo, cantidad_primer_tramo);

            if (!AcumularDigito(&numero, digito))
                goto error_desborde;

            hubo_digitos = true;
            ungetc(c, s);
            goto inicio;
        }

        if (total_simbolos == 0) {
            primer_simbolo = c;
            cantidad_primer_tramo = 1;
            total_simbolos++;
            goto leer_caracter;
        }

        if (!en_segundo_tramo && c == primer_simbolo) {
            cantidad_primer_tramo++;
            total_simbolos++;
            goto leer_caracter;
        }

        if (!en_segundo_tramo && c != primer_simbolo) {
            en_segundo_tramo = true;
            total_simbolos++;
            goto leer_caracter;
        }

        if (en_segundo_tramo && c != primer_simbolo) {
            total_simbolos++;
            goto leer_caracter;
        }

        goto error_patron;

    fin_numero:
        if (total_simbolos == 0 && !hubo_digitos) {
            if (c == EOF)
                 goto retornar;
            goto leer_caracter;
        }

        if (total_simbolos == 0)
            goto retornar;

        if (total_simbolos % SIMBOLOS_POR_DIGITO != 0)
            goto error_longitud;

        digito = CalcularDigito(primer_simbolo, cantidad_primer_tramo);

        if (!AcumularDigito(&numero, digito))
            goto error_desborde;

        hubo_digitos = true;
        goto retornar;

    retornar:
        if (hubo_digitos) {
            *p = numero;
            return true;
        }
        return false;

    error_longitud:
        fprintf(stderr, "Error: Digito Morse invalido (cantidad de simbolos erronea)\n");
        return false;

    error_caracter:
        fprintf(stderr, "Error: Digito Morse invalido (caracter erroneo)\n");
        return false;

    error_patron:
        fprintf(stderr, "Error: Digito Morse invalido (mas de dos tramos de simbolos)\n");
        return false;

    error_desborde:
        fprintf(stderr, "Error: Overflow\n");
        return false;
}

int main(void) {
    int total = 0;

    for (int n; GetNextX(stdin, &n); ) {
        if (total > INT_MAX - n) {
            fprintf(stderr, "Error: Overflow\n");
            return 1;
        }

        total += n;
        printf("%d\n", total);
    }

    return 0;
}
