#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main(void) {
    int64_t total = 0;

    for (int64_t n; fread(&n, sizeof(n), 1, stdin) == 1; ) {
        if (total > INT64_MAX - n) {
            fprintf(stderr, "Error: Overflow\n");
            return 1;
        }
        total += n;
        printf("%lld\n", (long long)total);
    }

    return 0;
}
