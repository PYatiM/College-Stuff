#include <stdio.h>
#include <string.h>

int key[3][3];

void hillEncrypt(char text[]) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 3) {
        int vector[3], result[3];
        for (int j = 0; j < 3; j++)
            vector[j] = text[i + j] - 'A';

        for (int j = 0; j < 3; j++) {
            result[j] = 0;
            for (int k = 0; k < 3; k++)
                result[j] += key[j][k] * vector[k];
            result[j] %= 26;
            text[i + j] = result[j] + 'A';
        }
    }
}

int main() {
    char text[100];
    printf("Enter 3x3 key matrix:\n");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d", &key[i][j]);

    printf("Enter text (multiple of 3 letters, uppercase A-Z): ");
    scanf("%s", text);

    hillEncrypt(text);
    printf("Encrypted text: %s\n", text);

    return 0;
}
