/*
** my_strncpy.c for  in /home/henon_t/rendu/Piscine_C_J06
** 
** Made by Thomas Henon
** Login   <henon_t@epitech.net>
** 
** Started on  Mon Oct  5 09:32:11 2015 Thomas Henon
** Last update Wed Jan  6 10:54:37 2016 thomas
*/

char    *my_strncpy(char *dest, char *src, unsigned int n)
{
  int   i;

  i = 0;
  while (src[i] && i < n)
    dest[i] = src[i++];
}
