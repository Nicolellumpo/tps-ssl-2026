#include <stdio.h>
#include "String.h"

int main(int argc, char *argv[]) {
    int iguales = 1;

    for (char **actual = argv + 1; *actual != NULL && iguales; actual = actual + 1)
        if (!AreEqual(argv[1], *actual))
            iguales = 0;

    printf("%d\n", iguales);

    return 0;
}

//EJEMPLO
//./todosIguales.exe curso curso curso
