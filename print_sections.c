
#include <stdio.h>
#include <string.h>
#include "objdump.h"

void print_section_hexadecimal(void *section_content,
                               unsigned int *offset,
                               Elf64_Shdr *section_hdr) {
    char cur_char;
    Elf64_Off off;
    int i;

    i = 0;
    off = section_hdr->sh_offset + *offset;
    printf(" %04lx ", off);
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

void print_section_printable(void *section_content,
                             unsigned int *offset,
                             Elf64_Shdr *section_hdr) {
    char cur_char;
    int i;

    i = 0;
    while (i < 16) {
        if ((i + *offset) < section_hdr->sh_size) {
            cur_char = ((char *) section_content)[*offset + i];
            if (is_printable(cur_char))
                printf("%c", cur_char);
            else
                printf(".");
        } else
            printf(" ");
        i++;
    }
}

void print_section(t_elf_file *file, Elf64_Shdr *section_hdr) {
    char *section_name;
    void *section_content;
    unsigned int offset;

    section_name = (char *) (file->section_strings + section_hdr->sh_name);
    if (section_hdr->sh_type == SHT_STRTAB ||
        section_hdr->sh_type == SHT_NULL ||
        section_hdr->sh_size == 0)
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

void print_sections(t_elf_file *file) {
    int i;

    if (file->elf_header->e_shoff == 0 || file->elf_header->e_shnum == 0)
        return;
    fill_elf_sections(file);
    file->elf_str_section = (Elf64_Shdr * ) & file->elf_sections[file->elf_header->e_shstrndx];
    file->section_strings = file->mapped_mem + file->elf_str_section->sh_offset;
    i = 0;
    while (i < file->elf_header->e_shnum)
        print_section(file, &file->elf_sections[i++]);
}