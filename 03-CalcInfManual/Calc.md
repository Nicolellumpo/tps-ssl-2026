# Calculadora Infija — Especificación

Calculadora de expresiones aritméticas infijas con variables. Operaciones: suma `+`, resta `-`, multiplicación `*`, división `/`, potencia `^` y asignación `=`.

La representación original elegida por el equipo es el **código Morse para los números naturales**. Los operadores, los paréntesis y los identificadores se escriben con sus símbolos habituales.

Dígitos Morse (5 símbolos, a lo sumo dos tramos):

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `-----` | `.----` | `..---` | `...--` | `....-` | `.....` | `-....` | `--...` | `---..` | `----.` |

## 1. Especificación del nivel léxico (Regex tipo flex)

```lex
DIGITO      (-----|\.----|\.\.---|\.\.\.--|\.\.\.\.-|\.\.\.\.\.|-\.\.\.\.|--\.\.\.|---\.\.|----\.)
SEP         [ \t\r]+
FINPALABRA  [^.-]

%%
{DIGITO}+/{FINPALABRA}                  return NUMERO;
[a-z]+                                  return IDENTIFICADOR;
"+"                                     return '+';
"-"/{FINPALABRA}                        return '-';
"*"                                     return '*';
"/"                                     return '/';
"^"                                     return '^';
"="                                     return '=';
"("                                     return '(';
")"                                     return ')';
{SEP}                                   ;
\n                                      return FIN_LINEA;
[.-]+                                   return ERROR;
.                                       return ERROR;
<<EOF>>                                  return FIN_ENTRADA;
```

## Tokens

| Token | Lexema | Nota |
| --- | --- | --- |
| `NUMERO` | uno o más dígitos Morse **pegados**, sin espacios | `..---....-` es el número `24` |
| `IDENTIFICADOR` | `[a-z]+` | nombre de variable |
| `'+'` `'-'` `'*'` `'/'` `'^'` `'='` | el propio símbolo | |
| `'('` `')'` | el propio símbolo | |
| `FIN_LINEA` | `\n` | termina la sentencia |
| `FIN_ENTRADA` | fin de archivo | el scanner lo devuelve una vez agotada la entrada; si la última línea no termina en `\n`, también cierra esa sentencia |
| `ERROR` | secuencia no reconocida | el parser decide el mensaje |

## Reglas léxicas

- Una **palabra Morse** es una secuencia maximal de `.` y `-`. Tiene que ser un dígito completo o el operador `-` solo.
- El contexto posterior `/{FINPALABRA}` obliga a que cada token termine en una palabra completa. En la implementación, el fin de archivo cumple el papel de un carácter que no es `.` ni `-`.
- **Un número son dígitos Morse pegados** (igual que en el TP de Sumadores). Los espacios separan tokens: `..--- ....-` son dos números (`2` y `4`) y es un error sintáctico, no el número `24`.
- **El `-` operador se separa con espacios de las palabras Morse vecinas.** `..--- + ...--` es válido, pero `..----...--` es una sola palabra inválida.
- Los dígitos `0`-`9` no pertenecen al lenguaje de entrada. Los números se escriben en Morse.
- Los separadores son espacios, tabs y `\r`, y se descartan.

---

## 2. Especificación del nivel sintáctico (BNF tipo Bison)

```bison
%token NUMERO IDENTIFICADOR FIN_LINEA FIN_ENTRADA
%start translation-unit

%%

translation-unit:
      %empty
    | translation-unit statement
    ;

statement:
      finSentencia
    | expresion finSentencia
    | IDENTIFICADOR '=' expresion finSentencia
    ;

finSentencia:
      FIN_LINEA
    | FIN_ENTRADA
    ;

expresion:
      sumaOperacion
    ;

sumaOperacion:
      multiplicacionOperacion
    | sumaOperacion '+' multiplicacionOperacion
    | sumaOperacion '-' multiplicacionOperacion
    ;

multiplicacionOperacion:
      expresionNegativa
    | multiplicacionOperacion '*' expresionNegativa
    | multiplicacionOperacion '/' expresionNegativa
    ;

expresionNegativa:
      potenciaOperacion
    | '-' expresionNegativa
    ;

potenciaOperacion:
      expresionBasica
    | expresionBasica '^' expresionNegativa
    ;

expresionBasica:
      NUMERO
    | IDENTIFICADOR
    | '(' expresion ')'
    ;
```

**Precedencia y asociatividad** (de menor a mayor precedencia)

| Nivel | Operadores | Asociatividad |
| --- | --- | --- |
| 1 | `+` `-` binarios | izquierda |
| 2 | `*` `/` | izquierda |
| 3 | `-` unario | derecha |
| 4 | `^` | derecha |

- En la gramática, `expresionNegativa` contiene a `potenciaOperacion`, así que `-2 ^ 2` es `-(2 ^ 2)`.
- El exponente es un `expresionNegativa`, así que `2 ^ -1` es sintácticamente válido y `2 ^ 3 ^ 2` es `2 ^ (3 ^ 2)`.
- Una línea vacía es una sentencia válida y no produce salida.
- La gramática no tiene conflictos en Bison. Para el descenso recursivo, `statement` necesita **dos tokens de lookahead**: `IDENTIFICADOR` seguido de `=` es una asignación, y seguido de cualquier otra cosa es una expresión.

