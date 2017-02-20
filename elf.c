
#include <string.h>
#include "objdump.h"

void set_flags(t_elf_file *file) {
    int i;
    char *section_name;

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
        section_name = (char*)(file->section_strings + file->elf_sections[i].sh_name);
        if (file->elf_sections[i].sh_type == SHT_DYNAMIC)
            file->flags |= D_PAGED;
        if (file->elf_sections[i].sh_type == SHT_DYNSYM ||
                file->elf_sections[i].sh_type == SHT_SYMTAB ||
                file->elf_sections[i].sh_type == SHT_HASH)
            file->flags |= HAS_SYSMS;
        if (!strcmp(section_name, ".line") && file->elf_sections[i].sh_type == SHT_PROGBITS)
            file->flags |= HAS_LINENO;
        if (!strcmp(section_name, ".debug") && file->elf_sections[i].sh_type == SHT_PROGBITS)
            file->flags |= HAS_DEBUG;
        i++;
    }
}

char pre_check_elf_header(t_elf_file *file) {
    t_common_elf *common_elf;
    Elf64_Ehdr *elf_64bits;

    if (file->file_infos.st_size < sizeof(t_common_elf))
        return 0;
    common_elf = (t_common_elf *) file->mapped_mem;
    if (!(common_elf->e_indent[EI_MAG0] == ELFMAG0 &&
          common_elf->e_indent[EI_MAG1] == ELFMAG1 &&
          common_elf->e_indent[EI_MAG2] == ELFMAG2 &&
          common_elf->e_indent[EI_MAG3] == ELFMAG3))
        return 0;
    file->is_32bits = 0;
    if (common_elf->e_indent[EI_CLASS] == ELFCLASS32)
        file->is_32bits = 1;
    fill_elf_header(file);
    fill_elf_program_header(file);
    fill_elf_sections(file);
    set_flags(file);
    return 1;
}