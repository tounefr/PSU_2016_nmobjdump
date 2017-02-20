
#include <stdio.h>
#include "objdump.h"

void print_flags(t_elf_file *file) {
    int i;
    int c;

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

int cpt_flags(t_elf_file *file) {
    int i;
    int result;

    result = 0;
    i = 0;
    while (i < N_FLAGS) {
        if (g_flags[i].k & file->flags)
            result += g_flags[i].k;
        i++;
    }
    return result;
}

void print_header(t_elf_file *file) {
    char *file_format;
    char *architecture;
    int flags_result;

    file_format = (file->elf_header->e_ident[EI_CLASS] == ELFCLASS32) ? "" : "elf64-x86-64";
    architecture = "UNKNOWN!";
    if (file->elf_header->e_machine == EM_386)
        architecture = "i386";
    if (file->elf_header->e_machine == EM_X86_64)
        architecture = "i386:x86-64";
    //if (file->elf_header->e_machine == EM_NONE)
    printf("\n%s:     file format %s\n", file->file_path, file_format);
    flags_result = cpt_flags(file);
    printf("architecture: %s, flags 0x%08x:\n", architecture, flags_result);
    print_flags(file);
    if (file->elf_header->e_ident[EI_CLASS] == ELFCLASS32)
        printf("start address %#08lx\n\n", file->elf_header->e_entry);
    else
        printf("start address %#018lx\n\n", file->elf_header->e_entry);
}