**Correspondencia con la implementación** (una función por no-terminal)

| No-terminal | Función |
| --- | --- |
| `translation-unit` | `Parse` |
| `statement` | `Statement` |
| `finSentencia` | `FinSentencia` |
| `expresion` | `Expresion` |
| `sumaOperacion` | `SumaOperacion` |
| `multiplicacionOperacion` | `MultiplicacionOperacion` |
| `expresionNegativa` | `ExpresionNegativa` |
| `potenciaOperacion` | `PotenciaOperacion` |
| `expresionBasica` | `ExpresionBasica` |

Las reglas recursivas a izquierda (`translation-unit`, `sumaOperacion`, `multiplicacionOperacion`) no se pueden implementar directamente en descenso recursivo. Se implementan con un bucle: la función llama primero al no-terminal de menor nivel y luego itera mientras el siguiente token sea uno de sus operadores.

## Ejemplos de precedencia y asociatividad

| Expresión | Árbol implícito |
| ------------ | ---------------- |
| `2 + 3 * 4` | `2 + (3 * 4)` |
| `(2 + 3) * 4` | `(2 + 3) * 4` |
| `10 - 3 - 2` | `(10 - 3) - 2` |
| `20 / 5 / 2` | `(20 / 5) / 2` |
| `2 ^ 3 ^ 2` | `2 ^ (3 ^ 2)` |
| `2 ^ -1` | `2 ^ (-1)` |
| `-2 ^ 2` | `-(2 ^ 2)` |

(En los ejemplos los números se muestran en decimal por legibilidad; en la entrada real van en Morse.)

---

## 3. Especificación del nivel semántico (lenguaje natural)

*SUGERENCIA HECHA POR NICOLAS DEGANO**
  
- **Números:** `NUMERO` vale el entero decimal formado por sus dígitos Morse (`..---....-` vale 24). Si no entra en `long`, es un error de desborde.
- **Variables:** hay una tabla de variables (nombre → valor). `x = expresion` evalúa la expresión, guarda el valor en `x` y no imprime nada. Usar una variable que no fue asignada es un error.
- **Expresión como sentencia:** se evalúa y se imprime el resultado en una línea. La línea vacía no hace nada.
- **Operadores:** `+ - * /` y `^` operan con enteros. `/` es división entera y dividir por cero es un error. `^` es potencia entera: un exponente negativo es un error (el resultado no sería entero), salvo que la base sea 1 o -1. El `-` unario cambia el signo.
- **Desborde:** si un resultado no entra en `long`, es un error.
- **Errores:** se informan por `stderr` con el número de línea. Tras un error se descarta el resto de la línea, se sigue con la siguiente y el programa termina con código 1 al final.
- **Última línea sin salto de línea:** `FIN_ENTRADA` también termina la sentencia, así que una última línea sin `\n` se evalúa igual. Después de `FIN_ENTRADA` el parser deja de leer.
- **Interfaz del scanner:** `Token GetNextToken(void)`, que lee de `stdin` con `getchar`. `Token` es `{ TokenType type; long value; char name[N]; }`: `value` se usa en `NUMERO` y `name` en `IDENTIFICADOR`. `name` tiene `MAX_NAME` = 64 caracteres. En un `ERROR`, `name` guarda el lexema (truncado si es largo) para que el parser lo muestre. El scanner usa `ungetc` para devolver el carácter que corta cada lexema. El parser guarda el token adelantado que necesita para el lookahead de 2 tokens.

*SUGERENCIA HECHA POR NICOLAS DEGANO**

## Sistemas de tipos

Tipo_Numerico: Subdividido en ENTERO y REAL.
OP_FACT: Argumento de tipo ENTERO de valor mayor o igual a 0.

Sistema de tipos:

ERR_DIV_POR_CERO: El denominador de una división es 0.
ERROR_FACTORIAL_INVALIDO: Aplicar factorial con un número negativo o con parte decimal.
ERROR_PILA_UNDERFLOW: No se cumple la aridad para el operador actual.

## BNF

< Expresion > ::= < Termino > [ .-.-. | -....- ] < Termino > (Suma / Resta)

< Termino > ::= < Potencia > [ -..- | -..-. ] < Potencia > (Multiplicación / División)

< Potencia > ::= < Factorial > [ .---.] < Potencia > (Potencia)

< Literal > ::= [ Morse_Digitos ] (Hojas Numéricas)

## Especificación

|Token|Tipo de Nodo|Aridad|Restricción semántica|
|-----|---------------|---------------|----------------------|
|+|Binario|2|-|
|-|Binario|2|-|
|x|Binario|2|-|
|/|Binario|2|El denominador debe ser distinto de 0|
|^|Binario|2|Si la base es negativa, el exponente debe ser entero|
|!|Unario|1|El operando debe ser un entero no negativo|

## Implementacion

