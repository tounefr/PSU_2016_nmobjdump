/*
** my_evil_str.c for  in /home/henon_t/rendu/Piscine_C_J04
**
** Made by Thomas Henon
** Login   <henon_t@epitech.net>
**
** Started on  Thu Oct  1 18:53:44 2015 Thomas Henon
** Last update Fri Apr 15 13:22:33 2016 John Doe
*/

#include <string.h>
#include <stdlib.h>
#include "common.h"

char	*my_revstr(char *str)
{
  char	*reversed;
  int	i;

  if (NULL == (reversed = malloc(strlen(str) + 1)))
    return (NULL);
  reversed[strlen(str)] = 0;
  i = 0;
  while (i < strlen(str))
    {
      reversed[i] = str[strlen(str) - 1 - i];
      i++;
    }
  return (reversed);
}
