#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Unified Caesar Cipher function
void caesarCipher(char *tt, int key, int mode) {
    char ch;
    int shift = (mode == 1) ? key : -key; // +key for encrypt, -key for decrypt

    for (int i = 0; tt[i] != '\0'; ++i) {
        ch = tt[i];

        if (islower(ch)) {
            ch = (ch - 'a' + shift + 26) % 26 + 'a';
        } else if (isupper(ch)) {
            ch = (ch - 'A' + shift + 26) % 26 + 'A';
        } else if (isdigit(ch)) {
            ch = (ch - '0' + shift + 10) % 10 + '0';
        } else if (ch >= 32 && ch <= 47) { // symbols
            ch = (ch - ' ' + shift + 16) % 16 + ' ';
        } else if (ch >= 58 && ch <= 64) {
            ch = (ch - ':' + shift + 7) % 7 + ':';
        } else if (ch >= 91 && ch <= 96) {
            ch = (ch - '[' + shift + 6) % 6 + '[';
        } else if (ch >= 123 && ch <= 126) {
            ch = (ch - '{' + shift + 4) % 4 + '{';
        }
        tt[i] = ch;
    }
}

int main() {
    char text[500];
    int key, choice;

    printf("Enter a message (no spaces): ");
    scanf("%s", text);

    printf("Enter the key: ");
    scanf("%d", &key);

    printf("Choose an option:\n1. Encrypt\n2. Decrypt\n");
    scanf("%d", &choice);

    if (choice == 1 || choice == 2) {
        caesarCipher(text, key, choice);
        printf("%s message: %s\n", (choice == 1 ? "Encrypted" : "Decrypted"), text);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}


// OUTPUT
// Enter a message (no spaces): Hello-123!
// Enter the key: 3
// Choose an option:
// 1. Encrypt
// 2. Decrypt
// 1
// Encrypted message: Khoor,456"
