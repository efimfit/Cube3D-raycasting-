#include "cub3d.h"

void	init_floor(t_data *data, int y)
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	float	rowDistance;

	rayDirX0 = data->player.dir_x + data->rays.plane_x;
	rayDirY0 = data->player.dir_y + data->rays.plane_y;
	rayDirX1 = data->player.dir_x - data->rays.plane_x;
	rayDirY1 = data->player.dir_y - data->rays.plane_y;
	rowDistance = (data->window.y / 2.0) / (y - data->window.y / 2.0);
	data->a.floor_stepX = rowDistance * (rayDirX1 - rayDirX0) / data->window.x;
	data->a.floor_stepY = rowDistance * (rayDirY1 - rayDirY0) / data->window.x;
	data->a.floorX = data->player.pos_x + rowDistance * rayDirX0;
	data->a.floorY = data->player.pos_y + rowDistance * rayDirY0;
}

int	draw_floor2(t_data *data, int width_height, int flag)
{
	int	t;

	if (flag)
		t = (int)(width_height * (data->a.floorX - (int) data->a.floorX));
	if (!flag)
		t = (int)(width_height * (data->a.floorY - (int)data->a.floorY));
	t = defense(t, width_height);
	return (t);
}

void	draw_floor(t_data *data)
{
	int				y;
	int				x;
	int				tx;
	int				ty;
	unsigned int	color;

	y = data->window.y / 2;
	while (++y < data->window.y)
	{
		init_floor(data, y);
		x = -1;
		while (++x < data->window.x)
		{
			tx = draw_floor2(data, data->texture.n.width, 0);
			ty = draw_floor2(data, data->texture.n.height, 1);
			data->a.floorX += data->a.floor_stepX;
			data->a.floorY += data->a.floor_stepY;
			color = data->texture.n.addr[data->texture.n.width * ty + tx];
			my_mlx_pixel_put(data, x, y, color);
			tx = draw_floor2(data, data->texture.g.width, 0);
			ty = draw_floor2(data, data->texture.g.height, 1);
			color = data->texture.g.addr[data->texture.g.width * ty + tx];
			my_mlx_pixel_put(data, x, data->window.y - y - 1, color);
		}
	}
}
