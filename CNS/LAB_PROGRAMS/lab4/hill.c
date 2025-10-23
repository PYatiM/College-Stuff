#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Required for exit()

// Global key matrices
int key[3][3], invKey[3][3];

// Helper for correct modulo 26 arithmetic
int mod(int a) { return (a % 26 + 26) % 26; }

// Finds modular multiplicative inverse of a under modulo 26
int modInverse(int a) {
    for (int x = 1; x < 26; x++)
        if (mod(a * x) == 1) return x;
    return -1;
}

// Calculates determinant of a 3x3 matrix
int determinant(int m[3][3]) {
    int det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
              m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
              m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    return mod(det);
}

// Calculates the inverse of the global key matrix
void getInverse() {
    int invDet = modInverse(determinant(key));
    if (invDet == -1) {
        printf("Key matrix is not invertible mod 26!\n");
        exit(1);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int cofactor = key[(j + 1) % 3][(i + 1) % 3] * key[(j + 2) % 3][(i + 2) % 3] -
                           key[(j + 1) % 3][(i + 2) % 3] * key[(j + 2) % 3][(i + 1) % 3];
            invKey[i][j] = mod(((i + j) % 2 == 0 ? 1 : -1) * cofactor * invDet);
        }
    }
}

// Encrypts or decrypts text using a given matrix
void transform(char text[], int m[3][3]) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 3) {
        int res[3] = {0};
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++)
                res[j] += m[j][k] * (text[i + k] - 'A');
        }
        for (int j = 0; j < 3; j++)
            text[i + j] = mod(res[j]) + 'A';
    }
}

int main() {
    char text[100];
    printf("Enter 3x3 key matrix:\n");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d", &key[i][j]);

    getInverse();

    printf("Enter text (multiple of 3 letters, uppercase A-Z): ");
    scanf("%s", text);

    transform(text, key);
    printf("Encrypted text: %s\n", text);

    transform(text, invKey);
    printf("Decrypted text: %s\n", text);

    return 0;
}


// Enter 3x3 key matrix:
// 6
// 24
// 1
// 13
// 16
// 10
// 20
// 17
// 15
// Enter text (multiple of 3 letters, uppercase A-Z): ACT
// Encrypted text: POH
// Decrypted text: ACT
