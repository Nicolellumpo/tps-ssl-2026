#include <stdio.h>
#include <limits.h>

int main(void) {
    int total = 0;

    for (int c; (c = getchar()) != EOF; ) {
        if (total > INT_MAX - c) {
            fprintf(stderr, "Error: Overflow\n");
            return 1;
        }
        total += c;
        printf("%d\n", total);
    }

    return 0;
}
