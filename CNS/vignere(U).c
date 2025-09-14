#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereCipher(char text[], char key[], int encrypt) {
    int textLen = strlen(text), keyLen = strlen(key);
    int i, j = 0;
    for (i = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            int shift = toupper(key[j % keyLen]) - 'A';
            if (!encrypt) shift = 26 - shift;
            text[i] = (toupper(text[i]) - 'A' + shift) % 26 + 'A';
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

    vigenereCipher(text, key, 1);
    printf("Encrypted: %s\n", text);

    vigenereCipher(text, key, 0);
    printf("Decrypted: %s\n", text);

    return 0;
}
