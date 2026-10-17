#include "String.h"

bool IsEmpty(const char *cadena) {
    return *cadena == '\0';
}

int GetLength(const char *cadena) {
    int length = 0;
    for (const char *p = cadena ; *p != '\0'; p++) {
        length++;
    }
    return length;
}

bool AreEqual(const char *cadena, const char *otraCadena) {
    if (*cadena == '\0' && *otraCadena == '\0')
        return true;

    if (*cadena != *otraCadena)
        return false;

    return AreEqual(cadena + 1, otraCadena + 1);
}

bool AreDecimalDigits(const char *cadena) {
    if (*cadena == '\0')
        return false;

    if (*cadena < '0' || *cadena > '9')
        return false;
    
    if(*(cadena + 1) == '\0')
        return true;

    return AreDecimalDigits(cadena + 1);
}

bool Contains(const char *cadena, char caracterBuscado) {
    if (*cadena == '\0')
        return false;

    if (*cadena == caracterBuscado)
        return true;

    return Contains(cadena + 1, caracterBuscado);
}

int ToInteger(const char *cadenaNumerica) {
    int signo = 1;
    int valorAcumulado = 0;

    // Manejo de signo
    if (*cadenaNumerica == '-') {
        signo = -1;
        cadenaNumerica++;
    } else if (*cadenaNumerica == '+') {
        cadenaNumerica++;
    }

    // Construcción del numero
    while (*cadenaNumerica != '\0') {
        valorAcumulado = valorAcumulado * 10 + (*cadenaNumerica - '0');
        cadenaNumerica++;
    }

    return signo * valorAcumulado;
}

bool IsLowerCase(const char *cadena) {
    if (*cadena == '\0')
        return true;

    if (*cadena >= 'A' && *cadena <= 'Z')
        return false;

    return IsLowerCase(cadena + 1);
}

// Credito extra
void Concatenate(char *destino, const char *origen) {
    destino += GetLength(destino);

    while (*origen != '\0') {
        *destino = *origen;
        destino++;
        origen++;
    }

    *destino = '\0';
}

void Power(char *destino, const char *cadena, int exponente){
    *destino = '\0';
    
    for (int repeticiones = exponente; repeticiones > 0; repeticiones--)
        Concatenate(destino, cadena);
}

void Reverse(char *cadena) {
    int longitud = GetLength(cadena);
    
    if (longitud <= 1)
        return;

    char temporal;

    for (char *inicio = cadena, *fin = cadena + (longitud - 1); inicio < fin; inicio++, fin--) {
        temporal = *inicio;
        *inicio = *fin;
        *fin = temporal;
    }
}
