#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vernamCipher(char text[], char key[]) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i]) && isalpha(key[i])){
            text[i] = ((toupper(text[i]) - 'A') ^ (toupper(key[i]) - 'A')) % 26 + 'A';
        }
    }
}

int main() {
    char text[256], key[256];
    printf("Enter text: ");
    gets(text);
    printf("Enter key (same length as text): ");
    gets(key);

    vernamCipher(text, key);
    printf("Encrypted: %s\n", text);

    vernamCipher(text, key);
    printf("Decrypted : %s\n", text);
    return 0;
}



// OUTPUT
// Enter text: CODE
// Enter key (same length as text): KEYK
// Encrypted: MKBO
// Decrypted: CODE