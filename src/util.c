#include <stdio.h>
#include <string.h>
#include "util.h"

static int print_forward(const char *a) {
    if (!a) {
        return 1;
    }
    char buf[5] = {0};
    unsigned char msk = 0x80;
    unsigned len = 0;
    for (const char *i = a; *i;) {
        if (!(*i & 0x80)) {
            putchar(*(i++));
        } else {
            for (msk = 0x80, len = 0; (*i & msk);
                 ++len, msk >>= 1);
            strncpy(buf, i, len);
            i += len;
            printf("%s", buf);
        }
    }
    putchar(10);
    return 0;
}

static int print_backward(const char *a) {
    if (!a) {
        return 1;
    }
    const char *i = a;
    char buf[5];
    unsigned len = 0;
    for (; *i; ++i);
    for (--i; i >= a; --i) {
        if (!(*i & 0x80)) {
            putchar(*i);
        } else {
            for (len = 1; len <= 4 && !(*i & 0x40); --i, ++len);
            strncpy(buf, i, len);
            printf("%s", buf);
        }
    }
    putchar(10);
    return 0;
}

int check_palindrome(const char *a, _Bool verbose, _Bool *out) {
    if (!a || !out) {
        return 1;
    }
    if (verbose) {
        print_forward(a);
        print_backward(a);
    }
    const char *iter_forward = a;
    const char *iter_backward = a;
    char buf_forward[5] = {0};
    char buf_backward[5] = {0};
    unsigned char msk = 0x80;
    unsigned len = 0;
    for (; *iter_backward && *iter_backward != 10; ++iter_backward);
    --iter_backward;
    for (; *iter_forward && iter_backward >= iter_forward;
         --iter_backward) {
        if (!(*iter_forward & 0x80) ^ !(*iter_backward & 0x80)) {
            *out = 0;
            return 0;
        }
        if (!(*iter_forward & 0x80) && !(*iter_backward & 0x80)) {
            if (*iter_forward == *iter_backward) {
                ++iter_forward;
            } else {
                *out = 0;
                return 0;
            }
        } else {
            for (msk = 0x80, len = 0; (*iter_forward & msk);
                 ++len, msk >>= 1);
            strncpy(buf_forward, iter_forward, len);
            iter_forward += len;
            for (len = 1; len <= 4 && !(*iter_backward & 0x40);
                 --iter_backward, ++len);
            strncpy(buf_backward, iter_backward, len);
            if (strncmp(buf_forward, buf_backward, 4)) {
                *out = 0;
                return 0;
            }
        }
    }
    *out = 1;
    return 0;
}

int check_palindrome_file(FILE *fin, _Bool verbose, FILE *fout) {
    if (!fin) {
        return 1;
    }
    char buf[100];
    _Bool res = 0;
    for (; fgets(buf, 80, fin);) {
        if (check_palindrome(buf, verbose, &res)) {
            return 1;
        }
        fprintf(fout, "%sPalindrome: %s\n", buf, res ? "Yes" : "No");
    }
    return 0;
}
