/*
** print_sections.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Fri Feb 24 15:47:18 2017 thomas
** Last update Fri Feb 24 15:47:18 2017 thomas
*/

#include <stdio.h>
#include <string.h>
#include "common.h"

static void            print_section_hexadecimal(
                                void *section_content,
                                unsigned int *offset,
                                Elf64_Shdr *section_hdr) {
    char        cur_char;
    Elf64_Off   off;
    int         i;
    char        *format_printf;
    i = 0;
    off = section_hdr->sh_addr + *offset;

    format_printf = printf_format_offset(section_hdr);
    printf(format_printf, off);
    while (i < 16) {
        if ((i + *offset) < section_hdr->sh_size) {
            cur_char = ((char *) section_content)[*offset + i];
            printf("%02x", cur_char & 0xff);
        } else
            printf("  ");
        i++;
        if (i % 4 == 0)
            printf(" ");
    }
    printf(" ");
}

static void        print_section_printable(void *section_content,
                                    unsigned int *offset,
                                    Elf64_Shdr *section_hdr) {
    char    cur_char;
    int     i;

    i = 0;
    while (i < 16) {
        if ((i + *offset) < section_hdr->sh_size) {
            cur_char = ((char *) section_content)[*offset + i];
            printf("%c", is_printable(cur_char) ? cur_char : '.');
        } else
            printf(" ");
        i++;
    }
}

static char    check_print_section(t_elf_file *file, Elf64_Shdr *section_hdr) {
    char *section_name;
    Elf64_Shdr *section_str;

    if (NULL == (section_name = lookup_string(file, section_hdr->sh_name)))
        return 0;
    section_str = get_section_header(file, file->elf_header->e_shstrndx);
    if (section_str == section_hdr ||
        section_hdr->sh_type == SHT_NOBITS ||
        section_hdr->sh_type == SHT_NULL ||
        section_hdr->sh_size == 0)
        return 0;
    if (section_hdr->sh_type != SHT_PROGBITS && file->elf_header->e_type == ET_REL)
        return 0;
    if (section_hdr->sh_type == SHT_SYMTAB && file->elf_header->e_type == ET_DYN)
        return 0;
    if (!strcmp(section_name, ".strtab") &&  file->elf_header->e_type == ET_DYN)
        return 0;
    return 1;
}

static void                print_section(t_elf_file *file, Elf64_Shdr *section_hdr) {
    char            *section_name;
    void            *section_content;
    unsigned int    offset;

    if (NULL == (section_name = lookup_string(file, section_hdr->sh_name)))
        return;
    if (!check_print_section(file, section_hdr))
        return;
    section_content = file->mapped_mem + section_hdr->sh_offset;
    printf("Contents of section %s:\n", section_name);
    offset = 0;
    while (offset < section_hdr->sh_size) {
        print_section_hexadecimal(section_content, &offset, section_hdr);
        print_section_printable(section_content, &offset, section_hdr);
        printf("\n");
        offset += 16;
    }
}

void    print_sections(t_elf_file *file) {
    int i;
    char            *section_name;
    void            *section_content;
    unsigned int    offset;
    Elf64_Shdr *section_hdr;

    if (file->elf_header->e_shoff == 0 || file->elf_header->e_shnum == 0)
        return;
    i = 0;
    while (i < file->elf_header->e_shnum) {
        if (NULL == (section_hdr = get_section_header(file, i)))
            return;
        if (NULL == (section_name = lookup_string(file, section_hdr->sh_name)))
            return;
        if (check_print_section(file, section_hdr)) {
            if ((section_content = get_section_content(file, i))) {
                printf("Contents of section %s:\n", section_name);
                offset = 0;
                while (offset < section_hdr->sh_size) {
                    print_section_hexadecimal(section_content, &offset, section_hdr);
                    print_section_printable(section_content, &offset, section_hdr);
                    printf("\n");
                    offset += 16;
                }
            }
        }
        i++;
    }
}