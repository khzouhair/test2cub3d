/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:13:02 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 02:29:09 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_c.h"

char	*ft_strchr(char *s, int c)
{
	char	s1;
	char	*s2;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	s2 = (char *)s;
	s1 = (char)c;
	while (s2[i] != s1)
	{
		if (s2[i] == '\0')
			return (NULL);
		i++;
	}
	return (s2 + i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*arr;

	if (!s1)
	{
		s1 = (char *)ft_alloc(1 * sizeof(char), 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	arr = ft_alloc(1 + ft_strlen(s1) + ft_strlen(s2) * sizeof(char), 1);
	arr = ft_join(arr, s1, s2);
	return (arr);
}

char	*ft_join(char *dest, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
