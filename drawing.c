#include "cub3d.h"

void	walls_part_four(t_data *data, int side, int x, int line_hgt)
{
	double	texPos;

	data->a.draw_start = -line_hgt / 2 + data->window.y / 2;
	data->a.draw_end = line_hgt / 2 + data->window.y / 2;
	if (data->a.draw_start < 0)
		data->a.draw_start = 0;
	if (data->a.draw_end >= data->window.y)
		data->a.draw_end = data->window.y - 1;
	data->a.wallX = data->player.pos_x + data->a.perp * data->rays.dir_x;
	if (side == 0)
		data->a.wallX = data->player.pos_y + data->a.perp * data->rays.dir_y;
	data->a.wallX -= (int)data->a.wallX;
	if (side && data->rays.dir_y > 0)
		find_step(data, &data->texture.so, line_hgt, 1);
	if (side && data->rays.dir_y < 0)
		find_step(data, &data->texture.no, line_hgt, 0);
	if (!side && data->rays.dir_x > 0)
		find_step(data, &data->texture.ea, line_hgt, 0);
	if (!side && data->rays.dir_x < 0)
		find_step(data, &data->texture.we, line_hgt, 1);
	texPos = (data->a.draw_start - data->window.y / 2 + line_hgt / 2)
		* data->a.step;
	walls_part_five(data, texPos, side, x);
}

void	walls_part_three(t_data *data, int x, double deltaDistX,
						 double deltaDistY)
{
	int	side;
	int	hit;
	int	line_hgt;

	hit = 0;
	while (!hit)
	{
		if (data->a.sideDistX < data->a.sideDistY)
		{
			data->a.sideDistX += deltaDistX;
			data->a.mapX += data->a.stepX;
			side = 0;
		}
		else
		{
			data->a.sideDistY += deltaDistY;
			data->a.mapY += data->a.stepY;
			side = 1;
		}
		if (data->map.tab[data->a.mapY][data->a.mapX] == '1')
			hit = 1;
	}
	line_hgt = (int)(data->window.y / data->a.perp);
	walls_part_four(data, side, x, line_hgt);
}

void	walls_part_two(t_data *data, double deltaDistX, double deltaDistY,
					   int x)
{
	if (data->rays.dir_x < 0)
	{
		data->a.stepX = -1;
		data->a.sideDistX = (data->player.pos_x - data->a.mapX)
			* deltaDistX;
	}
	if (data->rays.dir_x > 0)
	{
		data->a.stepX = 1;
		data->a.sideDistX = (data->a.mapX + 1 - data->player.pos_x)
			* deltaDistX;
	}
	if (data->rays.dir_y < 0)
	{
		data->a.stepY = -1;
		data->a.sideDistY = (data->player.pos_y - data->a.mapY)
			* deltaDistY;
	}
	if (data->rays.dir_y > 0)
	{
		data->a.stepY = 1;
		data->a.sideDistY = (data->a.mapY + 1 - data->player.pos_y)
			* deltaDistY;
	}
	walls_part_three(data, x, deltaDistX, deltaDistY);
}

void	walls_part_one(t_data *data, int x)
{
	double	cameraX;
	double	v;
	double	deltaDistX;
	double	deltaDistY;

	cameraX = -(2 * x / (double)data->window.x - 1);
	data->rays.dir_x = data->player.dir_x + data->rays.plane_x * cameraX;
	data->rays.dir_y = data->player.dir_y + data->rays.plane_y * cameraX;
	data->a.mapX = (int)data->player.pos_x;
	data->a.mapY = (int)data->player.pos_y;
	v = hypot(data->rays.dir_x, data->rays.dir_y);
	if (!data->rays.dir_x)
		deltaDistX = 0;
	else
		deltaDistX = fabs(v / data->rays.dir_x);
	if (!data->rays.dir_x)
		deltaDistY = 0;
	else
		deltaDistY = fabs(v / data->rays.dir_y);
	walls_part_two(data, deltaDistX, deltaDistY, x);
}

void	draw_walls(t_data *data)
{
	int		x;
	double	*ZBuffer;

	x = 0;
	ZBuffer = malloc(sizeof(double) * data->window.x + 1);
	if (!ZBuffer)
		check_error(6);
	while (x <= data->window.x)
	{
		walls_part_one(data, x - 1);
		ZBuffer[x] = data->a.perp;
		x++;
	}
	draw_sprites(data, ZBuffer);
	free(ZBuffer);
}
