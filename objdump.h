
#ifndef PSU_2016_NMOBJDUMP_OBJDUMP_H
#define PSU_2016_NMOBJDUMP_OBJDUMP_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>

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

extern struct s_flags g_flags[N_FLAGS];

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
    Elf64_Shdr *elf_str_section;

    struct stat file_infos;
    void *mapped_mem;
    char *file_path;
    int fd;
    char is_32bits;
    void *section_strings;
    int flags;
} t_elf_file;

void print_flags(t_elf_file *file);

int cpt_flags(t_elf_file *file);

void print_header(t_elf_file *file);

void print_section_hexadecimal(void *section_content,
                               unsigned int *offset,
                               Elf64_Shdr *section_hdr);

void print_section_printable(void *section_content,
                             unsigned int *offset,
                             Elf64_Shdr *section_hdr);

void print_section(t_elf_file *file, Elf64_Shdr *section_hdr);

void print_sections(t_elf_file *file);

char pre_check_elf_header(t_elf_file *file);

char objdump(char *file_path);

char is_printable(char cur_char);

char error(char *str, int returnv);

void fill_elf_header(t_elf_file *file);

void fill_elf_program_header(t_elf_file *file);

void fill_elf_section_header(Elf64_Shdr *dest, Elf32_Shdr *src);

void fill_elf_sections(t_elf_file *file);

#endif //PSU_2016_NMOBJDUMP_OBJDUMP_H
