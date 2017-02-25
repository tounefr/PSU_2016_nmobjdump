/*
** get_struct.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Fri Feb 24 18:21:29 2017 thomas
** Last update Fri Feb 24 18:21:30 2017 thomas
*/

#include <stdlib.h>
#include "common.h"

Elf64_Ehdr *get_elf_header(t_elf_file *file) {
    if (file->elf_header)
        return file->elf_header;
    if (file->is_32bits) {
        if (file->file_infos.st_size < sizeof(Elf32_Ehdr))
            return NULL;
        if (NULL == (file->elf_header = malloc(sizeof(Elf64_Ehdr))))
            return NULL;
        fill_elf_header(file->elf_header, file->mapped_mem);
        return file->elf_header;
    }
    if (file->file_infos.st_size < sizeof(Elf64_Ehdr))
        return NULL;
    file->elf_header = file->mapped_mem;
    return file->elf_header;
}

Elf64_Phdr *get_program_header(t_elf_file *file) {
    Elf64_Ehdr *elf_header;
    void *program_header;

    if (file->elf_program_header)
        return file->elf_program_header;
    if (NULL == (elf_header = get_elf_header(file)))
        return NULL;
    program_header = file->mapped_mem + elf_header->e_phoff;
    if (file->is_32bits) {
        if (program_header > file->end - sizeof(Elf32_Phdr))
            return NULL;
        if (NULL == (file->elf_program_header = malloc(sizeof(Elf64_Phdr))))
            return NULL;
        fill_elf_program_header(file->elf_program_header, program_header);
        return file->elf_program_header;
    }
    if ((void*)file->elf_program_header > file->end - sizeof(Elf64_Phdr))
        return NULL;
    file->elf_program_header = program_header;
    return file->elf_program_header;
}

char sections_hdr_to_64bits(t_elf_file *file) {
    Elf64_Ehdr *elf_header;
    Elf32_Shdr *elf_sections;

    if (NULL == (elf_header = get_elf_header(file)))
        return 0;
    if (!file->is_32bits) {
        file->elf_sections = file->mapped_mem + elf_header->e_shoff;
        return 1;
    }
    elf_sections = file->mapped_mem + elf_header->e_shoff;
    if (NULL == (file->elf_sections = malloc(sizeof(Elf64_Shdr) *
                                                     elf_header->e_shnum)))
        return 0;
    fill_elf_sections(file->elf_sections, elf_sections, elf_header->e_shnum);
    return 1;
}

Elf64_Shdr *get_section_header(t_elf_file *file, unsigned int i) {
    Elf64_Ehdr *elf_header;

    if (NULL == (elf_header = get_elf_header(file)))
        return NULL;
    if (i > elf_header->e_shnum)
        return NULL;
    if (!file->elf_sections && !sections_hdr_to_64bits(file))
        return NULL;
    /*if ((void*)&file->elf_sections[i] > file->end - sizeof(Elf64_Shdr))
        return 1;*/
    return &file->elf_sections[i];
}

Elf64_Sym *get_symbols(t_elf_file *file,
                       Elf64_Shdr *section_hdr,
                       int *nbr_symbols) {
    Elf64_Sym *symtabs_64;
    Elf32_Sym *symtabs_32;

    *nbr_symbols = section_hdr->sh_size / section_hdr->sh_entsize;
    if (!file->is_32bits)
        return file->mapped_mem + section_hdr->sh_offset;
    if (NULL == (symtabs_64 = malloc(*nbr_symbols * sizeof(Elf64_Sym))))
        return NULL;
    symtabs_32 = file->mapped_mem + section_hdr->sh_offset;
    fill_symtabs(symtabs_64, symtabs_32, *nbr_symbols);
    return symtabs_64;
}

void *get_section_content(t_elf_file *file, unsigned int i) {
    Elf64_Shdr *section_hdr;

    if (NULL == (section_hdr = get_section_header(file, i)))
        return NULL;
    /*if (file->mapped_mem + section_hdr->sh_offset + section_hdr->sh_size >
            file->file_infos.st_size)
        return NULL;*/
    return file->mapped_mem + section_hdr->sh_offset;
}

char *lookup_string(t_elf_file *file, unsigned int i) {
    Elf64_Shdr *section_hdr;

    section_hdr = get_section_header(file, file->elf_header->e_shstrndx);
    if (NULL == section_hdr)
        return NULL;
    if (section_hdr->sh_type != SHT_STRTAB)
        return NULL;
    return (char*)(file->mapped_mem + section_hdr->sh_offset + i);
}
