#include <stdio.h>
#include <stdlib.h>

void convert1Dto2D(int *arr1D, int rows, int cols, int arr2D[rows][cols]) {
    for (int i = 0; i < rows * cols; i++) {
        arr2D[i / cols][i % cols] = arr1D[i];
    }
}

int main() {
    int rows = 2, cols = 3;
    int arr1D[6] = {1, 2, 3, 4, 5, 6};
    int arr2D[2][3];

    convert1Dto2D(arr1D, rows, cols, arr2D);

    printf("2D array from 1D array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr2D[i][j]);
        }
        printf("\n");
    }

    return 0;
}
