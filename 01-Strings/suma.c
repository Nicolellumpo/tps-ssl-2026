#include <stdio.h>
#include "String.h"

int main(int argc, char *argv[]) {
    int suma = 0;

    for (char **actual = argv + 1; *actual != NULL; actual = actual + 1) {
        char *arg = *actual;

        char *sinSigno = arg;
        if (*sinSigno == '+' || *sinSigno == '-')
            sinSigno = sinSigno + 1;

        if (AreDecimalDigits(sinSigno) && !IsEmpty(sinSigno))
            suma = suma + ToInteger(arg);
    }

    printf("%d\n", suma);

    return 0;
}

//EJEMPLO
//./suma.exe 8 8
