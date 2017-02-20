
#include <stdio.h>
#include "objdump.h"

char is_printable(char cur_char) {
    return (cur_char >= 32 && cur_char <= 126);
}

char error(char *str, int returnv) {
    fprintf(stderr, "%s\n", str);
    return returnv;
}
