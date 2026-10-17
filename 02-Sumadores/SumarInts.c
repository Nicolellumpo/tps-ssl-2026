#include <stdio.h>
#include <limits.h>

int main(void) {
    int total = 0;

    for (int n; fread(&n, sizeof(n), 1, stdin) == 1; ) {
        if (total > INT_MAX - n) {
            fprintf(stderr, "Error: Overflow\n");
            return 1;
        }
        total += n;
        printf("%d\n", total);
    }

    return 0;
}
