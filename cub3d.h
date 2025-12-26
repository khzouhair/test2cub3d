# ifndef CUB3D_H
# define CUB3D_H
#include "mlx/mlx.h"
#include "parsinggggg/pars_c.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/types.h>
#define ROT_SPEED 0.01
#define PI 3.14159
/*
	you should think of this file as a four part header...
	one for map, player, textures and colors...
	one for mlx(i'm also using textures here)...
	one for raycasting...
	and functions declarations
	input struct
*/






















/*
		map
		textures
		floor and ceiling colors
		player variables
*/

typedef struct s_player
{
	double x;
	double y;
	double angle;
	double dir_x;
	double dir_y;
}   t_player;

// typedef struct s_map
// {
//     char    **grid;
//     int     width;
//     int     height;
// }   t_map;


typedef struct s_textures
{
	int     width;
	int     height;
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}   t_textures;

// typedef struct s_colors
// {
// 	int floor;
//     int ceiling;
// }   t_colors;


typedef struct s_data
{
	t_map       map;
	// t_textures		textures;
	// t_colors    colors;
	t_player    player;
}   t_data;


/*mlx:*/
typedef struct s_img
{
	void    *img;
	char    *addr;
	int     bpp;
	int     line_len;
	int     endian;
}   t_img;

typedef struct s_mlx
{
    void        *mlx;
    void        *win;
    int         win_width;
    int         win_height;
	t_img     	img;
}   t_mlx;

typedef struct s_wall
{
	t_tex    *north;
    t_tex    *south;
    t_tex    *east;
    t_tex    *west;
} t_wall;

/*ray_casting struct*/
typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
}   t_ray;

























/*input*/
typedef struct s_input
{
	int move_forward;
	int move_backward;
	int move_left;
	int move_right;
	int rotate_left;
	int rotate_right;
}	t_input;





typedef struct s_cub3d
{
	t_data	data;   // map, textures, colors, player
	t_mlx	mlx;    // mlx-related stuff
	t_ray	ray;    // raycasting data
	t_input	input;  // user input
	t_wall  *wall;
}	t_cub3d;

/*functions:*/
int 	init_mlx(t_mlx *mlx_data);
t_data 	init_data(t_mlx *mlx_data, t_map *map);
// void 	dda(t_mlx *mlx_data, t_data *data, t_img middle_img_buffer);
void dda(t_cub3d *cub3d);
// void vertical_line(t_img img, int x, int draw_start, int draw_end, int wall_color, int ceiling_color, int floor_color);
// void vertical_line(t_cub3d *cub, int x, int draw_start, int draw_end, double wall_x);

int	key_analysis(int keycode, t_input *input);
void handle_rotation(t_player *player, t_input *input);
t_input	init_input(void);
t_img create_img(t_mlx *mlx_data);
void	clean_image(t_mlx *mlx_data);
void update_player_position(t_player *player, t_input *input, char **map);
void reset_input(t_input *input);

//-------------->textures
t_wall	*init_text(t_cub3d *cub3d);
void draw_textured_column(t_cub3d *cub3d, t_tex *tex,
                          int column, int y_top, int y_bottom, int *y, double wall_x);
int get_texture_color(t_tex *tex, int x, int y);
void	write_pixel(t_cub3d *cub3d, int x, int y, int color);
void vertical_line(t_cub3d *cub, t_ray *ray, int x, int draw_start, int draw_end, double wall_x);
// void vertical_line(t_cub3d *cub, int x, int draw_start, int draw_end,
//                    double wall_x, t_ray *ray);
#endif