#include <stdio.h>
#include "String.h"

int main(int argc, char *argv[]) {
    char *mayor = argv[1];

    for (char **actual = argv + 1; *actual != NULL; actual = actual + 1)
        if (GetLength(*actual) > GetLength(mayor))
            mayor = *actual;

    printf("%s\n", mayor);

    return 0;
}

//EJEMPLO
//./mayorlongitud.exe Curso de SSL 2026
