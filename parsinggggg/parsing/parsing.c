/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:02:22 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 02:53:19 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_c.h"

int	find_max(char **lines)
{
	int	i;
	int	j;
	int	max;
	char	*str;

	i = 0;
	max = 0;
	while (lines[i])
	{
		str = lines[i];
		j = 0;
		while (str[j])
			j++;
		if (max < j)
			max = j;
		i++;
	}
	return (max);
}

int	check_flag(t_map *map)
{
	if (!map->flag->c || !map->flag->f || !map->flag->ea
		|| !map->flag->no || !map->flag->so || !map->flag->we)
		return (write(2, "error::missing identifier\n", 27), 0);
	else if (map->flag->c > 1 || map->flag->f > 1 || map->flag->ea > 1
		|| map->flag->no > 1 || map->flag->so > 1 || map->flag->we > 1)
		return (write(2, "error::duplicate identifier\n", 29), 0);
	return (1);
}

int	find_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (is_valid(map->map[i][j]) && map->map[i][j] != '1' && map->map[i][j] != '0')
				{
					map->flag->p += 1;
					if (map->flag->p > 1)
						return (write(2, "error::duplicate player\n", 25), 0);
					map->y = i;
					map->x = j;
					map->direction = map->map[i][j];
				}
			j++;
		}
		i++;
	}
	if (!map->flag->p)
		return (write(2, "error::missing player\n", 23), 0);
	return (1);
}

int	pars_color(char *str, t_color *color)
{
	int	i;

	i = 0;
	if (check_coma(str) == -1)
		return (0);
	if (str[i] == 'C' || str[i] == 'F')
		i++;
	color->r = ft_atoi(str, &i);
	color->g = ft_atoi(str, &i);
	color->b = ft_atoi(str, &i);
	if (ft_atoi(str, &i) > 0)
		return (0);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		return (0);
	return (1);
}

int	is_valid(char c)
{
	return ( c == 'N' || c == 'W' || c == 'E' || c == 'S'
		|| c == '1' || c == '0');
}
