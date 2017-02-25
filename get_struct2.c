/*
** get_struct2.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Sat Feb 25 15:51:39 2017 thomas
** Last update Sat Feb 25 15:51:41 2017 thomas
*/

#include "common.h"

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

char            *lookup_string_symbol(t_elf_file *file,
                                      Elf64_Shdr *section_hdr,
                                      Elf64_Sym *sym) {
    Elf64_Shdr  *str_hdr;

    if (NULL == (str_hdr = get_section_header(file, section_hdr->sh_link)))
        return NULL;
    return file->mapped_mem + str_hdr->sh_offset + sym->st_name;
}