/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_c.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:43:14 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 03:07:10 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_C_H
# define PARS_C_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_flag
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				f;
	int				c;
	int				p;
}	t_flag;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}	t_color;

typedef struct s_map
{
	int				x;
	int				y;
	int				final_c;
	int				final_f;
	char			direction;
	int				map_h;
	int				map_w;
	char			*p_no;
	char			*p_so;
	char			*p_we;
	char			*p_ea;
	t_flag			*flag;
	t_color			*f;
	t_color			*c;
	char			**map;
}	t_map;

typedef struct s_clean
{
	void			*ptr;
	struct s_clean	*next;
}	t_clean;

typedef struct s_tex
{
	void			*img;
	char			*addr;
	int				bpp;
	int				len;
	int				endian;
	int				height;
	int				width;
	int				flag;
}	t_tex;

///-------------parsing-------------///
//----->tools
size_t	ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strjoin2(char *s1, char *s2);
int		ft_atoi(char *str, int *i);

//------>free
void	ft_clear_list(t_clean **lst);
void	*ft_alloc(size_t size, int flag);
t_clean	*ft_creat_list(void *mem);
void	ft_add_front(t_clean **list, t_clean *to_add);

//----->get_next_line
char	*ft_join(char *dest, char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char *s);
char	*get_backup(int fd, char *backup);
char	*get_l(char *backup);
char	*update(char *backup);
char	*get_next_line(int fd);

//----->map
t_map	*init_map(void);
int		verify_map(char *name, int *i);
char	**check_map(char *name);
int		find_max(char **lines);
int		check_flag(t_map *map);
char	**fill_map(char **lines, int *i, int max);
t_map	*pars_map(char **lines, t_map *map);
int		is_valid(char c);
int		final_parsing(t_map *map);
int		find_player(t_map *map);
int		pars_color(char *str, t_color *color);
int		check_coma(char *str);
char	**ft_split(char *s);
int		count_str(char **str);
char	*ft_join2(char **str);

#endif