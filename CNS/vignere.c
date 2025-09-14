#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereEncrypt(char text[], char key[]) {
    int textLen = strlen(text), keyLen = strlen(key), i, j;
    for (i = 0, j = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            int shift = tolower(key[j % keyLen]) - 'a';
            if (isupper(text[i]))
                text[i] = (text[i] - 'A' + shift) % 26 + 'A';
            else
                text[i] = (text[i] - 'a' + shift) % 26 + 'a';
            j++;
        }
    }
}

void vigenereDecrypt(char text[], char key[]) {
    int textLen = strlen(text), keyLen = strlen(key), i, j;
    for (i = 0, j = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            int shift = tolower(key[j % keyLen]) - 'a';
            if (isupper(text[i]))
                text[i] = (text[i] - 'A' - shift + 26) % 26 + 'A';
            else
                text[i] = (text[i] - 'a' - shift + 26) % 26 + 'a';
            j++;
        }
    }
}

int main() {
    char text[256], key[256];
    printf("Enter text: ");
    gets(text);
    printf("Enter key: ");
    gets(key);

    vigenereEncrypt(text, key);
    printf("Encrypted: %s\n", text);

    vigenereDecrypt(text, key);
    printf("Decrypted: %s\n", text);

    return 0;
}
