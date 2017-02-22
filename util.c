
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "my.h"

char is_printable(char cur_char) {
    return (cur_char >= 32 && cur_char <= 126);
}

char error(char *str, int returnv) {
    fprintf(stderr, "%s\n", str);
    return returnv;
}

char malloc_error() {
    error("malloc error", 0);
    exit(1);
}

int	my_pow(int nb, int power)
{
    if (power == 0)
        return 1;
    if (power != 1)
        nb = nb * my_pow(nb, (power - 1));
    else
        return (nb);
}

char *str_concat(char *str1, char *str2) {
    int len1;
    int len2;
    int i;
    char *dest;

    len1 = strlen(str1);
    len2 = strlen(str2);
    if (NULL == (dest = malloc(len1 + len2 + 1)))
        return NULL;
    dest[len1 + len2 + 1] = 0;
    i = 0;
    while (i < len1)
        dest[i] = str1[i++];
    i = 0;
    while (i < len2)
        dest[i + len1] = str2[i++];
    dest[len1 + len2 + 1] = 0;
    return dest;
}

char    *printf_format_offset(Elf64_Shdr *section_hdr) {
    int last_nbr;
    int nbr_rangs;

    last_nbr = section_hdr->sh_addr + section_hdr->sh_size;
    nbr_rangs = 0;
    while (last_nbr > 0) {
        last_nbr /= my_pow(16, nbr_rangs++);
    }
    nbr_rangs++;

    return str_concat(str_concat(" %0", my_int_to_str(nbr_rangs)), "x");
}