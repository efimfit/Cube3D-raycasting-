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

void	draw_floor(t_data *data)
{
	int				y;
	int				x;
	unsigned int	color;

	y = data->window.y / 2;
	while (++y < data->window.y)
	{
		init_floor(data, y);
		x = -1;
		while (++x < data->window.x)
		{
			color = data->f;
			my_mlx_pixel_put(data, x, y, color);
			color = data->c;
			my_mlx_pixel_put(data, x, data->window.y - y - 1, color);
		}
	}
}
