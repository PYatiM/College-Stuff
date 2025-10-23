#include <stdio.h>
#include <stdlib.h>

void convert2Dto1D(int rows, int cols, int arr2D[rows][cols], int *arr1D) {
    for (int i = 0; i < rows * cols; i++) {
        arr1D[i] = arr2D[i / cols][i % cols];
    }
}

int main() {
    int rows = 2, cols = 3;
    int arr2D[2][3] = {{7, 8, 9}, {10, 11, 12}};
    int arr1D[6];

    convert2Dto1D(rows, cols, arr2D, arr1D);

    printf("1D array from 2D array:\n");
    for (int i = 0; i < rows * cols; i++) {
        printf("%d ", arr1D[i]);
    }
    printf("\n");

    return 0;
}
