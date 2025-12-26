#include "cub3d.h"

int init_mlx(t_mlx *mlx_data)
{
    mlx_data->mlx = mlx_init();
    if (!mlx_data->mlx)
    {
        printf("Failed to initialize MiniLibX\n");
        return (1);
    }
    mlx_data->win_width = 800;
    mlx_data->win_height = 600;
    mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->win_width, mlx_data->win_height, "Cub3D World");
    if (!mlx_data->win)
    {
        printf("Failed to create window\n");
        return (1);
    }
	mlx_data->img = create_img(mlx_data);
    return (0); 
}


t_input	init_input(void)
{
    t_input	input;

    input.move_forward = 0;
    input.move_backward = 0;
    input.move_left = 0;
    input.move_right = 0;
    input.rotate_left = 0;
    input.rotate_right = 0;
    return (input);
}

t_img create_img(t_mlx *mlx_data)
{
    t_img img;
    
    img.img = mlx_new_image(mlx_data->mlx, mlx_data->win_width, mlx_data->win_height);
    if (!img.img)
    {
        perror("mlx_new_image failed");
        exit(EXIT_FAILURE);
    }
    img.addr = mlx_get_data_addr(
        img.img,
        &img.bpp,
        &img.line_len,
        &img.endian
    );
    return img;
}
