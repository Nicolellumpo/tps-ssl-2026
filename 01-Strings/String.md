# Biblioteca de Operaciones sobre Strings

## Introducción

Esta biblioteca define un conjunto de operaciones sobre cadenas de caracteres en lenguaje C.

Una cadena es entendida como una secuencia de caracteres terminada en el carácter nulo `\0`.

La especificación matemática describe el comportamiento abstracto de las operaciones utilizando valores booleanos (`true` y `false`).

---

# Operaciones de consulta

## 1. IsEmpty

### Descripción

Determina si una cadena está vacía.

### Especificación matemática

Dominio:

IsEmpty : Σ* -> Boolean

Definición:

IsEmpty(cadena) = true &nbsp; si cadena = ε  
IsEmpty(cadena) = false &nbsp; si cadena ≠ ε

--- 

## 2. GetLength

### Descripción

Calcula la cantidad de caracteres de una cadena.

### Especificación matemática

Dominio:

GetLength : Σ* -> N

Definición:

GetLength(cadena) = 0 &nbsp; si cadena = ε  
GetLength(cadena) = 1 + GetLength(cola) &nbsp; si cadena = cabeza . cola, cabeza ∈ Σ

---

## 3. AreEqual

### Descripción

Determina si dos cadenas son exactamente iguales.

### Especificación matemática

Dominio:

AreEqual : Σ* x Σ* -> Boolean

Definición:

AreEqual(cadena, otraCadena) = true &nbsp; si cadena = ε, otraCadena = ε  
AreEqual(cadena, otraCadena) = false &nbsp; si cadena = cabeza . cola, otraCadena = otraCabeza . otraCola, cabeza ≠ otraCabeza  
AreEqual(cadena, otraCadena) = AreEqual(cola, otraCola) &nbsp; si cadena = cabeza . cola, otraCadena = cabeza . otraCola

---

## 4. AreDecimalDigits

### Descripción

Determina si todos los caracteres de una cadena son dígitos decimales.

### Especificación matemática

Dominio:

AreDecimalDigits : Σ* -> Boolean

Definición:

AreDecimalDigits(cadena) = false &nbsp; si cadena = ε  
AreDecimalDigits(cadena) = false &nbsp; si cadena = cabeza . cola, cabeza ∉ {0,1,2,3,4,5,6,7,8,9}  
AreDecimalDigits(cadena) = true &nbsp; si cadena = cabeza, cabeza ∈ {0,1,2,3,4,5,6,7,8,9}  
AreDecimalDigits(cadena) = AreDecimalDigits(cola) &nbsp; si cadena = cabeza . cola, cabeza ∈ {0,1,2,3,4,5,6,7,8,9}, cola ≠ ε

---

## 5. Contains

### Descripción

Determina si una cadena contiene un carácter dado.

### Especificación matemática

Dominio:

Contains : Σ* x Σ -> Boolean

Definición:

Contains(cadena, caracterBuscado) = false &nbsp; si cadena = ε  
Contains(cadena, caracterBuscado) = true  &nbsp; si cadena = cabeza . cola, cabeza = caracterBuscado  
Contains(cadena, caracterBuscado) = Contains(cola, caracterBuscado) &nbsp; si cadena = cabeza . cola, cabeza ≠ caracterBuscado

---

## 6. ToInteger

### Descripción

Convierte una cadena numérica en un número entero.

### Especificación matemática

Dominio:

ToInteger : Σ* -> Z

Definición:

ToInteger(cadenaNumerica) = ToInteger(cadena) &nbsp; si cadenaNumerica = "+" . cadena  
ToInteger(cadenaNumerica) = -ToInteger(cadena) &nbsp; si cadenaNumerica = "-" . cadena  
ToInteger(cadenaNumerica) = numero &nbsp;  si cadenaNumerica = numero , numero ∈ {0..9}  

---

## 7. IsLowerCase

### Descripción

Determina si todos los caracteres alfabéticos de una cadena están escritos en minúscula.

### Especificación matemática

Dominio:

IsLowerCase : Σ* -> Boolean

Definición:

IsLowerCase(cadena) = true &nbsp; si cadena = ε  
IsLowerCase(cadena) = false &nbsp; si cadena = cabeza . cola, cabeza ∈ {A..Z}  
IsLowerCase(cadena) = IsLowerCase(cola) &nbsp; si cadena = cabeza . cola, cabeza ∉ {A..Z}

---

# Operaciones de Mutación / Crédito Extra

## 8. Concatenate

### Descripción

Concatena una cadena fuente al final de una cadena destino.

### Especificación matemática

Dominio:

Concatenate : Σ* x Σ* -> Σ*

Definición:

Concatenate(destino, origen) = destino &nbsp; si origen = ε  
Concatenate(destino, origen) = Concatenate(destino . cabeza, cola) &nbsp; si origen = cabeza . cola

---

## 9. Power

### Descripción

Concatena la cadena dada con sigo misma n-1 veces.

### Especificación matemática

Dominio:

Power :  Σ* X N -> Σ*

Definición:

Power(cadena, exponente) = ε &nbsp; si exponente = 0  
Power(cadena, exponente) = cadena . Power(cadena, exponente - 1) &nbsp; si exponente > 0

---

## 10. Reverse

### Descripción

Invierte el orden de los caracteres de una cadena modificando la cadena original.

### Especificación matemática

Dominio:

Reverse : Σ* -> Σ*

Definición:

Reverse(cadena) = cadena &nbsp; si cadena = ε  
Reverse(cadena) = cadena &nbsp; si cadena = cabeza  
Reverse(cadena) = Reverse(cola) . cabeza &nbsp; si cadena = cabeza . cola

---

# Observaciones de Diseño

## Sobre ToInteger

La operación `ToInteger` convierte datos entre dominios distintos (`String` e `Integer`).

Por diseño, podría formar parte de una biblioteca separada de conversiones.

Sin embargo, se incluye dentro de esta biblioteca por simplicidad y cohesión académica del trabajo práctico.
