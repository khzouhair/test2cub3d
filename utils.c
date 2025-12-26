#include "cub3d.h"

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

void ft_type_move(t_input *input, t_xy *c)
{
    if (input->move_forward)
        ft_move_forward(c);
    if (input->move_backward)
        ft_move_backward(c);
    if (input->move_left)
        ft_move_left(c);
    if (input->move_right)
        ft_move_right(c);
}
