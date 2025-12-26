#include "cub3d.h"

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
