//
// Created by thomas on 15/02/17.
//

#ifndef PSU_2016_NMOBJDUMP_OBJDUMP_H
#define PSU_2016_NMOBJDUMP_OBJDUMP_H

#include <elf.h>

typedef struct s_files {
    char *file;
    struct s_files *next;
} t_files;

typedef struct s_args {
    char show_content;
    char show_headers;
    t_files *files;
} t_args;

#ifdef __x86_64__
# define ELF_HEADER Elf64_Ehdr
# else
# define ELF_HEADER Elf32_Ehdr
#endif

void    free_args_struct(struct s_args *args);
int     parse_args(int argc, char **argv, t_args *args);

#endif //PSU_2016_NMOBJDUMP_OBJDUMP_H
