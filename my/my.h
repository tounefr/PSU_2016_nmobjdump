/*
** my.h for  in /home/henon_t/rendu/Piscine_C_J09/ex_01
**
** Made by Thomas Henon
** Login   <henon_t@epitech.net>
**
** Started on  Thu Oct  8 10:17:02 2015 Thomas Henon
** Last update Wed Jun 08 18:48:23 2016 thomas
*/

#ifndef __MY_H__
# define __MY_H__

#include <stdlib.h>

void	my_putchar(char c);
int	my_isneg(int nb);
int	my_put_nbr(int nb);
int	my_swap(int *a, int *b);
int	my_putstr(char *str);
int	my_strlen(char *str);
int	my_getnbr(char *str);
void	my_sort_int_tab(int *tab, int size);
int	my_power_rec(int nb, int power);
int	my_square_root(int nb);
int	my_is_prime(int nombre);
int	my_find_prime_sup(int nb);
char	*my_strcpy(char *dest, char *src);
char	*my_strncpy(char *dest, char *src, unsigned int n);
char	*my_revstr(char *str);
char	*my_strstr(char *str, char *to_find);
int	my_strcmp(char *s1, char *s2);
int	my_strncmp(char *s1, char *s2, int nb);
char	*my_strupcase(char *str);
char	*my_strlowcase(char *str);
char	*my_strcapitalize(char *str);
int	my_str_isalpha(char *str);
int	my_str_isnum(char *str);
int	my_str_islower(char *str);
int	my_str_isupper(char *str);
int	my_str_isprintable(char *str);
int	my_showstr(char *str);
int	my_showmem(char *str, int size);
char	*my_strcat(char *dest, char *src);
char	*my_strncat(char *dest, char *src, int nb);
char	**my_str_to_wordtab(char *str, char d);
char	*my_strdup(char *str1);
char	*my_int_to_str(int nbr);
void	my_putprintable(char *str);
void	my_put_uns_int(unsigned int u);
void	my_put_uns_long(unsigned long u);
void	my_put_uns_pointer(unsigned long u);
void	my_put_bin(unsigned long u);
int	my_printf(const char *format, ...);

#endif /*! MY_H_ */
