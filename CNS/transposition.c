#include <stdio.h>
#include <string.h>

void transposeEncrypt(char text[], int key[], int keyLen) {
    int textLen = strlen(text), i, j;
    for (i = 0; i < textLen; i += keyLen) {
        for (j = 0; j < keyLen; j++)
            if (i + key[j] < textLen)
                printf("%c", text[i + key[j]]);
    }
    printf("\n");
}

int main() {
    char text[256];
    int key[10], keyLen, i;

    printf("Enter text: ");
    gets(text);
    printf("Enter key length: ");
    scanf("%d", &keyLen);

    printf("Enter key sequence (0-based indices): ");
    for (i = 0; i < keyLen; i++) scanf("%d", &key[i]);

    printf("Encrypted: ");
    transposeEncrypt(text, key, keyLen);

    return 0;
}
