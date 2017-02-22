/*
** my_strdup.c for  in /home/thomas/Documents/epitech/mylib/my
** 
** Made by thomas
** Login   <thomas@epitech.net>
** 
** Started on  Thu Jan  7 13:27:42 2016 thomas
** Last update Thu Jan  7 13:59:35 2016 thomas
*/

#include <stdlib.h>
#include "my.h"

char	*my_strdup(char *str1)
{
  char	*str2;
  int	i;

  if (0 == (str2 = malloc(my_strlen(str1) + 1)))
    return (NULL);
  i = 0;
  while (str1[i])
    {
      str2[i] = str1[i];
      i++;
    }
  str2[i] = '\0';
  return (str2);
}
