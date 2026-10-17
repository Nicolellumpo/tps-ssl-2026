#include <stdio.h>

int main(int argc, char *argv[]) {
    for (char **actual = argv + 1; *actual != NULL; actual = actual + 1)
        printf("%s\n", *actual);

    return 0;
}

//EJEMPLO
//./enlineas.exe Curso de SSL 2026
