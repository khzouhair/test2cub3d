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

typedef struct s_xy{
    double	dx;
	double	dy;
	double	new_x;
	double	new_y;
} t_xy;

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

typedef struct s_player
{
	double x;
	double y;
	double angle;
	double dir_x;
	double dir_y;
}   t_player;

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

typedef struct s_data
{
	t_map       map;
	t_player    player;
}   t_data;

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
	t_data	data;   
	t_mlx	mlx;    
	t_ray	ray;    
	t_input	input;  
	t_wall  *wall;
}	t_cub3d;



void ft_move_forward(t_xy *c);
void ft_move_backward(t_xy *c);
void ft_move_left(t_xy *c);
void ft_move_right(t_xy *c);
void ft_type_move(t_input *input, t_xy *c);
void ft_cal_step_initial_side_distance(t_r *r, t_cub3d *cub3d);
void ft_init_r(t_r *r, t_cub3d *cub3d);
void ft_perform(t_r *r, t_cub3d *cub3d);
void ft_condition_side(t_r *r, t_cub3d *cub3d);
int 	init_mlx(t_mlx *mlx_data);
t_data 	init_data(t_mlx *mlx_data, t_map *map);
void dda(t_cub3d *cub3d);
int	key_analysis(int keycode, t_input *input);
void handle_rotation(t_player *player, t_input *input);
t_input	init_input(void);
t_img create_img(t_mlx *mlx_data);
void	clean_image(t_mlx *mlx_data);
void update_player_position(t_player *player, t_input *input, char **map);
void reset_input(t_input *input);
t_wall	*init_text(t_cub3d *cub3d);
void draw_textured_column(t_cub3d *cub3d, t_tex *tex,
                          int column, int y_top, int y_bottom, int *y, double wall_x);
int get_texture_color(t_tex *tex, int x, int y);
void	write_pixel(t_cub3d *cub3d, int x, int y, int color);
void vertical_line(t_cub3d *cub, t_ray *ray, int x, int draw_start, int draw_end, double wall_x);


#endif
