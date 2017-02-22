/*
** my_str_isnum.c for  in /home/henon_t/rendu/Piscine_C_J06
**
** Made by Thomas Henon
** Login   <henon_t@epitech.net>
**
** Started on  Mon Oct  5 13:55:13 2015 Thomas Henon
** Last update Fri May 27 20:06:55 2016 thomas
*/

int	my_str_isnum(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] < '0' || str[i] > '9')
	return (0);
      i++;
    }
  return (1);
}
