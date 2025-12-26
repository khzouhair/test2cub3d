#include "cub3d.h"
#include <math.h>

void dda(t_cub3d *cub3d)
{
	double camera_step;
	double start_angle;
	t_ray ray;
	t_tex *current_tex;
	camera_step = (double)1.074 / (double)cub3d->mlx.win_width;
	start_angle = cub3d->data.player.angle - (1.074 / 2);

	int x = -1;
	while (++x < cub3d->mlx.win_width)
	{
		double ray_angle = start_angle + x * camera_step;
		
		ray.dir_x = cos(ray_angle);
		ray.dir_y = sin(ray_angle);
		
		int map_x = (int)cub3d->data.player.x;
		int map_y = (int)cub3d->data.player.y;
		
		ray.delta_dist_x = fabs(1 / ray.dir_x);
		ray.delta_dist_y = fabs(1 / ray.dir_y);
		
		// Calculate step and initial side distances
		if (ray.dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_dist_x = (cub3d->data.player.x - map_x) * ray.delta_dist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist_x = (map_x + 1.0 - cub3d->data.player.x) * ray.delta_dist_x;
		}
		
		if (ray.dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_dist_y = (cub3d->data.player.y - map_y) * ray.delta_dist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist_y = (map_y + 1.0 - cub3d->data.player.y) * ray.delta_dist_y;
		}
		
		// Perform DDA
		ray.hit = 0;
		while (ray.hit == 0)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				map_y += ray.step_y;
				ray.side = 1;
			}
			/*here*/
			if (cub3d->data.map.map[map_y][map_x] == '1')
				ray.hit = 1;
		}
		/* after you determine ray.side, map_x, map_y and set ray.hit = 1 */
			/* inside dda loop, after DDA found map_x,map_y and ray.side & ray.step_x/step_y */
    if (ray.side == 0)
        ray.perp_wall_dist = (map_x - cub3d->data.player.x + (1 - ray.step_x) / 2.0) / ray.dir_x;
    else
        ray.perp_wall_dist = (map_y - cub3d->data.player.y + (1 - ray.step_y) / 2.0) / ray.dir_y;

	// printf("perp:%f\n", ray.perp_wall_dist);
    ray.perp_wall_dist *= cos(cub3d->data.player.angle - ray_angle);
    double wall_x;
    if (ray.side == 0)
        wall_x = cub3d->data.player.y + ray.perp_wall_dist * ray.dir_y;
    else
        wall_x = cub3d->data.player.x + ray.perp_wall_dist * ray.dir_x;
    wall_x -= floor(wall_x);
    int line_height = (int)(cub3d->mlx.win_height / ray.perp_wall_dist);
    int draw_start = cub3d->mlx.win_height / 2 - (line_height / 2);
    int draw_end   = cub3d->mlx.win_height / 2 + (line_height / 2);
    vertical_line(cub3d, &ray, x, draw_start, draw_end, wall_x);
	}
}

void	vertical_line(t_cub3d *cub, t_ray *ray, int x, int draw_start,
			int draw_end, double wall_x)
{
	int		y;
	t_tex	*current_tex;
	int		line_height;
	int		tex_x;
	float	step;
	float	tex_pos;
	int		tex_y;
	int		color;

	if (ray->side == 0)
	{
        if (ray->step_x == 1)
		current_tex = cub->wall->east;  
        else
			current_tex = cub->wall->west;
    }
	else
	{
        if (ray->step_y == 1)
			current_tex = cub->wall->south;  
        else
			current_tex = cub->wall->north;
    }
	line_height = draw_end - draw_start + 1;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= cub->mlx.win_height)
		draw_end = cub->mlx.win_height - 1;
	y = 0;
	while (y < draw_start)
		write_pixel(cub, x, y++, cub->data.map.final_c);
	tex_x = (int)(wall_x * current_tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= current_tex->width)
		tex_x = current_tex->width - 1;
	step = (float)current_tex->height / (float)line_height;
	tex_pos = (draw_start - (cub->mlx.win_height / 2 - line_height / 2)) * step;
	if (tex_pos < 0)
		tex_pos = 0;
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= current_tex->height)
			tex_y = current_tex->height - 1;
		color = get_texture_color(current_tex, tex_x, tex_y);
		write_pixel(cub, x, y, color);
		tex_pos += step;
		y++;
	}
	y = draw_end + 1;
	while (y < cub->mlx.win_height)
		write_pixel(cub, x, y++, cub->data.map.final_f);
}
