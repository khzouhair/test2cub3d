#include "cub3d.h"
#include <math.h>

typedef struct s_r{
	double camera_step;
	double start_angle;
	int x;
	t_ray ray;
	t_tex *current_tex;
	double ray_angle;
	int map_x;
	int map_y;
	double wall_x;
	int line_height;
	int draw_start;
	int draw_end;
} t_r;


void ft_cal_step_initial_side_distance(t_r *r, t_cub3d *cub3d)
{
	if (r->ray.dir_x < 0)
		{
			r->ray.step_x = -1;
			r->ray.side_dist_x = (cub3d->data.player.x - r->map_x) * r->ray.delta_dist_x;
		}
		else
		{
			r->ray.step_x = 1;
			r->ray.side_dist_x = (r->map_x + 1.0 - cub3d->data.player.x) * r->ray.delta_dist_x;
		}
		
		if (r->ray.dir_y < 0)
		{
			r->ray.step_y = -1;
			r->ray.side_dist_y = (cub3d->data.player.y - r->map_y) * r->ray.delta_dist_y;
		}
		else
		{
			r->ray.step_y = 1;
			r->ray.side_dist_y = (r->map_y + 1.0 - cub3d->data.player.y) * r->ray.delta_dist_y;
		}
}

void ft_init_r(t_r *r, t_cub3d *cub3d)
{
		r->ray_angle = r->start_angle + r->x * r->camera_step;
		r->ray.dir_x = cos(r->ray_angle);
		r->ray.dir_y = sin(r->ray_angle);
		r->map_x = (int)cub3d->data.player.x;
		r->map_y = (int)cub3d->data.player.y;
		r->ray.delta_dist_x = fabs(1 / r->ray.dir_x);
		r->ray.delta_dist_y = fabs(1 / r->ray.dir_y);
}

void ft_perform(t_r *r, t_cub3d *cub3d)
{
	while (r->ray.hit == 0)
		{
			if (r->ray.side_dist_x < r->ray.side_dist_y)
			{
				r->ray.side_dist_x += r->ray.delta_dist_x;
				r->map_x += r->ray.step_x;
				r->ray.side = 0;
			}
			else
			{
				r->ray.side_dist_y += r->ray.delta_dist_y;
				r->map_y += r->ray.step_y;
				r->ray.side = 1;
			}
			/*here*/
			if (cub3d->data.map.map[r->map_y][r->map_x] == '1')
				r->ray.hit = 1;
		}
}

void ft_condition_side(t_r *r, t_cub3d *cub3d)
{
	if (r->ray.side == 0)
        r->ray.perp_wall_dist = (r->map_x - cub3d->data.player.x + (1 - r->ray.step_x) / 2.0) / r->ray.dir_x;
    else
        r->ray.perp_wall_dist = (r->map_y - cub3d->data.player.y + (1 - r->ray.step_y) / 2.0) / r->ray.dir_y;

}

void dda(t_cub3d *cub3d)
{
	t_r r;

	r.camera_step = (double)1.074 / (double)cub3d->mlx.win_width;
	r.start_angle = cub3d->data.player.angle - (1.074 / 2);
	r.x = -1;
	while (++r.x < cub3d->mlx.win_width)
	{
		ft_init_r(&r, cub3d);
		ft_cal_step_initial_side_distance(&r, cub3d);
		r.ray.hit = 0;
		ft_peform(&r, cub3d);
    ft_condition_side(&r, cub3d);
    r.ray.perp_wall_dist *= cos(cub3d->data.player.angle - r.ray_angle);
    if (r.ray.side == 0)
        r.wall_x = cub3d->data.player.y + r.ray.perp_wall_dist * r.ray.dir_y;
    else
        r.wall_x = cub3d->data.player.x + r.ray.perp_wall_dist * r.ray.dir_x;
    r.wall_x -= floor(r.wall_x);
    r.line_height = (int)(cub3d->mlx.win_height / r.ray.perp_wall_dist);
    r.draw_start = cub3d->mlx.win_height / 2 - (r.line_height / 2);
    r.draw_end   = cub3d->mlx.win_height / 2 + (r.line_height / 2);
    vertical_line(cub3d, &r.ray, r.x, r.draw_start, r.draw_end, r.wall_x);
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
