/*
** my_str_to_wordtab.c for  in /home/thomas/Documents/epitech/mylib
** 
** Made by thomas
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Wed Nov  4 12:32:23 2015 thomas
** Last update Thu May 26 11:13:38 2016 Thomas HENON
*/

#include <stdlib.h>
#include "my.h"

char	is_alpha(char c)
{
  if (c >= 'a' && c <= 'z')
    return (1);
  if (c >= 'A' && c <= 'Z')
    return (1);
  if (c >= '0' && c <= '9')
    return (1);
  return (0);
}

int	nbr_words(char *str, char d)
{
  int	i;
  int	nbr_words;

  nbr_words = 0;
  i = 0;
  while (str[i] != 0)
    {
      if (str[i] == d)
	{
	  nbr_words++;
	  while (str[i] == d)
	    i++;
	}
      else
	i++;
    }
  return (nbr_words + 1);
}

char	*malloc_word(char *str, int start, int end)
{
  char	*word;
  int	i;

  word = malloc(end - start + 1);
  if (!word)
    return (0);
  i = 0;
  while (start <= end)
    {
      word[i] = str[start];
      start++;
      i++;
    }
  return (word);
}

char	*get_next_word(char *str, int *i, char d)
{
  int	start;
  char	*word;

  start = *i;
  while (str[*i])
    {
      if (str[*i] == d)
	{
	  if (NULL == (word = malloc(*i - start + 1)))
	    return (NULL);
	  word[*i - start] = '\0';
	  my_strncpy(word, &str[start], *i - start);
	  return (word);
	}
      (*i)++;
    }
  return (my_strdup(&str[start]));
}

char	**my_str_to_wordtab(char *str, char d)
{
  char	**words;
  char	nbr_words_;
  int	i;
  int	i2;

  i = 0;
  i2 = 0;
  nbr_words_ = nbr_words(str, d);
  if (nbr_words_ < 2)
    return (NULL);
  if (!(words = malloc(nbr_words_ + 1)))
    return (0);
  while (i < nbr_words_)
    {
      words[i++] = get_next_word(str, &i2, d);
      i2++;
    }
  return (words);
}
