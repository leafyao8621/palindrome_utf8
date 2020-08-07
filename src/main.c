#include <stdio.h>
#include "util.h"

int main(int argc, char **argv) {
    FILE *fin = stdin;
    FILE *fout = stdout;
    _Bool verbose = 0;
    if (argc > 1) {
        fin = fopen(argv[1], "r");
    }
    if (argc > 2) {
        fout = fopen(argv[2], "w");
    }
    if (argc > 3) {
        verbose = 1;
    }
    _Bool res = 0;
    // check_palindrome("你好こんにちはhelloollehはちにんこ好你", 1, &res);
    // printf("%d\n", res);
    if (check_palindrome_file(fin, verbose, fout)) {
        puts("Error");
        return 1;
    }
    return 0;
}
