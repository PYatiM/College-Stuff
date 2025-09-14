#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char** create_table() {
    char **table = malloc(26 * sizeof(char*));
    for (int i = 0; i < 26; i++) {
        table[i] = malloc(26 * sizeof(char));
    }

    char list[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            table[i][j] = list[(i + j) % 26];
        }
    }
    return table;
}

int main() {
    char **tab = create_table();

    char ct[256];
    char key[256];

    printf("Enter the cipher text : ");
    scanf("%s", ct);

    printf("Enter the key : ");
    scanf("%s", key);

    int cts = strlen(ct);
    int keys = strlen(key);

    char fullKey[256];
    for (int i = 0; i < cts; i++) {
        fullKey[i] = toupper(key[i % keys]);
    }
    fullKey[cts] = '\0';

    char dt[256];

    for (int i = 0; i < cts; i++) {
        int rr = fullKey[i] - 'A';          
        char cipherChar = toupper(ct[i]);   

        int col = 0;
        for (int j = 0; j < 26; j++) {
            if (tab[rr][j] == cipherChar) {
                col = j;
                break;
            }
        }
        dt[i] = 'A' + col;
    }
    dt[cts] = '\0';

    printf("Decrypted Text: %s\n", dt);

    for (int i = 0; i < 26; i++) {
        free(tab[i]);
    }
    free(tab);

    return 0;
}
