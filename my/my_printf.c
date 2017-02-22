/*
** my_printf.c for my_printf in /home/walter/rendu/final/PSU_2015_tetris/srcs
** 
** Made by walter
** Login   <walter@epitech.net>
** 
** Started on  Fri Jun  3 16:37:22 2016 walter
** Last update Fri Jun  3 17:05:56 2016 walter
*/

#include <stdarg.h>
#include <stdio.h>

static int	count_args(const char *str)
{
  int		i;
  int		count;

  i = 0;
  count = 0;
  while (str[i] != '\0')
    {
      if (str [i] == '%')
	count = count + 1;
      i = i + 1;
    }
  return (count);
}

static void	gestion_special(va_list my, const char *format, int i)
{
  if (format[i] == 'p')
    {
      my_putstr("0x");
      my_put_pointer(va_arg(my, unsigned long));
    }
  else if (format[i] == 'l')
    my_put_uns_long(va_arg(my, unsigned long));
  else if (format[i] == '%')
    my_putchar('%');
  else
    {
      my_putchar('%');
      my_putchar(format[i]);
    }
}

static int	gestion_args(va_list my, const char *format, int i)
{
  if (format[i] == 's')
    my_putstr(va_arg(my, char*));
  else if (format[i] == 'd' || format[i] == 'i')
    my_put_nbr(va_arg(my, int));
  else if (format[i] == 'o')
    my_put_nbr_base(va_arg(my, int), "01234567");
  else if (format[i] == 'x')
    my_put_nbr_base(va_arg(my, int), "0123456789abcdef");
  else if (format[i] == 'X')
    my_put_nbr_base(va_arg(my, int), "0123456789ABCDEF");
  else if (format[i] == 'c')
    my_putchar(va_arg(my, int));
  else if (format[i] == 'S')
    my_putprintable(va_arg(my, char*));
  else if (format[i] == 'u')
    my_put_uns_int(va_arg(my, unsigned int));
  else if (format[i] == 'b')
    my_put_bin(va_arg(my, unsigned long));
  else
    gestion_special(my, format, i);
  return (42);
}

int		my_printf(const char *format, ...)
{
  va_list	my;
  int		size;
  int		i;

  i = 0;
  size = count_args(format);
  va_start(my, format);
  while (format[i] != '\0')
    {
      if (format[i] == '%')
	{
	  i = i + 1;
	  gestion_args(my, format, i);
	}
      else
	my_putchar(format[i]);
      i = i + 1;
    }
  va_end(my);
  return (42);
}
