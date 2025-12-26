/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:52:56 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 02:49:25 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_c.h"

int	check_coma(char *str)
{
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == ',')
			count++;
		j++;
	}
	if (count != 2)
		return (-1);
	return (1);
}

int	ft_atoi(char *str, int *i)
{
	int	nb;
	int	k;

	nb = 0;
	k = *i;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (str[*i] == '-')
		return (-1);
	if (str[*i] == '+')
		(*i)++;
	while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
	{
		nb = nb * 10 + (str[*i] - '0');
		(*i)++;
	}
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (str[*i] == ',')
	{
		(*i)++;
	}
	if (nb > 255)
		return (-1);
	return (nb);
}
