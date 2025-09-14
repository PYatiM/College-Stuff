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

void transposeDecrypt(char text[], int key[], int keyLen) {
    int textLen = strlen(text);
    char plain[256];
    int i, j, pos = 0;

    for (i = 0; i < textLen; i++) plain[i] = '_';

    for (i = 0; i < textLen; i += keyLen) {
        for (j = 0; j < keyLen; j++) {
            if (i + key[j] < textLen) {
                plain[i + key[j]] = text[pos++];
            }
        }
    }
    plain[textLen] = '\0';
    printf("%s\n", plain);
}

int main() {
    char text[256];
    int key[10], keyLen, i, choice;

    printf("Enter text: ");
    gets(text);   // keep original (unsafe but unchanged)

    printf("Enter key length: ");
    scanf("%d", &keyLen);

    printf("Enter key sequence (0-based indices): ");
    for (i = 0; i < keyLen; i++) scanf("%d", &key[i]);

    printf("Choose option:\n1. Encrypt\n2. Decrypt\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Encrypted: ");
        transposeEncrypt(text, key, keyLen);
    } else if (choice == 2) {
        printf("Decrypted: ");
        transposeDecrypt(text, key, keyLen);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