```bison
typedef enum {
    OK = 0,
    ERR_DIV_POR_CERO,
    ERR_POTENCIA_NEGATIVA,
    ERR_DESBORDE,
    ERROR_VARIABLE_NO_ASIGNADA
} ErrorSemantico;

typedef enum {
    NODO_NUMERO,
    NODO_OP_UNARIO,
    NODO_OP_BINARIO
} TipoNodo;

typedef enum {
    sumaOperacion, 
    restaOperacion,  
    multiplicacionOperacion, 
    divisionOperacion, 
    potenciaOperacion
} TipoOperacion;

typedef struct NodoAST {
    TipoNodo tipo;
    union {
        long valor; 
        struct {
            TipoOperacion op;
            struct NodoAST *hijo;
        } unario;     
        struct {
            TipoOperacion op;
            struct NodoAST *izq;
            struct NodoAST *der;
        } binario;    
    } data;
} NodoAST;



long seguro_suma(long a, long b, ErrorSemantico *err) {
    if ((b > 0 && a > LONG_MAX - b) || (b < 0 && a < LONG_MIN - b)) {
        *err = ERR_DESBORDE;
        return 0;
    }
    return a + b;
}

long seguro_resta(long a, long b, ErrorSemantico *err) {
    if ((b > 0 && a < LONG_MIN + b) || (b < 0 && a > LONG_MAX + b)) {
        *err = ERR_DESBORDE;
        return 0;
    }
    return a - b;
}

long seguro_multiplicacion(long a, long b, ErrorSemantico *err) {
    if (a > 0) {
        if (b > 0) { if (a > LONG_MAX / b) { *err = ERR_DESBORDE; return 0; } }
        else { if (b < LONG_MIN / a) { *err = ERR_DESBORDE; return 0; } }
    } else if (a < 0) {
        if (b > 0) { if (a < LONG_MIN / b) { *err = ERR_DESBORDE; return 0; } }
        else { if (b < LONG_MAX / a) { *err = ERR_DESBORDE; return 0; } }
    }
    return a * b;
}

long seguro_potencia(long base, long exp, ErrorSemantico *err) {
   
    if (exp < 0) {
        if (base == 1) return 1;
        if (base == -1) return (exp % 2 == 0) ? 1 : -1;
        *err = ERR_POTENCIA_NEGATIVA;
        return 0;
    }
    
    long resultado = 1;
    long b = base;
    while (exp > 0) {
        if (exp % 2 == 1) {
            resultado = seguro_multiplicacion(resultado, b, err);
            if (*err != OK) return 0;
        }
        exp /= 2;
        if (exp > 0) {
            b = seguro_multiplicacion(b, b, err);
            if (*err != OK) return 0;
        }
    }
    return resultado;
}


long evaluar_ast(NodoAST* nodo, ErrorSemantico *err) {
    if (!nodo || *err != OK) return 0;

    if (nodo->tipo == NODO_NUMERO) {
        return nodo->data.valor;
    }

    if (nodo->tipo == NODO_OP_UNARIO) {
        long val_hijo = evaluar_ast(nodo->data.unario.hijo, err);
        if (*err != OK) return 0;
        
    
        if (val_hijo == LONG_MIN) {
            *err = ERR_DESBORDE;
            return 0;
        }
        return -val_hijo;
    }

    if (nodo->tipo == NODO_OP_BINARIO) {
        long val_izq = evaluar_ast(nodo->data.binario.izq, err);
        long val_der = evaluar_ast(nodo->data.binario.der, err);
        if (*err != OK) return 0;

        switch (nodo->data.binario.op) {
            case sumaOperacion:  
                return seguro_suma(val_izq, val_der, err);
                
            case restaOperacion: 
                return seguro_resta(val_izq, val_der, err);
                
            case multiplicacionOperacion:  
                return seguro_multiplicacion(val_izq, val_der, err);
                
            case potenciaOperacion:   
                return seguro_potencia(val_izq, val_der, err);
                
            case divisionOperacion:
                if (val_der == 0) {
                    *err = ERR_DIV_POR_CERO;
                    return 0;
                }
                if (val_izq == LONG_MIN && val_der == -1) {
                    *err = ERR_DESBORDE;
                    return 0;
                }
                return val_izq / val_der; 
                
            default: 
                break;
        }
    }
  
}
```

## 4. Compilación y uso

El programa lee de `stdin`, una sentencia por línea.

- Archivos: `Scanner.h`, `Scanner.c`, `Scanner_test.c` (imprime un token por línea para probar el scanner), `Parser.h`, `Parser.c`, `main.c` y `Makefile`.
- `make` compila; `make test` corre los casos de prueba y compara con `diff`.

## 5. Decisiones y limitaciones

- Los dígitos de un número van pegados; los espacios separan tokens.
- El `-` operador necesita espacios con las palabras Morse vecinas.
- Aritmética entera con `long`.
- Un identificador puede tener hasta 63 letras; uno más largo es `ERROR`. La regex `[a-z]+` no tiene límite, pero el buffer del token sí.
- Un número que no entra en `long` y una palabra Morse inválida salen ambos como `ERROR`, así que el parser no distingue el motivo.
- Los números se escriben solo en Morse. Los dígitos `0`-`9` son `ERROR`.
