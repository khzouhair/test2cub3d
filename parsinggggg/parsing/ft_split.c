/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:54:26 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 02:49:57 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_c.h"

static size_t	count_w(char*s)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while ((s[i] == ' ' || s[i] == '\t') && s[i])
			i++;
		if (s[i])
		{
			count++;
			while ((s[i] != ' ' && s[i] != '\t') && s[i])
				i++;
		}
	}
	return (count);
}

static size_t	len_w(char *s)
{
	size_t	i;

	i = 0;
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	while (*s && *s != ' ' && *s != '\t')
	{
		s++;
		i++;
	}
	return (i);
}

static void	safe_free(char **arr, size_t i)
{
	size_t	n;

	n = 0;
	while (n < i)
	{
		free(arr[n]);
		n++;
	}
	free(arr);
}

static char	**alluc(char **arr, char *s , size_t count)
{
	size_t	i;
	size_t	wlen;
	size_t	j;

	wlen = 0;
	i = 0;
	while (i < count)
	{
		wlen = len_w(s);
		arr[i] = (char *)ft_alloc((wlen + 1) * sizeof(char), 1);
		j = 0;
		while (*s == ' ' || *s == '\t')
			s++;
		while (j < wlen)
			arr[i][j++] = *(s++);
		arr[i++][j] = '\0';
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char *s)
{
	size_t	count_words;
	char	**arr;

	if (s == NULL)
		return (NULL);
	count_words = count_w(s);
	arr = (char **)ft_alloc((count_words + 1) * sizeof(char *), 1);
	return (alluc(arr, s, count_words));
}
