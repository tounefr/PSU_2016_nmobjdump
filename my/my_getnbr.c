/*
** my_getnbr.c for  in /home/henon_t/rendu/Piscine_C_J06
**
** Made by Thomas Henon
** Login   <henon_t@epitech.net>
**
** Started on  Mon Oct  5 15:37:11 2015 Thomas Henon
** Last update Wed Jun 08 19:32:10 2016 thomas
*/

int	my_getnbr(char *str)
{
  int	i;
  int	nb;
  int	sign;

  nb = 0;
  sign = 1;
  i = -1;
  while (str && (str[++i] == '+' || str[i] == '-'))
    if (str[i] == '-')
      sign *= -1;
  i--;
  while (str && str[++i] >= '0' && str[i] <= '9')
    {
      nb *= 10;
      nb += str[i] - '0';
    }
  return (nb);
}
