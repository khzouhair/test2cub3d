#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"
#include <stddef.h>

#define PI 3.14159265358979323846

int rgb_to_int(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

t_data init_data(t_mlx *mlx_data, t_map *map)
{
    t_data data;

    data.map = *map;
	data.player.x = map->x + 0.5;
	data.player.y = map->y + 0.5;
	data.player.angle = 3.0f * PI / 2.0f;///function jdida
	return (data);
}
