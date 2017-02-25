/*
** common.h for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Fri Feb 24 15:46:07 2017 thomas
** Last update Fri Feb 24 15:46:08 2017 thomas
*/

#ifndef PSU_2016_NMOBJDUMP_OBJDUMP_H
#define PSU_2016_NMOBJDUMP_OBJDUMP_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>
#include <stdio.h>

#define MY_ERROR(v_, f_, ...) { fprintf(stderr, (f_), __VA_ARGS__); return v_; }
#define STRERRNO(v_) { fprintf(stderr, "%s\n", strerror(errno)); return v_; }
#define AR_MAGIC_NBR "!<arch>"

typedef struct s_common_elf {
    unsigned char e_indent[EI_NIDENT];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
} t_common_elf;

typedef struct s_elf_file {
    Elf64_Ehdr *elf_header;
    Elf64_Phdr *elf_program_header;
    Elf64_Shdr *elf_sections;

    char *bin_path;
    struct stat file_infos;
    void *mapped_mem;
    void *end;
    char *file_path;
    int fd;
    char is_32bits;
    int flags;
} t_elf_file;

typedef struct __attribute__((packed)) s_static_file_header {
    char file_name[16];
    char edit_timestamp[12];
    char owner_id[6];
    char group_id[6];
    char file_mode[8];
    char file_size[10];
    char end_chars[2];
} t_static_file_header;

#define N_FLAGS 10
enum e_flags {
    BFD_NO_FLAGS = 0x00,
    HAS_RELOC = 0x01,
    EXEC_P = 0x02,
    HAS_LINENO = 0x04,
    HAS_DEBUG = 0x08,
    HAS_SYSMS = 0x10,
    HAS_LOCALS = 0x20,
    DYNAMIC = 0x40,
    WP_TEXT = 0x80,
    D_PAGED = 0x100
};

struct s_flags {
    enum e_flags k;
    char *v;
};

typedef struct s_sorted_symbols {
    Elf64_Sym *symbol;
    struct s_sorted_symbols *next;
} t_sorted_symbols;

extern struct s_flags g_flags[N_FLAGS];

void print_header(t_elf_file *file);

void print_sections(t_elf_file *file);

char handle_elf_file(t_elf_file *file);

char is_printable(char cur_char);

char *printf_format_offset(Elf64_Shdr *section_hdr);

char *str_concat(char *str1, char *str2);

void init_elf_file(t_elf_file *file);

char *my_int_to_str(int nbr);

char *my_revstr(char *str);

char *my_strcat(char *str1, char *str2);

char handle_static_library(t_elf_file *file);

Elf64_Shdr *get_sectionhdr(t_elf_file *file, unsigned int i);

Elf64_Ehdr *get_elf_header(t_elf_file *file);

Elf64_Phdr *get_program_header(t_elf_file *file);

Elf64_Shdr *get_section_header(t_elf_file *file, unsigned int i);

void *get_section_content(t_elf_file *file, unsigned int i);

void fill_elf_header(Elf64_Ehdr *dest, Elf32_Ehdr *src);

void fill_elf_program_header(Elf64_Phdr *dest, Elf32_Phdr *src);

void fill_elf_section_header(Elf64_Shdr *dest, Elf32_Shdr *src);

void fill_elf_sections(Elf64_Shdr *dest, Elf32_Shdr *src, unsigned nbr);

char *lookup_string(t_elf_file *file, unsigned int i);

void fill_symtabs(Elf64_Sym *dest, Elf32_Sym *src, unsigned int nbr);

Elf64_Sym *get_symbols(t_elf_file *file, Elf64_Shdr *section_hdr, int *nbr_symbols);

char print_symbols(t_elf_file *file,
                   t_sorted_symbols *sorted_symbols,
                   Elf64_Shdr *section_hdr);

char *lookup_string_symbol(t_elf_file *file, Elf64_Shdr *section_hdr, Elf64_Sym *sym);

t_sorted_symbols *sort_symbols(t_elf_file *file,
                               Elf64_Shdr *section_hdr,
                               Elf64_Sym *sym_tabs,
                               int nbr_syms);

#endif //PSU_2016_NMOBJDUMP_OBJDUMP_H
