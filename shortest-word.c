// https://reddit.com/r/C_Programming/comments/zu9pym/really_confused_about_strings_newbie/

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//All of these break if the string has zero words.
//None of these these to see if the string is NULL.

int take0(const char *s)
{
    int min = INT_MAX;
    int count = 0;
    while (true) {
        if (('\0' == *s) || isspace(*s)) {
            if ((count > 0) && (count < min)) min = count;
            count = 0;
        } else {
            ++count;
        }
        if ('\0' == *s) return min;
        ++s;
    }
}

int take1(const char *s)
{
    int count = INT_MAX;
    while (true) {
        const char *space = strchr(s, ' ');
        int c = space? space - s: strlen(s);
        if ((c > 0) && (c < count)) count = c;
        if (!space) return count;
        s = space + 1;
    }
}

int take2(const char *s)
{
    int count = INT_MAX;
    while (true) {
        const char *space = strpbrk(s, " \t\n\r");
        int c = space? space - s: strlen(s);
        if ((c > 0) && (c < count)) count = c;
        if (!space) return count;
        s = space + 1;
    }
}

int take3(const char *s)
{
    int count = INT_MAX;
    while (true) {
        size_t len = strcspn(s, " \t\n\r");
        if ((len > 0) && (len < count)) count = len;
        s += len;
        if ('\0' == *s) return count;
        ++s;
    }
}

int take4(const char *s)
{
    //Sscanf doesn't work because it doesn't tell us how many characters have been consumed, so we don't know where to start the next scan.
    //So this uses fmemopen and fscanf.
    size_t original_len = strlen(s);
    //Create a FILE* that reads from our input string.
    //Fmemopen requires us to cast away const, but we're only going to read.
    FILE *file = fmemopen((char *) s, original_len, "r");
    //What's the max number of decimal digits in an int?
    //There are easier ways than this.
    int max_digits = snprintf(NULL, 0, "%d", INT_MAX);
    //Our format specifier will also have a '%', an 's', and a '\0'.
    char format[max_digits + 3];
    //Build the format specifier:
    snprintf(format, sizeof(format), "%%%ds", original_len);
    int count = INT_MAX;
    while (true) {
        //No word in s can be longer than s.
        char word[original_len + 1];
        //Read a word:
        int n = fscanf(file, format, word);
        //If we didn't read anything, we're done.
        if ((0 == n) || (EOF == n)) break;
        //Otherwise, see if this is the shortest word we've seen.
        size_t len = strlen(word);
        if ((len > 0) && (len < count)) count = len;
    }
    fclose(file);
    return count;
}

int take5(const char *s)
{
    //Strtok writes to the string, so dup it first:
    char *input = strdup(s);
    char *token = strtok(input, " ");
    int min = INT_MAX;
    while (token) {
        size_t len = strlen(token);
        if ((len > 0) && (len < min)) min = len;
        token = strtok(NULL, " ");
    }
    free(input);
    return min;
}

int main()
{
    char s[] = "What is the shortest string";
    printf("take0: %d\n", take0(s));
    printf("take1: %d\n", take1(s));
    printf("take2: %d\n", take2(s));
    printf("take3: %d\n", take3(s));
    printf("take4: %d\n", take4(s));
    printf("take5: %d\n", take5(s));
}
