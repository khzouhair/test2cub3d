/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:29:02 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 03:22:28 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_c.h"

char	**fill_map(char **lines, int *i, int max)
{
	char	**map;
	int		j;
	int		k;

	k = *i;
	j = 0;
	while (lines[*i])
		(*i)++;
	map = ft_alloc(sizeof(char *) * ((*i) - k + 1), 1);
	*i = k;
	k = 0;
	while (lines[*i])
	{
		map[k] = ft_alloc(sizeof(char) * (max + 1), 1);
		j = 0;
		while (lines[*i][j] && lines[*i][j] != '\n')
		{
			map[k][j] = lines[*i][j];
			j++;
		}
		if ((lines[*i][j] == '\n' || !lines[*i][j]) && j < max)
		{
			while (j < max - 1)
			{
				map[k][j] = ' ';
				j++;
			}
		}
		if (lines[(*i) + 1])
			map[k][j++] = '\n';	
		map[k][j] = '\0';
		(*i)++;
		k++;
	}
	map[k] = NULL;
	return (map);
}

t_map	*fill_data(char	**lines,int j, t_map *map)
{
	char	*str;
	char	**img;
	int		i;
	
	i = 0;
	while (lines[i] && i < j)
	{
			str = ft_strtrim(lines[i], " \t");
			if (!ft_strcmp(str, "\n"))
			{
				i++;
				continue;
			}
			if (str && str[0] != '1' && str[0] != '0')
			{
				img = ft_split(str);
				if (!ft_strcmp(img[0], "NO"))
					map->p_no = ft_strdup(ft_join2(img));
				else if (!ft_strcmp(img[0], "SO"))
					map->p_so = ft_strdup(ft_join2(img));
				else if (!ft_strcmp(img[0], "WE"))
					map->p_we = ft_strdup(ft_join2(img));
				else if (!ft_strcmp(img[0], "EA"))
					map->p_ea = ft_strdup(ft_join2(img));
				else if (!ft_strcmp(img[0], "F"))
				{
					if (!pars_color(str, map->f))
						return (write(2, "error::wrong colors\n", 21), NULL);
					else
						map->final_f = ((map->f->r << 16) | (map->f->g << 8) | (map->f->b));
				}
				else if (!ft_strcmp(img[0], "C"))
				{
					if (!pars_color(str, map->c))
						return (write(2, "error::wrong colors\n", 21), NULL);
					else
						map->final_c = ((map->c->r << 16) | (map->c->g << 8) | (map->c->b));
				}
			}
			i++;
		}
	return (map);
}

t_map	*pars_map(char **lines, t_map *map)
{
	char	*str;
	int		max;
	char	**img;
	int		i;

	i = 0;
	while (lines[i])
	{
		str = ft_strtrim(lines[i], " \t");
		if (!ft_strcmp(str, "\n"))
		{
			i++;
			continue;
		}
		if (str && str[0] != '1' && str[0] != '0')
		{
			img = ft_split(str);
			if (!ft_strcmp(img[0], "NO"))
			map->flag->no++;
			else if (!ft_strcmp(img[0], "SO"))
			map->flag->so++;
			else if (!ft_strcmp(img[0], "WE"))
			map->flag->we++;
			else if (!ft_strcmp(img[0], "EA"))
			map->flag->ea++;
			else if (!ft_strcmp(img[0], "F"))
			map->flag->f++;
			else if (!ft_strcmp(img[0], "C"))
			map->flag->c++;
			else
			return (write(2, "error::wrong character\n", 24), NULL);
		}
		else if (str && (str[0] == '1' || str[0] == '0'))
		{
			max = find_max(lines + i);
			if (!fill_data(lines, i, map))
				return (ft_alloc(0, 0), NULL);
			if (!find_max(lines + i))
				return (ft_alloc(0, 0), NULL);
			if (!check_flag(map))
				return (ft_alloc(0, 0), NULL);
			map->map = fill_map(lines, &i, max);
			break;
		}
		i++;
	}
	return (map);
}

int	final_parsing(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (is_valid(map->map[i][j]) && map->map[i][j] != '1')
			{
				if (map->map[i] && map->map[i] && map->map[i + 1] && map->map[i - 1]
					&& is_valid(map->map[i][j - 1]) && is_valid(map->map[i][j + 1])
					&& is_valid(map->map[i + 1][j]) && is_valid(map->map[i - 1][j]))
					j++;
				else
					return (write(2, "error::invalid map\n", 20), 0);
			}
			else if (!is_valid(map->map[i][j]) && map->map[i][j] != ' ' && map->map[i][j] != '\t'
				&& map->map[i][j] != '\n')
				return (write(2, "error::invalid map\n", 20), 0);
			else
				j++;
		}
	}
	return (1);
}
