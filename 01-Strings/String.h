#define STRING_H

// Precondición: cadena es una cadena válida terminada en '\0'
// Postcondición: retorna 1 si está vacía, 0 si no
bool IsEmpty(const char *cadena);

// Precondición: cadena es una cadena válida terminada en '\0'
// Postcondición: retorna la cantidad de caracteres sin contar '\0'
int GetLength(const char *cadena);

// Precondición: ambas cadenas son válidas y terminan en '\0'
// Postcondición: retorna 1 si son iguales, 0 si no
bool AreEqual(const char *cadena, const char *otraCadena);

// Precondición: palabra es una cadena válida terminada en '\0'
// Postcondición: retorna 1 si todos los caracteres son dígitos decimales ('0' a '9'), 0 si no
bool AreDecimalDigits(const char *cadena);

// Precondición: cadena es una cadena válida terminada en '\0'
// Postcondición: retorna 1 si caracterBuscado está en cadena, 0 si no
bool Contains(const char *cadena, char caracterBuscado);

// Precondición: textoNumerico representa un entero válido
// Postcondición: retorna el valor entero correspondiente
int ToInteger(const char *cadenaNumerica);

// Precondición: cadena es una cadena válida terminada en '\0'
// Postcondición: retorna 1 si todos los caracteres son minúsculas, 0 si no
bool IsLowerCase(const char *cadena);

// Precondición: destino debe apuntar a un espacio de memoria válido y tener capacidad suficiente para albergar su propio contenido más el de la fuente y el carácter nulo. Ambos strings deben estar finalizados con '\0'
// Poscondición: Modifica destino anexando el contenido de la fuente al final. destino queda finalizado con el carácter nulo '\0'
void Concatenate(char *destino, const char *origen);

// Precondición: cadena es una cadena válida terminada en '\0', exponente >= 0, y destino tiene espacio suficiente
// Postcondición: destino contiene cadena repetida exponente veces (cadena vacia si exponente = 0)
void Power(char *destino, const char *cadena, int exponente);

// Precondición: una cadena válida terminada en '\0'
// Poscondición: retorna cadena en orden invertido de los caracteres modificando el espacio de memoria original
void Reverse(char *cadena);
