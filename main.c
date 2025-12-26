#include "cub3d.h"

void    put_pixel_to_img(t_img *img, int x, int y, int color)
{
    char    *pixel_offset;

    pixel_offset = img->addr + (y * img->line_len /*Offset to the beginning of the row (y-coordinate)
        */+ x * (img->bpp / 8)/*Offset to the specific pixel in that row (x-coordinate)*/);
    *(unsigned int *)pixel_offset = color;
}

void    img_building(t_img *img, int width, int height, int ceiling_color, int floor_color)
{
    int x;
	int y;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (y < height / 2)
            {
                put_pixel_to_img(img, x, y, ceiling_color);
            }
            else
            {
                put_pixel_to_img(img, x, y, floor_color);
            }
        }
    }
}

void drawing(t_cub3d *cub3d)/*there's something weird here*/
{
	handle_rotation(&cub3d->data.player, &cub3d->input);
	update_player_position(&cub3d->data.player, &cub3d->input, cub3d->data.map.map);
	clean_image(&cub3d->mlx);
    dda(cub3d);
    mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win, cub3d->mlx.img.img, 0, 0);
	reset_input(&cub3d->input);
}


void init_cub3d(t_cub3d *cub3d, t_map *map)
{
	/*initialize mlx*/
	if (init_mlx(&cub3d->mlx))
	{
		printf("Error initializing mlx\n");
	}
	/*initialize data*/
	cub3d->data = init_data(&cub3d->mlx, map);
	cub3d->wall = init_text(cub3d);
	if (!cub3d->wall)
	{
		ft_alloc(0, 0);
		exit(1);
	}
	// cub3d->data.textures = *init_text(cub3d);

	/*initialize input*/
	cub3d->input = init_input();
}

int main(int ac, char **av)
{
	t_cub3d cub3d;
	t_map	*map;
	char	**lines;

	if (ac < 2)
	{
		write(2, "error::few arguments\n", 22);
		exit(1);
	}
	lines = check_map(av[1]);
	if (!lines)
	{
		ft_alloc(0, 0);
		exit(1);
	}
	map = init_map();
	map = pars_map(lines, map);
	if (!map || !map->map || !final_parsing(map)|| !find_player(map))
	{
		ft_alloc(0, 0);
		exit(1);
	}
	init_cub3d(&cub3d, map);
	mlx_key_hook(cub3d.mlx.win, key_analysis, &cub3d.input);
	mlx_loop_hook(cub3d.mlx.mlx, drawing, &cub3d);
    mlx_loop(cub3d.mlx.mlx);
    return 0;
}
