/*
** my_putnbr.c for  in /home/henon_t/rendu/Piscine_C_J06/ex_16
** 
** Made by Thomas Henon
** Login   <henon_t@epitech.net>
** 
** Started on  Mon Oct  5 15:16:34 2015 Thomas Henon
** Last update Fri Jan  8 18:07:39 2016 thomas
*/

int	my_put_unbr(unsigned int nb)
{
  int	neg;

  neg = 0;
  if (nb >= 10)
    my_put_nbr(nb / 10);
  my_putchar(nb % 10 + '0');
}
