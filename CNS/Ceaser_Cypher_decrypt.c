#include <stdio.h>
#include <ctype.h>

void decrypt(int key, char* tt) {
    char ch;
    for (int i = 0; tt[i] != '\0'; ++i) {
        ch = tt[i];
        if (isalpha(ch)) {
            key %= 26;
            if (islower(ch)) {
                ch = ((ch - 'a' - key + 26) % 26) + 'a';
            } else if (isupper(ch)) {
                ch = ((ch - 'A' - key + 26) % 26) + 'A';
            }
            tt[i] = ch;
        } 
        else if (isdigit(ch)) {
        	key %= 10;
                ch = ((ch - '0' - key + 10) % 10) + '0';
            	tt[i] = ch;
        } 
        else {
            if(ch>=32 && ch<=47){
            	key %= 16;
            	ch = ((ch - ' ' - key +16) % 16) + ' ';
            }
            else if(ch>=58 && ch<=64){
                key %= 7;
            	ch = ((ch - ':' - key + 7) % 7) + ':';
            }
            else if(ch>=91 && ch<=96){
            	key %= 6;
            	ch = ((ch - '[' - key + 6) % 6) + '[';
            }
            else if(ch>=32 && ch<=47){
            	key %= 4;
            	ch = ((ch - '{' - key + 4) % 4) + '{';
	    }
	    tt[i] = ch;
	}
     }
}

int main() {
    char text[500];
    int key;

    printf("Enter a message to decrypt (no spaces): ");
    scanf("%s", text);

    printf("Enter the key: ");
    scanf("%d", &key);

    decrypt(key, text);
    printf("Decrypted message: %s\n", text);

    return 0;
}
