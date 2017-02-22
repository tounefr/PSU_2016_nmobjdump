/*
** my_strcmp.c for  in /home/henon_t/rendu/Piscine_C_J06
** 
** Made by Thomas Henon
** Login   <henon_t@epitech.net>
** 
** Started on  Mon Oct  5 10:39:27 2015 Thomas Henon
** Last update Fri Jan  8 18:07:48 2016 thomas
*/

int	my_strncmp(char *s1, char *s2, int n)
{
  char	*curChar;
  char	i;

  i = 0;
  curChar = s1;
  while (*curChar != '\0' && i < n)
    {
      if ((s1[i] - s2[i]) != 0)
	return (s1[i] - s2[i]);
      i = i + 1;
      curChar = curChar + 1;
    }
  return (0);
}
