/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieddaoud <ieddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 04:13:42 by ieddaoud          #+#    #+#             */
/*   Updated: 2025/12/06 02:47:04 by ieddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_wall  *init_text(t_cub3d *cub3d)
{
    t_wall *wall;

    if (!cub3d->data.map.p_no || !cub3d->data.map.p_so ||
		!cub3d->data.map.p_we || !cub3d->data.map.p_ea)
    {
            write(2, "Error: texture path missing\n", 30);
            return (NULL);
	}
    wall = ft_alloc(sizeof(t_wall), 1); 
    wall->north = ft_alloc(sizeof(t_tex), 1);
    wall->east = ft_alloc(sizeof(t_tex), 1);
    wall->west = ft_alloc(sizeof(t_tex), 1);
    wall->south = ft_alloc(sizeof(t_tex), 1);
    wall->north->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, cub3d->data.map.p_no, &(wall->north->width), &(wall->north->height));
    wall->east->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, cub3d->data.map.p_ea, &(wall->east->width), &(wall->east->height));
    wall->south->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, cub3d->data.map.p_so, &(wall->south->width), &(wall->south->height));
    wall->west->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, cub3d->data.map.p_we, &(wall->west->width), &(wall->west->height));
	if (!wall->north->img || !wall->east->img || !wall->south->img || !wall->west->img)
    {
        write(2, "Error:: failed loading the image\n", 34);
        return (NULL);
    }
	wall->north->addr = mlx_get_data_addr(wall->north->img, &wall->north->bpp, &wall->north->len, &wall->north->endian);
    wall->east->addr = mlx_get_data_addr(wall->east->img, &wall->east->bpp, &wall->east->len, &wall->east->endian);
    wall->south->addr = mlx_get_data_addr(wall->south->img, &wall->south->bpp, &wall->south->len, &wall->south->endian);
    wall->west->addr = mlx_get_data_addr(wall->west->img, &wall->west->bpp, &wall->west->len, &wall->west->endian);
	if (!wall->north->addr || !wall->east->addr || !wall->south->addr || !wall->west->addr)
        return (NULL);
    return (wall);
}

void	write_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;
    
	dst = cub3d->mlx.img.addr + (y * cub3d->mlx.img.line_len + x * (cub3d->mlx.img.bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_textured_column(t_cub3d *cub3d, t_tex *tex,
    int column, int y_top, int y_bottom, int *y, double wall_x)
{
    if (!tex)
    {
        write(2, "ERROR: draw_textured_column: tex is NULL\n", 42);
        return;
    }
    if (tex->width <= 0 || tex->height <= 0)
    {
        write(2, "ERROR: invalid texture dimensions\n", 35);
        return;
    }
    int tex_x = (int)(wall_x * tex->width);
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex->width) tex_x = tex->width - 1;
    while ((*y) <= y_bottom)
    {
        double tex_y_ratio = (float)((*y) - y_top) / (y_bottom - y_top);
        int tex_y = (int)(tex->height * tex_y_ratio);
        
        int color = get_texture_color(tex, tex_x, tex_y);
        write_pixel(cub3d, column, *y, color);
        (*y)++;
    }
}

int get_texture_color(t_tex *tex, int x, int y)
{
	char	*dst;

    if (!tex || !tex->addr)
    {
        fprintf(stderr, "Error: texture not loaded\n");
        return 0;
    }
    if (x < 0)
		x = 0;
    if (y < 0)
		y = 0;
    if (x >= tex->width)
		x = tex->width - 1;
    if (y >= tex->height)
		y = tex->height - 1;
    dst = tex->addr + (y * tex->len + x * (tex->bpp / 8));
    return *(unsigned int *)dst;
}
