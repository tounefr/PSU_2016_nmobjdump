/*
** util.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Fri Feb 24 15:47:26 2017 thomas
** Last update Fri Feb 24 15:47:26 2017 thomas
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include "common.h"

char is_printable(char cur_char) {
    return (cur_char >= 32 && cur_char <= 126);
}

long	my_pow(long nb, int power)
{
    if (power == 0)
        return 1;
    if (power != 1)
        nb = nb * my_pow(nb, (power - 1));
    else
        return (nb);
}

char        *str_concat(char *str1, char *str2) {
    int     len1;
    int     len2;
    int     i;
    char    *dest;

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
    int last_nbr_save;
    int nbr_rangs;

    last_nbr = section_hdr->sh_addr + section_hdr->sh_size;
    nbr_rangs = 0;
    last_nbr_save = last_nbr;

    nbr_rangs = 10;
    while (last_nbr / my_pow(16, nbr_rangs) == 0)
        nbr_rangs--;
    nbr_rangs++;
    if (nbr_rangs < 4)
        nbr_rangs = 4;
//    printf("nbr_rangs = %d last_nbr=%x ", nbr_rangs, last_nbr_save);
    return str_concat(str_concat(" %0", my_int_to_str(nbr_rangs)), "x ");
}
