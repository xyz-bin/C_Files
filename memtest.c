#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t n = 10;
    int *arr = calloc(n, sizeof(int));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; i++) {
        arr[i] = i + 1;
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return EXIT_SUCCESS;
}
