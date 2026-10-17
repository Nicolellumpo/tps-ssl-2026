# Trabajo práctico 1: Operaciones de Strings

Este trabajo tiene tres partes: un análisis comparativo, el desarrollo de operaciones, y una última parte de programas que aplican las operaciones desarrolladas.

El análisis comparativo es sobre el tipo de dato String en el lenguaje de programación C versus otro lenguaje de programación a elección; mientras que el desarrollo está basado en los ejercicios 20 y 21 del Capítulo 1 del Volumen 1 de Much2012:

> **Ejercicio 20**
> Investigue y construya, en LENGUAJE C, la función que realiza cada operación solicitada:
> - (a) Calcula la longitud de una cadena.
> - (b) Determina si una cadena dada es vacía.
> - (c) Concatena dos cadenas.
>
> **Ejercicio 21**
> Construya un programa de testeo para cada función del ejercicio anterior.

## Temas

- Lenguajes formales.
- Especificación de operaciones.
- Interfaces.
- Proceso de traducción.
- `make`
- Strings.
- Alocación.
- Tipos.

## Objetivos

### Parte I — Análisis Comparativo de Strings en Lenguajes de Programación

Realizar un análisis comparativo del tipo de dato String en el lenguaje C versus un lenguaje de programación a elección.
El análisis debe contener, por lo menos, los siguientes ítems:

1. ¿El tipo es parte del lenguaje en algún nivel?
2. ¿El tipo es parte de la biblioteca?
3. ¿Qué alfabeto usa?
4. ¿Cómo se resuelve la alocación de memoria?
5. ¿El tipo tiene mutabilidad o es inmutable?
6. ¿El tipo es un *first class citizen*?
7. ¿Cuál es la mecánica para ese tipo cuando se los pasa como argumentos?
8. ¿Y cuando son retornados por una función?
9. ¿Qué nivel de soporte tiene para ASCII, Unicode, y UTF-8?

Las anteriores preguntas son disparadores para realizar un análisis comparativo profundo.

### Parte II — Biblioteca para el Tipo String

Desarrollar una biblioteca con operaciones de strings.
El desarrollo implica especificar las operaciones e implementar su parte pública y privada.

#### Operaciones de consulta (no crean ni mutan)

1. `IsEmpty`
2. `GetLength`
3. `AreEqual`
4. `AreDecimalDigits`
5. `Contains` — indica si una cadena dada contiene un carácter dado.
6. `ToInteger` — interpreta una cadena como un entero; asume que la cadena es correcta.
7. Una operación a definir libremente.

#### Crédito extra: Operaciones de creación o mutación

1. `Concatenate`
2. `Power` / `Potenciar`
3. Una operación a definir libremente.

#### Orden de desarrollo

1. Especificación en `Strings.md`.
2. Codificación de la interfaz en `Strings.h`.
3. Codificación de las pruebas en `StringsTest.c`.
4. Implementación en `Strings.c`.

> **Para debatir en el equipo:**
> ¿Es correcto que `ToInteger` sea parte de la biblioteca de Strings?
> ¿Debería ser parte de otra biblioteca implementada en, por ejemplo,
> `Conversion.h` y `Conversion.c`, con su propio programa de prueba `ConversionTest.c`?

#### Restricciones

- La especificación matemática debe seguir la estructura formal con conjuntos de dominio, codominio y definición de la operación.
- Las pruebas deben realizarse con `assert`, deben utilizar *literales cadena* y no variables, y no deben enviar nada a `stdout` ni a otro flujo.
- Los prototipos deben utilizar `const` cuando corresponde.
- Las implementaciones de las operaciones de String **no deben utilizar funciones estándar**, por ejemplo las declaradas en `<string.h>`.
- Por lo menos una operación debe implementarse con **recursividad**.
- Codificar el `Makefile` para que el comando `make test` corra los tests.

### Parte III — Programas con argumentos de línea de comando

Esta última parte consiste en desarrollar una serie de programas que esperan argumentos en su línea de comandos.
Todos los programas envían su salida a `stdout`.

- `enlineas` — muestra cada argumento en una línea propia.
- `longitudes` — longitud de cada argumento.
- `mayorlongitud` — argumento con mayor longitud.
- `todosiguales` — imprime `1` si todos los argumentos son iguales, `0` si no.
- `suma` — suma de todos los argumentos que son enteros en base 10. Variación: signo opcional y otras bases.

#### Restricciones

- Se deben usar el o los módulos desarrollados en la parte anterior.
- No se deben usar funciones estándar de cadenas o conversión.
- Para iterar, se debe usar `for`, no `while`, y no debe usarse variables índice.
- Codificar el `Makefile` de manera que el comando `make` genere todos los ejecutables.

## Tareas

### Parte I
- Escribir `AnálisisComparativo.md` con la comparación de strings en C versus otro lenguaje de programación a elección.

### Parte II
1. Para cada operación, escribir en `Strings.md` la especificación matemática con conjuntos de dominio, codominio y definición.
2. Escribir el `Makefile`.
3. Por cada operación:
   - Escribir las pruebas en `StringsTest.c`.
   - Escribir los prototipos en `String.h`.
   - Escribir comentarios con precondiciones y poscondiciones de cada función en `String.h`.
   - Escribir las implementaciones en `Strings.c`.
4. Probar con `make test`.

### Parte III
1. Escribir y probar los siguientes programas: `enlineas`, `longitudes`, `mayorlongitud`, `todosiguales`, `suma`.
2. Actualizar el `Makefile`.

## Productos

```
01-Strings
├── readme.md
├── AnálisisComparativo.md
├── String.md
├── Makefile
├── StringTest.c
├── String.h
├── String.c
├── enlineas.c
├── longitudes.c
├── mayorlongitud.c
├── todosiguales.c
└── suma.c
```

## Referencias

- KR1988, B.6 — Diagnósticos: `<assert.h>`
- [Interfaces: Los Contratos entre Proveedores y Consumidores](https://josemariasola.github.io/ssl/papers/Interfaces.pdf)
- KR1988, 5.10 — Argumentos de la línea de comandos.