/*
** fill_elf.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Fri Feb 24 15:46:00 2017 thomas
** Last update Fri Feb 24 15:46:01 2017 thomas
*/

#include <stdlib.h>
#include "common.h"

void            fill_elf_header(Elf64_Ehdr *dest, Elf32_Ehdr *src) {
    int         i;

    i = 0;
    while (i < EI_NIDENT) {
        dest->e_ident[i] = src->e_ident[i];
        i++;
    }
    dest->e_type = src->e_type;
    dest->e_machine = src->e_machine;
    dest->e_version = src->e_version;
    dest->e_entry = src->e_entry;
    dest->e_phoff = src->e_phoff;
    dest->e_shoff = src->e_shoff;
    dest->e_flags = src->e_flags;
    dest->e_ehsize = src->e_ehsize;
    dest->e_phentsize = src->e_phentsize;
    dest->e_phnum = src->e_phnum;
    dest->e_shentsize = src->e_shentsize;
    dest->e_shnum = src->e_shnum;
    dest->e_shstrndx = src->e_shstrndx;
}

void            fill_elf_program_header(Elf64_Phdr *dest, Elf32_Phdr *src) {
    dest->p_type = src->p_type;
    dest->p_flags = src->p_flags;
    dest->p_offset = src->p_offset;
    dest->p_vaddr = src->p_vaddr;
    dest->p_paddr = src->p_paddr;
    dest->p_filesz = src->p_filesz;
    dest->p_memsz = src->p_memsz;
    dest->p_align = src->p_align;
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

void fill_elf_sections(Elf64_Shdr *dest, Elf32_Shdr *src, unsigned int nbr) {
    int i;

    i = 0;
    while (i < nbr) {
        fill_elf_section_header(&dest[i], &src[i]);
        i++;
    }
}
