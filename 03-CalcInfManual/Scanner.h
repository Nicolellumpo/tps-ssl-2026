#ifndef SCANNER_H
#define SCANNER_H

/* Scanner de la calculadora infija.
Implementa el nivel lexico de Calc.md. Lee de stdin con getchar y devuelve un token por llamada. */

enum { MAX_NAME = 64 };   /* Capacidad de Token.name, incluido el '\0' */

/* Los operadores y los parentesis son su propio caracter ('+', '-', '*', '/', '^', '=', '(', ')').
El resto de los tokens empieza en 256 para no chocar. */
enum {
    NUMERO = 256,
    IDENTIFICADOR,
    FIN_LINEA,
    FIN_ENTRADA,
    ERROR
};

typedef struct {
    int  type;              /* NUMERO, IDENTIFICADOR, FIN_LINEA, FIN_ENTRADA, ERROR o un caracter */
    long value;             /* Valido si type == NUMERO */
    char name[MAX_NAME];    /* IDENTIFICADOR: el nombre. ERROR: el lexema (truncado si es largo) */
} Token;

/* Pre:  Flujo stdin esta abierto para lectura.
   Post: Consume de stdin el proximo lexema y devuelve su token.
         Si el lexema no cumple la especificacion (palabra Morse invalida, numero que no entra en long, identificador demasiado largo o caracter ajeno al lenguaje) devuelve ERROR con el lexema en name.
         Al agotarse la entrada devuelve FIN_ENTRADA, y lo sigue devolviendo en las llamadas siguientes. */
Token GetNextToken(void);

#endif
