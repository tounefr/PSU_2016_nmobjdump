#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "common.h"

char            objdump(char *file_path) {
    t_elf_file  file;
    void        *data;

    init_elf_file(&file);
    file.file_path = file_path;
    if (-1 == (file.fd = open(file_path, O_RDONLY)))
        return error(strerror(errno), 0);
    if (-1 == fstat(file.fd, &file.file_infos))
        return error("fstat error", 0);
    file.mapped_mem = mmap(NULL, file.file_infos.st_size,
                           PROT_READ, MAP_SHARED, file.fd, 0);
    if (file.mapped_mem == MAP_FAILED)
        return error(strerror(errno), 0);
    if (!pre_check_elf_header(&file))
        return error("Not an ELF file", 0);
    print_header(&file);
    print_sections(&file);
    close(file.fd);
    /*if (file.is_32bits) {
        if (file.elf_program_header)
            free(file.elf_program_header);
        if (file.elf_sections)
            free(file.elf_sections);
    }*/
    if (-1 == munmap(file.mapped_mem, file.file_infos.st_size))
        return error(strerror(errno), 0);
}

int         main(int argc, char **argv) {
    int     i;

    i = 1;
    while (i < argc)
        objdump(argv[i++]);
}