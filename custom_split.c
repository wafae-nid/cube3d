/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:58:38 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/09/10 16:52:34 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c) && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	count_lengh_of_words(const char *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static char	*next_pointer_word(const char *s, char c, int *i)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	if (!s[*i])
		return (NULL);
	return ((char *)s + (*i));
}

static void	fill_in(char **ptr, const char *s, int *i, char c)
{
	int	index;

	index = 0;
	while (s[*i] && s[*i] != c)
	{
		(*ptr)[index] = s[*i];
		(*i)++;
		index++;
	}
	(*ptr)[index] = '\0';
}

char	**custom_split(const char *s, char c, int pid)
{
	int		i;
	int		j;
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = (char **)gcmalloc(sizeof(char *) * (count_words(s, c) + 1), pid);
	if (!ptr)
		return (NULL);
	(1 && (j = 0), (i = 0));
	while (j < count_words(s, c))
	{
		if (!next_pointer_word(s, c, &i))
			break ;
		ptr[j] = (char *)gcmalloc(count_lengh_of_words(s, c, i) + 1, pid);
		if (!ptr[j])
		{
			gcmalloc(0, 1);
			return (NULL);
		}
		fill_in(&ptr[j++], s, &i, c);
	}
	ptr[j] = NULL;
	return (ptr);
}
