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

    char pt[256];
    char key[256];

    printf("Enter the plain text : ");
    scanf("%s", pt);  

    printf("Enter the key : ");
    scanf("%s", key);

    int pts = strlen(pt);   
    int keys = strlen(key);

    for (int i = 0; i < pts; i++) {
        key[i] = key[i % keys];
    }
    key[pts] = '\0';

    char ct[256];
    char cr, rr;

    for (int i = 0; i < pts; i++) {
        rr = toupper(key[i]) - 'A';  
        cr = toupper(pt[i]) - 'A';
        ct[i] = tab[rr][cr];         
    }
    ct[pts] = '\0'; 

    printf("Cipher Text: %s\n", ct);

    return 0;
}
