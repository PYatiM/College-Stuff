#include <stdio.h>
#include <ctype.h>

void caesar_file(const char *in, const char *out, int key, int encrypt) {
    FILE *fin = fopen(in, "r"), *fout = fopen(out, "w");
    if (!fin || !fout) { printf("File error.\n"); return; }
    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = (ch - base + (encrypt ? key : 26 - key)) % 26 + base;
        }
        fputc(ch, fout);
    }
    fclose(fin); fclose(fout);
}

int main() {
    char in[256], out[256];
    int key, enc;
    printf("Input file: "); scanf("%255s", in);
    printf("Output file: "); scanf("%255s", out);
    printf("Key (1-25): "); scanf("%d", &key);
    printf("1.Encrypt 2.Decrypt: "); scanf("%d", &enc);
    if (key < 1 || key > 25 || (enc != 1 && enc != 2)) { printf("Invalid.\n"); return 1; }
    caesar_file(in, out, key, enc == 1);
    printf("Done.\n");
    return 0;
}

// OUTPUT
// Input file: input.txt
// Output file: output.txt
// Key (1-25): 3
// 1.Encrypt 2.Decrypt: 1
// Done.
// (Contents of output.txt will be the encrypted text)