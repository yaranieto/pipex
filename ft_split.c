/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:04:41 by ynieto-s          #+#    #+#             */
/*   Updated: 2025/07/11 17:04:59 by ynieto-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_fill_to_array(const char *s, char c, int *index);
static int	ft_size_word(const char *s, char c);
static int	ft_div_word(const char *s, char c);
static void	ft_clean_mem(char **array);

char	**ft_split(const char *s, char c)
{
	char	**array;
	int		size_array;
	int		index;
	int		i;

	if (s == NULL)
		return (NULL);
	size_array = ft_div_word(s, c);
	array = (char **)malloc((size_array + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	index = 0;
	i = 0;
	while (i < size_array)
	{
		array[i] = ft_fill_to_array(s, c, &index);
		if (!array[i])
		{
			ft_clean_mem(array);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}

static char	*ft_fill_to_array(const char *s, char c, int *index)
{
	int			size;
	int			i;
	char		*word;

	while (s[*index] == c)
		*index = *index + 1;
	size = ft_size_word (&s[*index], c);
	word = malloc((size + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (s[*index] && s[*index] != c)
	{
		word[i] = s[*index];
		i++;
		*index = *index + 1;
	}
	word[i] = '\0';
	return (word);
}

static int	ft_size_word(const char *s, char c)
{
	int	size;

	size = 0;
	while (*s == c)
		s++;
	while (*s && *s != c)
	{
		size++;
		s++;
	}
	return (size);
}

static int	ft_div_word(const char *s, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 1;
	while (*s)
	{
		if (*s != c && flag)
		{
			count++;
			flag = 0;
		}
		else if (*s == c)
			flag = 1;
		s++;
	}
	return (count);
}

static void	ft_clean_mem(char **array)
{
	int	i;

	if (array != NULL)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}