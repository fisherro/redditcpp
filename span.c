#include <stdio.h>
#include <string.h>

struct span {
    char *p;
    size_t s;
};

#define MKSPAN(array) (struct span){ p: array, s: sizeof(array) }

void copy(struct span *dst, struct span src)
{
    if (!dst || !dst->p || 0 == dst->s || !src.p || 0 == src.s) return;
    size_t s = (dst->s < src.s)? dst->s: src.s;
    memcpy(dst->p, src.p, s);
    dst->p += s;
    dst->s -= s;
}

int main()
{
    char buffer[10];
    char a[] = {'H','e','l','l','o'};
    char b[] = {',',' '};
    char c[] = {'W','o','r','l','d'};
    char d[] = {'!'};

    struct span rest = MKSPAN(buffer);
    copy(&rest, MKSPAN(a));
    copy(&rest, MKSPAN(b));
    copy(&rest, MKSPAN(c));
    copy(&rest, MKSPAN(d));

    fwrite(buffer, 1, rest.p - buffer, stdout);
    puts("");
}
