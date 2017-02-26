/*
** print_header.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Fri Feb 24 15:45:11 2017 thomas
** Last update Fri Feb 24 15:45:23 2017 thomas
*/

#include <stdio.h>
#include "common.h"

static void print_flags(t_elf_file *file) {
    int     i;
    int     c;

    i = 0;
    c = 0;
    while (i < N_FLAGS) {
        if (g_flags[i].k & file->flags) {
            if (c++ > 0)
                printf(", ");
            printf("%s", g_flags[i].v);
        }
        i++;
    }
    printf("\n");
}

static int  cpt_flags(t_elf_file *file) {
    int     i;
    int     result;

    result = 0;
    i = 0;
    while (i < N_FLAGS) {
        if (g_flags[i].k & file->flags)
            result += g_flags[i].k;
        i++;
    }
    return result;
}

void        print_header(t_elf_file *file) {
    char    *file_format;
    char    *architecture;
    int     flags_result;

    file_format = (file->is_32bits)
                  ? "elf32-i386" : "elf64-x86-64";
    architecture = (file->elf_header->e_machine == EM_386) ? "i386" :
                   (file->elf_header->e_machine == EM_X86_64) ?
                   "i386:x86-64" : "UNKNOWN!";
    printf("\n%s:     file format %s\n", file->file_path, file_format);
    flags_result = cpt_flags(file);
    printf("architecture: %s, flags 0x%08x:\n", architecture, flags_result);
    print_flags(file);
    if (file->is_32bits)
        printf("start address 0x%08lx\n\n", file->elf_header->e_entry);
    else
        printf("start address 0x%016lx\n\n", file->elf_header->e_entry);
}
