#include <stdio.h>
#include <ctype.h>

void encrypt(int key, char* tt) {
    char ch;
    for (int i = 0; tt[i] != '\0'; ++i) {
        ch = tt[i];
        if (isalnum(ch)) {
            if (islower(ch)) {
                ch = (ch - 'a' + key) % 26 + 'a';
            } else if (isupper(ch)) {
                ch = (ch - 'A' + key) % 26 + 'A';
            } else if (isdigit(ch)) {
                ch = (ch - '0' + key) % 10 + '0';
            }
            tt[i] = ch;
        } 
        else {
            if(ch>=32 && ch<=47){
            	ch = (ch - ' ' + key)%16 + ' ';
            }
            else if(ch>=58 && ch<=64){
            	ch = (ch - ':' + key) % 7 + ':';
            }
            else if(ch>=91 && ch<=96){
            	ch = (ch - '[' + key) % 6 + '[';
            }
            else if(ch>=32 && ch<=47){
            	ch = (ch - '{' + key) % 4 + '{';
	    }
	    tt[i] = ch;
	}
     }
}

int main() {
    char text[500];
    int key;

    printf("Enter a message to encrypt (no spaces): ");
    scanf("%s", text);

    printf("Enter the key: ");
    scanf("%d", &key);

    encrypt(key, text);
    printf("Encrypted message: %s\n", text);

    return 0;
}
