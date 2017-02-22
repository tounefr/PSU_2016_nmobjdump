/*
** my_strcat.c for  in /home/henon_t/rendu/Piscine_C_J07
** 
** Made by Thomas Henon
** Login   <henon_t@epitech.net>
** 
** Started on  Tue Oct  6 11:31:35 2015 Thomas Henon
** Last update Wed Jan  6 10:55:59 2016 thomas
*/

#include "stdlib.h"

char    *my_strcat(char *str1, char *str2)
{
  int   i;
  int   i2;
  char  *str3;

  if (0 == (str3 = malloc(my_strlen(str1) + my_strlen(str2) + 1)))
    return (NULL);
  i = 0;
  i2 = 0;
  while (str1 && str1[i2])
    str3[i++] = str1[i2++];
  i2 = 0;
  while (str2 && str2[i2])
    str3[i++] = str2[i2++];
  return (str3);
}
