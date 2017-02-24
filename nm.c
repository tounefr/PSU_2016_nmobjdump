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

/*
char    print_symbols(t_elf_file *file, ) {

}
 */

char    cross_sym_section(t_elf_file *file,
                          Elf64_Shdr *section_hdr,
                          void *sym_tabs,
                          int nbr_symtabs) {
    Elf64_Sym *sym_tabs64;
    int i;
    char *name;
    int sym_type;

    sym_tabs64 = sym_tabs;
    if (file->is_32bits) {
        if (!fill_symtabs(&sym_tabs64, sym_tabs, nbr_symtabs))
            return 0;
    }
    i = 0;
    while (i < nbr_symtabs) {
        sym_type = ELF32_ST_TYPE(sym_tabs64[i].st_info);
        if (sym_tabs64[i].st_name != 0) {
            name = (char*)(file->mapped_mem +
                    file->elf_sections[section_hdr->sh_link].sh_offset +
                    sym_tabs64[i].st_name);
            if (sym_tabs64[i].st_value == 0)
                printf("     ");
            else
                printf("%016lx ", sym_tabs64[i].st_value);
            printf("%s \n", name);
        }
        i++;
    }
}

char            print_sections_symbols(t_elf_file *file) {
    int         i;
    int         nbr_symtabs;
    void        *sym_tabs;
    void        *sym_section;

    i = 0;
    nbr_symtabs = 0;
    while (i < file->elf_header->e_shnum) {
        if (file->elf_sections[i].sh_type == SHT_SYMTAB ||
            file->elf_sections[i].sh_type == SHT_HASH)
        {
            nbr_symtabs = file->elf_sections[i].sh_size /
                    file->elf_sections[i].sh_entsize;
            sym_tabs = file->mapped_mem + file->elf_sections[i].sh_offset;
            cross_sym_section(file, &file->elf_sections[i], sym_tabs, nbr_symtabs);
        }
        i++;
    }
}

char            nm(char *bin_path, char *file_path) {
    t_elf_file  file;
    void        *data;

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
    if (handle_static_library(&file))
        return 0;
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
