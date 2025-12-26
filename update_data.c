#include "cub3d.h"

typedef struct s_xy{
    double	dx;
	double	dy;
	double	new_x;
	double	new_y;
} t_xy;

int	key_analysis(int keycode, t_input *input)
{
	if (keycode == 119)
		input->move_forward = 1;
	else if (keycode == 100)
		input->move_left = 1;
	else if (keycode == 115)
		input->move_backward = 1;
	else if (keycode == 97)
		input->move_right = 1;
	else if (keycode == 65361)
		input->rotate_left = 1;
	else if (keycode == 65363)
		input->rotate_right = 1;
	else if (keycode == 65307)
		exit(0);
	return (0);
}

void handle_rotation(t_player *player, t_input *input)
{
    if (input->rotate_left)
        player->angle -= 0.3;
    if (input->rotate_right)
        player->angle += 0.3;
    if (player->angle < 0)
        player->angle += 2 * PI;
    else if (player->angle >= 2 * PI)
        player->angle -= 2 * PI;
}

static int is_walkable(char **map, double x, double y)
{
	int mx = x;
    int my = y;

    if (map[my][mx] == '1')
		return (0);
    return (1);
}

void ft_move_forward(t_xy *c)
{
    double speed;
    speed = 0.08;
    c->new_x += c->dx * speed;
    c->new_y += c->dy * speed;
}

void ft_move_backward(t_xy *c)
{
    double speed;
    speed = 0.08;
    c->new_x -= c->dx * speed;
    c->new_y -= c->dy * speed;
}

void ft_move_left(t_xy *c)
{
    double speed;
    speed = 0.08;
    c->new_x += -c->dy * speed;
    c->new_y += c->dx * speed;
}

void ft_move_right(t_xy *c)
{
    double speed;
    speed = 0.08;
    c->new_x += c->dy * speed;
    c->new_y += -c->dx * speed;
}

void ft_type_move(t_input *input, t_xy c)
{
    if (input->move_forward)
        ft_move_forward(&c);
    if (input->move_backward)
        ft_move_backward(&c);
    if (input->move_left)
        ft_move_left(&c);
    if (input->move_right)
        ft_move_right(&c);
}

void update_player_position(t_player *player, t_input *input, char **map)
{

	t_xy c;

	c.dx = cos(player->angle);
	c.dy = sin(player->angle);
	c.new_x = player->x;
	c.new_y = player->y;
    ft_type_move(input, c);
    if (is_walkable(map, c.new_x, player->y))
		player->x = c.new_x;
	if (is_walkable(map, player->x, c.new_y))
		player->y = c.new_y;
}

void reset_input(t_input *input)
{
    input->move_forward = 0;
    input->move_backward = 0;
    input->move_left = 0;
    input->move_right = 0;
    input->rotate_left = 0;
    input->rotate_right = 0;
}
