/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 02:19:06 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 02:50:58 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_c.h"

t_map	*init_map(void)
{
	t_map	*map;
	map = ft_alloc(sizeof(t_map), 1);
	map->x = 0;
	map->y = 0;
	map->map_h = 0;
	map->map_w = 0;
	map->final_f = 0;
	map->final_c = 0;
	map->f = ft_alloc(sizeof(t_color), 1);
	map->c = ft_alloc(sizeof(t_color), 1);
	map->flag = ft_alloc(sizeof(t_flag), 1);
	map->flag->no = 0;
	map->flag->so = 0;
	map->flag->we = 0;
	map->flag->ea = 0;
	map->flag->f = 0;
	map->flag->c = 0;
	map->flag->p = 0;
	map->direction = '\0';
	map->p_ea = NULL;
	map->p_no = NULL;
	map->p_so = NULL;
	map->p_we = NULL;
	map->map = NULL;
	return (map);
}

int	verify_map(char *name, int *i)
{
	char	*line;
	int		fd;

	if (ft_strcmp(name + (ft_strlen(name) - 4), ".cub"))
		return (write(2, "error::wrong name\n", 19),0);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (write(2, "error::failed opening the file\n", 32), 0);
	while((line = get_next_line(fd)))
	{
		(*i)++;
	}
	close (fd);
	return (1);
}

char	**check_map(char *name)
{
	int		fd;
	int		i;
	char	**lines;
	char	*line;

	i = 0;
	if (!verify_map(name, &i))
		return(NULL);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (write(2, "error::failed opening the file\n", 32), NULL);
	lines = ft_alloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	while((line = get_next_line(fd)))
	{
		lines[i] = line;
		i++; 
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}
