#include "cub3d.h"

void	walk_forward_backward(t_data *data, int keycode)
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;

	x = data->player.pos_x;
	y = data->player.pos_y;
	dir_x = data->player.dir_x;
	dir_y = data->player.dir_y;
	if (keycode == 13)
	{
		if (!(ft_strchr("12", data->map.tab[(int)y][(int)(x + dir_x * SPEED)])))
			data->player.pos_x += data->player.dir_x * SPEED;
		if (!(ft_strchr("12", data->map.tab[(int)(y + dir_y * SPEED)][(int)x])))
			data->player.pos_y += data->player.dir_y * SPEED;
	}
	if (keycode == 1)
	{
		if (!(ft_strchr("12", data->map.tab[(int)y][(int)(x - dir_x * SPEED)])))
			data->player.pos_x -= data->player.dir_x * SPEED;
		if (!(ft_strchr("12", data->map.tab[(int)(y - dir_y * SPEED)][(int)x])))
			data->player.pos_y -= data->player.dir_y * SPEED;
	}
}

void	walk_aside(t_data *data, int keycode)
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;

	x = data->player.pos_x;
	y = data->player.pos_y;
	dir_x = data->player.dir_x;
	dir_y = data->player.dir_y;
	if (keycode == 0)
	{
		if (!(ft_strchr("12", data->map.tab[(int)y][(int)(x + dir_y * SPEED)])))
			data->player.pos_x += data->player.dir_y * SPEED;
		if (!(ft_strchr("12", data->map.tab[(int)(y - dir_x * SPEED)][(int)x])))
			data->player.pos_y -= data->player.dir_x * SPEED;
	}
	if (keycode == 2)
	{
		if (!(ft_strchr("12", data->map.tab[(int)y][(int)(x - dir_y * SPEED)])))
			data->player.pos_x -= data->player.dir_y * SPEED;
		if (!(ft_strchr("12", data->map.tab[(int)(y + dir_x * SPEED)][(int)x])))
			data->player.pos_y += data->player.dir_x * SPEED;
	}
}

void	rotate(t_data *data, int keycode, double ol1, double ol2)
{
	if (keycode == 123)
	{
		ol1 = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-ANGLE)
			- data->player.dir_y * sin(-ANGLE);
		data->player.dir_y = data->player.dir_y * cos(-ANGLE)
			+ ol1 * sin(-ANGLE);
		ol2 = data->rays.plane_x;
		data->rays.plane_x = data->rays.plane_x * cos(-ANGLE)
			- data->rays.plane_y * sin(-ANGLE);
		data->rays.plane_y = data->rays.plane_y * cos(-ANGLE)
			+ ol2 * sin(-ANGLE);
	}
	if (keycode == 124)
	{
		ol1 = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(ANGLE)
			- data->player.dir_y * sin(ANGLE);
		data->player.dir_y = data->player.dir_y * cos(ANGLE) + ol1 * sin(ANGLE);
		ol2 = data->rays.plane_x;
		data->rays.plane_x = data->rays.plane_x * cos(ANGLE)
			- data->rays.plane_y * sin(ANGLE);
		data->rays.plane_y = data->rays.plane_y * cos(ANGLE) + ol2 * sin(ANGLE);
	}
}

int	keyboard(int keycode, t_data *data)
{
	double	ol1;
	double	ol2;

	ol1 = 0;
	ol2 = 0;
	if (keycode == 13 || keycode == 1)
		walk_forward_backward(data, keycode);
	if (keycode == 0 || keycode == 2)
		walk_aside(data, keycode);
	if (keycode == 123 || keycode == 124)
		rotate(data, keycode, ol1, ol2);
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->window.win);
		exit(0);
	}
	lodev(data);
	return (1);
}
