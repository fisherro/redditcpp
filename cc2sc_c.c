//Convert camelCase to snake_case
//https://reddit.com/r/C_Programming/comments/usyufg/_/i9aq5cl/?context=1

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <iso646.h>

int main()
{
    while (true) {
        int c1 = fgetc(stdin);
        if (EOF == c1) {
            break;
        }
        if (not islower(c1)) {
            fputc(c1, stdout);
            continue;
        }
        int c2 = fgetc(stdin);
        if (EOF == c2) {
            fputc(c1, stdout);
            break;
        }
        if (not isupper(c2)) {
            fputc(c1, stdout);
            ungetc(c2, stdin);
            continue;
        }
        fprintf(stdout, "%c_%c", c1, tolower(c2));
    }
}
