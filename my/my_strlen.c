/*
** my_putstr.c for  in /home/henon_t/rendu/Piscine_C_J04
**
** Made by Thomas Henon
** Login   <henon_t@epitech.net>
**
** Started on  Thu Oct  1 09:49:52 2015 Thomas Henon
** Last update Sat May 28 11:37:51 2016 thomas
*/

#include <stdlib.h>

int	my_strlen(char *str)
{
  int	i;

  if (str == NULL)
    return (0);
  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}
