#include <stdio.h>

int main() {
    int n;

    printf("Enter size of 1D array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nTraversing 1D array:\n");
    for (int i = 0; i < n; i++) {
        printf("Element at index %d = %d\n", i, arr[i]);
    }

    return 0;
}
