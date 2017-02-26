/*
** sort_symbols.c for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Sat Feb 25 14:18:36 2017 thomas
** Last update Sat Feb 25 14:18:37 2017 thomas
*/

#include <stdlib.h>
#include <string.h>
#include "common.h"

char                    symbols_list_push(t_sorted_symbols **head,
                                          Elf64_Sym *elem)
{
    t_sorted_symbols    *new_sorted_sym;
    t_sorted_symbols    *last;

    if (NULL == (new_sorted_sym = malloc(sizeof(t_sorted_symbols))))
        return 0;
    last = *head;
    while (last && last->next)
        last = last->next;
    new_sorted_sym->next = NULL;
    new_sorted_sym->symbol = elem;
    if (*head == NULL)
        *head = new_sorted_sym;
    else
        last->next = new_sorted_sym;
    return 1;
}

char symbols_list_push_syms(t_sorted_symbols **sorted_symbols,
                          Elf64_Sym *sym_tabs,
                          int nbr_syms) {
    int i;

    i = 0;
    while (i < nbr_syms) {
        if (!symbols_list_push(sorted_symbols, &sym_tabs[i]))
            return 0;
        i++;
    }
    return 1;
}

static void     swap_ptrs(void **ptr1, void **ptr2) {
    void        *tmp;

    tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

t_sorted_symbols        *sort_symbols(t_elf_file *file,
                               Elf64_Shdr *section_hdr,
                               Elf64_Sym *sym_tabs,
                               int nbr_syms) {
    t_sorted_symbols    *sorted_symbols;
    t_sorted_symbols    *cur;
    char                sorted;
    char                *names[2];

    sorted_symbols = NULL;
    symbols_list_push_syms(&sorted_symbols, sym_tabs, nbr_syms);
    sorted = 0;
    while (!sorted) {
        sorted = 1;
        cur = sorted_symbols;
        while (cur && cur->next) {
            names[0] = lookup_string_symbol(file, section_hdr, cur->symbol);
            names[1] = lookup_string_symbol(file,
                                            section_hdr, cur->next->symbol);
            if (strcmp(names[1], names[0]) < 0) {
                sorted = 0;
                swap_ptrs((void**)&cur->symbol, (void**)&cur->next->symbol);
            }
            cur = cur->next;
        }
    }
    return sorted_symbols;
}
