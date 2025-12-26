/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:58:52 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 02:32:24 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_c.h"

static int	check(int c,char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	k;
	char	*d;

	i = 0;
	k = 0;
	if (!set || !s1)
		return (NULL);
	j = ft_strlen(s1);
	while (s1[i] != '\0' && check(s1[i], set) == 0)
		i++;
	while (j > 0 && check(s1[j - 1], set) == 0)
		j--;
	len = j - i;
	if (j < i)
		len = 0;
	d = ft_alloc(len + 1, 1);
	while (i < j)
		d[k++] = s1[i++];
	d[k] = '\0';
	return (d);
}

int	count_str(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_join2(char **str)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	count;
	char	*d;

	1 && (j = 0, k = 1, count = 0);
	if (!str)
		return (NULL);
	while (str[k])
		count += ft_strlen(str[k++]);
	k = 1;
	d = ft_alloc(count + count_str(str) - 1, 1);
	while (str[k])
	{
		i = 0;
		while (str[k] && i < ft_strlen(str[k]) && str[k][i] != '\n')
			d[j++] = str[k][i++];
		if (str[k + 1])
			d[j++] = ' ';
		k++;
	}
	d[j] = '\0';
	return (d);
}
