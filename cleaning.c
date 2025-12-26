#include "cub3d.h"


void	clean_image(t_mlx *mlx_data)
{
	int		bpp;
	int		line_length;
	int		endian;
	char	*addr;
	int		x;
	int		y;
	unsigned int color = 0x000000; // black

	addr = mlx_get_data_addr(mlx_data->img.img, &bpp, &line_length, &endian);
	for (y = 0; y < mlx_data->win_height; y++)
	{
		for (x = 0; x < mlx_data->win_width; x++)
		{
			char *pixel = addr + (y * line_length + x * (bpp / 8));
			*(unsigned int *)pixel = color;
		}
	}
}
