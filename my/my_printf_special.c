/*
** my_printf_special.c for my_printf_special in /home/jay_w/rendu/project_s1/Unix_System/PSU_2015_my_printf
** 
** Made by WALTER JAY
** Login   <jay_w@epitech.net>
** 
** Started on  Thu Nov 12 13:59:45 2015 WALTER JAY
** Last update Fri Jun  3 17:06:16 2016 walter
*/

void	my_putprintable(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] >= 32 && str[i] < 127)
	my_putchar(str[i]);
      else
	{
	  my_putchar('\\');
    	  if (str[i] >=0 && str[i] < 8)
	    my_putstr("00");
	  else if (str[i] < 127)
	    my_putchar('0');
	  my_put_nbr_base(str[i], "01234567");
	}
      i = i + 1;
    }
}

void	my_put_uns_int(unsigned int u)
{
  if (u <= 0x80000000)
    my_put_nbr(u);
  else
    {
      my_put_uns_int(u / 10);
      my_put_uns_int(u % 10);
    }
}

void	my_put_uns_long(unsigned long l)
{
  if (l <= 0x80000000)
    my_put_nbr(l);
  else
    {
      my_put_uns_int(1 / 10);
      my_put_uns_int(1 % 10);
    }
}

void	my_put_pointer(unsigned long p)
{
  if (p <= 0x80000000)
    my_put_nbr_base(p, "0123456789abcdef");
  else
    {
      my_put_pointer(p / 16);
      my_put_pointer(p % 16);
    }
}

void	my_put_bin(unsigned long b)
{
  if (b <= 0x80000000)
    my_put_nbr_base(b, "01");
  else
    {
      my_put_bin(b / 2);
      my_put_bin(b % 2);
    }
}
