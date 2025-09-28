#include <stdio.h>

// 1D array creation, traversing and printing
void createAndPrint1DArray(int *arr, int size) {
    // Creation (example values)
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    // Traversing and printing
    printf("1D Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 2D array creation, traversing and printing
void createAndPrint2DArray(int rows, int cols, int arr[rows][cols]) {
    // Creation (example values)
    int val = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = val++;
        }
    }
    // Traversing and printing
    printf("2D Array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int size = 6;
    int arr1D[size];
    createAndPrint1DArray(arr1D, size);

    int rows = 2, cols = 3;
    int arr2D[rows][cols];
    createAndPrint2DArray(rows, cols, arr2D);

    return 0;
}


// OUTPUT
// 1D Array:
// 1 2 3 4 5 6
// 2D Array:
// 1 2 3
// 4 5 6
// (Note: Actual output will depend on the example values used in creation)