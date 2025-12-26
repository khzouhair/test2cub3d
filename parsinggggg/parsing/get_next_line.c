/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:17:15 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 02:50:17 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars_c.h"

char	*get_backup(int fd, char *backup)
{
	char	*buffer;
	int		l;

	buffer = ft_alloc((size_t)BUFFER_SIZE + 1, 1);
	l = 1;
	while (l > 0 && !ft_strchr(backup, '\n'))
	{
		l = read(fd, buffer, BUFFER_SIZE);
		if (l == -1)
		{
			return (NULL);
		}
		buffer[l] = '\0';
		backup = ft_strjoin(backup, buffer);
	}
	return (backup);
}

char	*get_l(char *backup)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	j = 0;
	if (!*backup)
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
		i++;
	rest = ft_alloc(sizeof(char) * i + 1, 1);
	if (!rest)
		return (NULL);
	while (j < i)
	{
		rest[j] = backup[j];
		j++;
	}
	rest[i] = '\0';
	return (rest);
}

char	*update(char *backup)
{
	int		i;
	int		j;
	char	*new_ba;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\0')
	{
		return (NULL);
	}
	i += (backup[i] == '\n');
	new_ba = ft_alloc(ft_strlen(backup) - i + 1, 1);
	j = 0;
	while (backup[i + j] != '\0')
	{
		new_ba[j] = backup[i + j];
		j++;
	}
	new_ba[j] = '\0';
	return (new_ba);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	backup = get_backup(fd, backup);
	if (!backup)
		return (backup = NULL, NULL);
	line = get_l(backup);
	if (!line)
		return (backup = NULL, NULL);
	backup = update(backup);
	return (line);
}
