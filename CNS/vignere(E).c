#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereEncrypt(char text[], char key[]) {
    int textLen = strlen(text), keyLen = strlen(key), i, j;
    for (i = 0, j = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            int shift = toupper(key[j % keyLen]) - 'A';
            text[i] = (toupper(text[i]) - 'A' + shift) % 26 + 'A';
            j++;
        }
    }
}

int main() {
    char text[256], key[] = "VIGENERECIPHER";
    printf("Enter text: ");
    gets(text);

    vigenereEncrypt(text, key);
    printf("Encrypted: %s\n", text);

    return 0;
}
