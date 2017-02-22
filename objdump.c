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
    return !strncmp((char*)file->mapped_mem, "!<arch>", 7);
}

char handle_static_library(t_elf_file *file) {
    return 0;
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