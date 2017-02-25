/*
** elf.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Fri Feb 24 15:45:54 2017 thomas
** Last update Fri Feb 24 15:45:56 2017 thomas
*/

#include <string.h>
#include <assert.h>
#include "common.h"

struct s_flags g_flags[N_FLAGS] = {
        {BFD_NO_FLAGS, "BFD_NO_FLAGS"},
        {HAS_RELOC,    "HAS_RELOC"},
        {EXEC_P,       "EXEC_P"},
        {HAS_LINENO,   "HAS_LINENO"},
        {HAS_DEBUG,    "HAS_DEBUG"},
        {HAS_SYSMS,    "HAS_SYMS"},
        {HAS_LOCALS,   "HAS_LOCALS"},
        {DYNAMIC,      "DYNAMIC"},
        {WP_TEXT,      "WP_TEXT"},
        {D_PAGED,      "D_PAGED"}
};

static char        set_flags(t_elf_file *file) {
    int     i;
    char    *section_name;
    Elf64_Shdr *section_hdr;

    file->flags = 0;
    if (file->elf_header->e_type == ET_REL)
        file->flags |= HAS_RELOC;
    else if (file->elf_header->e_type == ET_DYN)
        file->flags |= DYNAMIC;
    else if (file->elf_header->e_type == ET_EXEC)
        file->flags |= EXEC_P;
    else if (file->elf_header->e_type == ET_CORE)
        file->flags |= HAS_DEBUG;
    i = 0;
    while (i < file->elf_header->e_shnum) {
        if (NULL == (section_hdr = get_section_header(file, i)))
            return 0;
        section_name = "";
        if (section_hdr->sh_type == SHT_DYNAMIC)
            file->flags |= D_PAGED;
        if (section_hdr->sh_type == SHT_DYNSYM ||
                section_hdr->sh_type == SHT_SYMTAB ||
                section_hdr->sh_type == SHT_HASH)
            file->flags |= HAS_SYSMS;
        //TODO: fix that shit
        if (!strcmp(section_name, ".line") &&
                section_hdr->sh_type == SHT_PROGBITS)
            file->flags |= HAS_LINENO;
        if (!strcmp(section_name, ".debug") &&
                section_hdr->sh_type == SHT_PROGBITS)
            file->flags |= HAS_DEBUG;
        i++;
    }
    return 1;
}

void init_elf_file(t_elf_file *file) {
    file->elf_header = NULL;
    file->elf_program_header = NULL;
    file->elf_sections = NULL;
    file->mapped_mem = NULL;
}

char                handle_elf_file(t_elf_file *file) {
    t_common_elf    *common_elf;
    Elf64_Ehdr      *elf_64bits;

    if (file->file_infos.st_size < sizeof(t_common_elf))
        MY_ERROR(0, "%s: %s: File format not recognized\n",
                 file->bin_path, file->file_path);
    common_elf = (t_common_elf *) file->mapped_mem;
    if (!(common_elf->e_indent[EI_MAG0] == ELFMAG0 &&
          common_elf->e_indent[EI_MAG1] == ELFMAG1 &&
          common_elf->e_indent[EI_MAG2] == ELFMAG2 &&
          common_elf->e_indent[EI_MAG3] == ELFMAG3 &&
          common_elf->e_indent[EI_CLASS] != ELFCLASSNONE &&
          common_elf->e_indent[EI_DATA] != ELFDATANONE &&
          common_elf->e_indent[EI_VERSION] != EV_NONE))
        MY_ERROR(0, "%s: %s: File format not recognized\n",
                 file->bin_path, file->file_path);
    file->is_32bits = (common_elf->e_indent[EI_CLASS] == ELFCLASS32);
    if (!get_elf_header(file) || !get_program_header(file))
        MY_ERROR(0, "%s: %s: File truncated\n", file->bin_path, file->file_path);
    set_flags(file);
    return 1;
}