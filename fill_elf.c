
#include <stdlib.h>
#include "common.h"

char            fill_elf_header(t_elf_file *file) {
    Elf32_Ehdr  *elf_32bits;
    int         i;

    if (!file->is_32bits) {
        file->elf_header = (Elf64_Ehdr *) file->mapped_mem;
        return !(file->elf_header >= (file->mapped_mem + file->file_infos.st_size - sizeof(Elf64_Ehdr)));
    }
    elf_32bits = (Elf32_Ehdr *) file->mapped_mem;
    if (NULL == (file->elf_header = malloc(sizeof(Elf64_Ehdr))))
        return 0;
    i = 0;
    if (file->elf_header >= (file->mapped_mem + file->file_infos.st_size - sizeof(Elf32_Ehdr)))
        return 0;
    while (i++ < EI_NIDENT)
        file->elf_header->e_ident[i - 1] = elf_32bits->e_ident[i - 1];
    file->elf_header->e_type = elf_32bits->e_type;
    file->elf_header->e_machine = elf_32bits->e_machine;
    file->elf_header->e_version = elf_32bits->e_version;
    file->elf_header->e_entry = elf_32bits->e_entry;
    file->elf_header->e_phoff = elf_32bits->e_phoff;
    file->elf_header->e_shoff = elf_32bits->e_shoff;
    file->elf_header->e_flags = elf_32bits->e_flags;
    file->elf_header->e_ehsize = elf_32bits->e_ehsize;
    file->elf_header->e_phentsize = elf_32bits->e_phentsize;
    file->elf_header->e_phnum = elf_32bits->e_phnum;
    file->elf_header->e_shentsize = elf_32bits->e_shentsize;
    file->elf_header->e_shnum = elf_32bits->e_shnum;
    file->elf_header->e_shstrndx = elf_32bits->e_shstrndx;
    return 1;
}

char            fill_elf_program_header(t_elf_file *file) {
    Elf32_Ehdr  *elf_32bits;
    Elf32_Phdr  *elf_program_header_32bits;

    if (!file->is_32bits) {
        file->elf_program_header = (file->mapped_mem + file->elf_header->e_phoff);
        return !(file->elf_program_header >= (file->mapped_mem + file->file_infos.st_size - sizeof(Elf64_Phdr)));
    }
    elf_32bits = (Elf32_Ehdr *) file->mapped_mem;
    if (NULL == (file->elf_program_header = malloc(sizeof(Elf64_Phdr))))
        return 0;
    elf_program_header_32bits = file->mapped_mem + elf_32bits->e_phoff;
    if (elf_program_header_32bits >= (file->mapped_mem + file->file_infos.st_size - sizeof(Elf32_Phdr)))
        return 0;
    file->elf_program_header->p_type = elf_program_header_32bits->p_type;
    file->elf_program_header->p_flags = elf_program_header_32bits->p_flags;
    file->elf_program_header->p_offset = elf_program_header_32bits->p_offset;
    file->elf_program_header->p_vaddr = elf_program_header_32bits->p_vaddr;
    file->elf_program_header->p_paddr = elf_program_header_32bits->p_paddr;
    file->elf_program_header->p_filesz = elf_program_header_32bits->p_filesz;
    file->elf_program_header->p_memsz = elf_program_header_32bits->p_memsz;
    file->elf_program_header->p_align = elf_program_header_32bits->p_align;
    return 1;
}

void fill_elf_section_header(Elf64_Shdr *dest, Elf32_Shdr *src) {
    dest->sh_name = src->sh_name;
    dest->sh_type = src->sh_type;
    dest->sh_flags = src->sh_flags;
    dest->sh_addr = src->sh_addr;
    dest->sh_offset = src->sh_offset;
    dest->sh_size = src->sh_size;
    dest->sh_link = src->sh_link;
    dest->sh_info = src->sh_info;
    dest->sh_addralign = src->sh_addralign;
    dest->sh_entsize = src->sh_entsize;
}

char                fill_elf_sections(t_elf_file *file) {
    int             i;
    unsigned int    size;
    Elf32_Shdr      *sections_32bits;

    if (!file->is_32bits) {
        file->elf_sections = (file->mapped_mem + file->elf_header->e_shoff);
        return !(file->elf_sections >= (file->mapped_mem + file->file_infos.st_size - (file->elf_header->e_phnum * sizeof(Elf64_Shdr))));
    }
    size = sizeof(Elf64_Shdr) * file->elf_header->e_shnum;
    if (NULL == (file->elf_sections = malloc(size)))
        return 0;
    sections_32bits = (file->mapped_mem + file->elf_header->e_shoff);
    if (sections_32bits >= (file->mapped_mem + file->file_infos.st_size - (file->elf_header->e_phnum * sizeof(Elf32_Shdr))))
        return 0;
    i = 0;
    while (i < file->elf_header->e_shnum) {
        fill_elf_section_header(&file->elf_sections[i], &sections_32bits[i]);
        i++;
    }
    return 1;
}