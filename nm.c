/*
** nm.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Fri Feb 24 15:46:44 2017 thomas
** Last update Fri Feb 24 15:46:44 2017 thomas
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <assert.h>
#include "common.h"

char check_print_symbol(Elf64_Sym *sym) {
    if (sym->st_info == STT_FILE)
        return 0;
    return 1;
}

char *lookup_string_symbol(t_elf_file *file,
                           Elf64_Shdr *section_hdr,
                           Elf64_Sym *sym) {
    Elf64_Shdr *str_hdr;

    if (NULL == (str_hdr = get_section_header(file, section_hdr->sh_link)))
        return NULL;
    return file->mapped_mem + str_hdr->sh_offset + sym->st_name;
}

static void print_symbols(t_elf_file *file,
                   t_sorted_symbols *sorted_symbols,
                   Elf64_Shdr *section_hdr) {
    char *name;
    int sym_type;
    Elf64_Off offset;

    while (sorted_symbols) {
        sym_type = ELF32_ST_TYPE(sorted_symbols->symbol->st_info);
        if (check_print_symbol(sorted_symbols->symbol)) {
            if (sorted_symbols->symbol->st_name != 0) {
                offset = file->elf_sections[section_hdr->sh_link].sh_offset;
                name = (char *) (file->mapped_mem +
                        offset +
                        sorted_symbols->symbol->st_name);
                if (sorted_symbols->symbol->st_value == 0)
                    printf("%17c", ' ');
                else
                    printf("%016lx ", sorted_symbols->symbol->st_value);
                printf("%s\n", name);
            }
        }
        sorted_symbols = sorted_symbols->next;
    }
}

char            print_sections_symbols(t_elf_file *file) {
    int         i;
    int         nbr_symbols;
    Elf64_Sym        *sym_tabs;
    void        *sym_section;
    Elf64_Shdr  *section_hdr;
    t_sorted_symbols *sorted_symbols;

    i = 1;
    nbr_symbols = 0;
    while (i < file->elf_header->e_shnum) {
        if (NULL == (section_hdr = get_section_header(file, i)))
            return 0;
        if (section_hdr->sh_type == SHT_SYMTAB ||
            section_hdr->sh_type == SHT_HASH) {
            nbr_symbols++;
            if (NULL == (sym_tabs = get_symbols(file, section_hdr, &nbr_symbols)))
                return 0;
            sorted_symbols = sort_symbols(file, section_hdr,
                                          sym_tabs, nbr_symbols);
            print_symbols(file, sorted_symbols, section_hdr);
            // print_symbols(file, section_hdr, sym_tabs, nbr_symbols);
        }
        i++;
    }
    if (nbr_symbols == 0)
        MY_ERROR(0, "%s: %s: no symbols\n", file->bin_path, file->file_path);
    return 1;
}

char            nm(char *bin_path, char *file_path) {
    t_elf_file  file;

    init_elf_file(&file);
    file.file_path = file_path;
    file.bin_path = bin_path;
    if (-1 == (file.fd = open(file_path, O_RDONLY)) ||
        -1 == fstat(file.fd, &file.file_infos))
        MY_ERROR(0, "%s: '%s': No such file\n", bin_path, file_path);
    if (!S_ISREG(file.file_infos.st_mode))
        MY_ERROR(0, "%s: Warning: '%s' is not an ordinary file\n",
                 bin_path, file_path);
    file.mapped_mem = mmap(NULL, file.file_infos.st_size,
                           PROT_READ, MAP_SHARED, file.fd, 0);
    if (file.mapped_mem == MAP_FAILED)
        STRERRNO(0);
    file.end = ((char*)file.mapped_mem + file.file_infos.st_size - 1);
    if (handle_static_library(&file)) {}
    else if (handle_elf_file(&file)) {
        print_sections_symbols(&file);
    } else
        return 0;
    close(file.fd);
    if (-1 == munmap(file.mapped_mem, file.file_infos.st_size))
        STRERRNO(0);
    return 1;
}

int         main(int argc, char **argv) {
    int i;
    int returnv;

    i = 1;
    if (argc == 1)
        return !nm(argv[0], "a.out");
    returnv = 0;
    while (i < argc) {
        if (!nm(argv[0], argv[i++]))
            returnv = 1;
    }
    return returnv;
}
