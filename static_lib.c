/*
** static_lib.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Fri Feb 24 15:48:40 2017 thomas
** Last update Fri Feb 24 15:48:41 2017 thomas
*/

#include <string.h>
#include "common.h"

static char is_static_library(t_elf_file *file) {
    return !strncmp((char*)file->mapped_mem, "!<arch>\n", 8);
}

static void    init_static_file_header(
        t_static_file_header *static_file_header)
{
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
        MY_ERROR(-1, "%s: %s: File truncated\n",
                 file->file_path, file->bin_path);

    memcpy(&static_file_header,
           (char*)file->mapped_mem + strlen(AR_MAGIC_NBR) + 1,
           sizeof(t_static_file_header));
    init_static_file_header(&static_file_header);

    if (static_file_header.end_chars[0] != 0x60 &&
            static_file_header.end_chars[1] != 0x0a)
        MY_ERROR(-1, "%s: %s: File truncated\n",
                 file->file_path, file->bin_path);
    return 1;
}
