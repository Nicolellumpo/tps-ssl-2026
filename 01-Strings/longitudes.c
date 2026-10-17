#include <stdio.h>
#include "String.h"

int main(int argc, char *argv[]) {
    for (char **actual = argv + 1; *actual != NULL; actual = actual + 1)
        printf("%d\n", GetLength(*actual));

    return 0;
}

//EJEMPLO
//./longitudes.exe Curso de SSL 2026
