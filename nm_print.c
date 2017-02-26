/*
** nm_print.c for  in /home/thomas/Documents/epitech/test
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Sun Feb 26 15:16:54 2017 thomas
** Last update Sun Feb 26 15:16:54 2017 thomas
*/

#include "common.h"

char check_print_symbol(Elf64_Sym *sym) {
    if (sym->st_info == STT_FILE)
        return 0;
    return 1;
}

char    get_letter(t_elf_file *file,
                Elf64_Shdr *section_hdr,
                Elf64_Sym *sym) {
    int sym_type;

    sym_type = ELF32_ST_TYPE(sym->st_info);
    if (sym->st_shndx == SHN_UNDEF || sym_type == STT_NOTYPE)
        return 'U';
    if (sym->st_shndx == SHN_COMMON)
        return 'C';
    if (sym->st_shndx == SHN_ABS)
        return 'A';
    if (section_hdr->sh_type == SHT_PROGBITS)
        return 'T';
    if (!(section_hdr->sh_flags & SHF_WRITE))
        return 'R';
    return '?';
}

static void     print_symbols(t_elf_file *file,
                              t_sorted_symbols *sorted_symbols,
                              Elf64_Shdr *section_hdr) {
    char        *name;
    Elf64_Off   offset;

    while (sorted_symbols) {
        if (check_print_symbol(sorted_symbols->symbol)) {
            if (sorted_symbols->symbol->st_name != 0) {
                offset = file->elf_sections[section_hdr->sh_link].sh_offset;
                name = (char *) (file->mapped_mem +
                                 offset +
                                 sorted_symbols->symbol->st_name);
                if (sorted_symbols->symbol->st_value == 0)
                    printf((file->is_32bits) ? "%9c" : "%17c", ' ');
                else
                    printf((file->is_32bits) ? "%08lx " : "%016lx ",
                           sorted_symbols->symbol->st_value);
                printf("%c %s\n",
                       get_letter(file, section_hdr, sorted_symbols->symbol),
                       name);
            }
        }
        sorted_symbols = sorted_symbols->next;
    }
}

char                    print_sections_symbols(t_elf_file *file) {
    int                 i;
    int                 nbr_symbols;
    Elf64_Sym           *sym_tabs;
    Elf64_Shdr          *section_hdr;
    t_sorted_symbols    *sorted_symbols;

    i = 1;
    nbr_symbols = 0;
    while (i < file->elf_header->e_shnum) {
        section_hdr = get_section_header(file, i);
        if (section_hdr && (section_hdr->sh_type == SHT_SYMTAB ||
            section_hdr->sh_type == SHT_HASH)) {
            nbr_symbols++;
            sym_tabs = get_symbols(file, section_hdr, &nbr_symbols);
            if (sym_tabs == NULL)
                return 0;
            sorted_symbols = sort_symbols(file, section_hdr,
                                          sym_tabs, nbr_symbols);
            print_symbols(file, sorted_symbols, section_hdr);
        }
        i++;
    }
    if (nbr_symbols == 0)
        MY_ERROR(0, "%s: %s: no symbols\n", file->bin_path, file->file_path);
    return 1;
}
