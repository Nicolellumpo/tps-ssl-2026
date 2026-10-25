#include "Scanner.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

enum { SIMBOLOS_POR_DIGITO = 5 };   /* Cada digito Morse tiene 5 simbolos */

static bool EsSimboloMorse(int c) {
    return c == '.' || c == '-';
}

static bool EsMinuscula(int c) {
    return c >= 'a' && c <= 'z';
}

static bool EsSeparador(int c) {
    return c == ' ' || c == '\t' || c == '\r';
}

/* Pre:  el digito tiene a lo sumo dos tramos y primerSimbolo abre el primero.
   Post: devuelve el valor del digito Morse (0 a 9). */
static int CalcularDigito(char primerSimbolo, int conteoPrimerTramo) {
    if (primerSimbolo == '.')
        return conteoPrimerTramo;
    if (conteoPrimerTramo == SIMBOLOS_POR_DIGITO)
        return 0;
    return conteoPrimerTramo + 5;
}

/* Post: si *numero * 10 + digito entra en long lo guarda y devuelve true;
         si no, deja *numero intacto y devuelve false. */
static bool AcumularDigito(long *numero, int digito) {
    if (*numero > LONG_MAX / 10 || (*numero == LONG_MAX / 10 && digito > LONG_MAX % 10))
        return false;
    
    *numero = *numero * 10 + digito;
    return true;
}

/* Lee una palabra Morse: la secuencia maximal de '.' y '-' que empieza en
   primero. Es el operador '-' si es un '-' solo; es NUMERO si son uno o mas
   digitos completos pegados; en cualquier otro caso es ERROR. */
static Token ScanPalabraMorse(int primero) {
    Token token = {0};
    long numero = 0;
    int  c = primero;
    int  longitud = 0;              /* Simbolos de la palabra */
    int  simbolosEnDigito = 0;
    int  conteoPrimerTramo = 0;
    char primerSimbolo = '\0';
    bool enSegundoTramo = false;
    bool valida = true;             /* false si algun digito tiene mas de dos tramos */
    bool desborde = false;

    while (EsSimboloMorse(c)) {
        char simbolo = (char)c;

        if (longitud < MAX_NAME - 1)
            token.name[longitud] = simbolo;
        
        longitud++;

        if (simbolosEnDigito == 0) {
            primerSimbolo = simbolo;
            conteoPrimerTramo = 1;
            enSegundoTramo = false;
        } else if (!enSegundoTramo && simbolo == primerSimbolo) {
            conteoPrimerTramo++;
        } else if (!enSegundoTramo) {
            enSegundoTramo = true;
        } else if (simbolo == primerSimbolo) {      /* Tercer tramo */
            valida = false;
        }
        
        simbolosEnDigito++;

        if (simbolosEnDigito == SIMBOLOS_POR_DIGITO) {
            if (valida && !desborde && !AcumularDigito(&numero, CalcularDigito(primerSimbolo, conteoPrimerTramo))) {
                desborde = true;
            }
            simbolosEnDigito = 0;
        }
        
        c = getchar();
    }
    if (c != EOF)
        ungetc(c, stdin);

    if (longitud == 1 && token.name[0] == '-') {
        token.type = '-';
        return token;
    }
    
    if (!valida || desborde || simbolosEnDigito != 0) {
        token.type = ERROR;
        return token;
    }
    
    token.type = NUMERO;
    token.value = numero;
    token.name[0] = '\0';
    return token;
}

/* Lee un identificador: letras minusculas consecutivas a partir de primero. */
static Token ScanIdentificador(int primero) {
    Token token = {0};
    int c = primero;
    int longitud = 0;

    while (EsMinuscula(c)) {
        if (longitud < MAX_NAME - 1) {
            token.name[longitud] = (char)c;
        }
        
        longitud++;
        c = getchar();
    }
    
    if (c != EOF)
        ungetc(c, stdin);

    token.type = (longitud < MAX_NAME) ? IDENTIFICADOR : ERROR;
    return token;
}

Token GetNextToken(void) {
    Token token = {0};
    int c;

    do c = getchar();
    while (EsSeparador(c));

    if (c == EOF) {
        token.type = FIN_ENTRADA;
        return token;
    }
    
    if (c == '\n') {
        token.type = FIN_LINEA;
        return token;
    }
    
    if (EsSimboloMorse(c))
        return ScanPalabraMorse(c);
    
    if (EsMinuscula(c))
        return ScanIdentificador(c);

    switch (c) {
        case '+': case '*': case '/': case '^': case '=': case '(': case ')':
            token.type = c;
            return token;
        
        default:
            token.type = ERROR;
            token.name[0] = (char)c;
            return token;
    }
}
