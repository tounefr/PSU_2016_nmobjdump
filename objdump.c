#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include "common.h"

char is_static_library(t_elf_file *file) {
    return !strncmp((char*)file->mapped_mem, "!<arch>\n", 8);
}

void    replace_spaces(void *ptr, int size) {
    int i;

    i = 0;
    while (i < size) {
        if (((char*)ptr)[i] == ' ')
            ((char*)ptr)[i] = 0;
        i++;
    }
}

void    init_static_file_header(t_static_file_header *static_file_header) {
    int i;

    i = 0;
    while (i < sizeof(t_static_file_header)) {
        if (((char*)static_file_header)[i] == ' ') {
            ((char*)static_file_header)[i] = 0;
        }
        i++;
    }
}

char handle_static_library(t_elf_file *file) {
    t_static_file_header static_file_header;

    if (!is_static_library(file))
        return 0;
    if (sizeof(t_static_file_header) >= file->file_infos.st_size)
        MY_ERROR(-1, "%s: %s: File truncated\n", file->file_path, file->bin_path);

    memcpy(&static_file_header, (char*)file->mapped_mem + strlen(AR_MAGIC_NBR) + 1, sizeof(t_static_file_header));
    init_static_file_header(&static_file_header);

    if (static_file_header.end_chars[0] != 0x60 && static_file_header.end_chars[1] != 0x0a)
        MY_ERROR(-1, "%s: %s: File truncated\n", file->file_path, file->bin_path);
    return 1;
}

char            objdump(char *bin_path, char *file_path) {
    t_elf_file  file;
    void        *data;

    init_elf_file(&file);
    file.file_path = file_path;
    file.bin_path = bin_path;
    if (-1 == (file.fd = open(file_path, O_RDONLY)) ||
        -1 == fstat(file.fd, &file.file_infos))
        MY_ERROR(0, "%s: '%s': No such file\n", bin_path, file_path);
    if (!S_ISREG(file.file_infos.st_mode))
        MY_ERROR(0, "%s: Warning: '%s' is not an ordinary file\n", bin_path, file_path);
    file.mapped_mem = mmap(NULL, file.file_infos.st_size,
                           PROT_READ, MAP_SHARED, file.fd, 0);
    if (file.mapped_mem == MAP_FAILED)
        STRERRNO(0);
    if (!(handle_static_library(&file) || handle_elf_file(&file)))
        return 0;
    close(file.fd);
    if (-1 == munmap(file.mapped_mem, file.file_infos.st_size))
        STRERRNO(0);
    return 1;
}

int         main(int argc, char **argv) {
    int i;
    int returnv;

    i = 1;
    if (argc == 1)
        return !objdump(argv[0], "a.out");
    returnv = 0;
    while (i < argc) {
        if (!objdump(argv[0], argv[i++]))
            returnv = 1;
    }
    return returnv;
}