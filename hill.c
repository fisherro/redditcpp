//https://reddit.com/r/C_Programming/comments/vtl1wd/help/
#include <ctype.h>
#include <string.h>
#include <stdio.h>

void hill_string(const char *s)
{
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (; *s != '\0'; ++s) {
        char c = toupper(*s);
        char *p = strchr(alphabet, c);
        if (p) {
            printf("%d ", p - alphabet);
        }
    }
    puts("");
}

int main(const int argc, const char **argv)
{
    for (int i = 1; i < argc; ++i) {
        hill_string(argv[i]);
    }
}
