#include "cub3d.h"

void	paint(t_data *data, t_textinfo *texture, int texY, int x)
{
	unsigned int	color;

	texY = defense(texY, texture->height);
	color = texture->addr[texture->width * texY + data->a.texX];
	if (x == -1 && data->a.draw_start == 0)
		x = 0;
	my_mlx_pixel_put(data, x, data->a.draw_start, 0x000000);
	if (color != 0xFF000000)
		my_mlx_pixel_put(data, x, data->a.draw_start, color);
}

void	walls_part_five(t_data *data, double texPos, int side, int x)
{
	int	texY;

	if (side == 0)
		data->a.perp = (data->a.mapX - data->player.pos_x
				+ (1 - data->a.stepX) / 2) / data->rays.dir_x;
	else
		data->a.perp = (data->a.mapY - data->player.pos_y
				+ (1 - data->a.stepY) / 2) / data->rays.dir_y;
	while (data->a.draw_start < data->a.draw_end)
	{
		texY = (int)texPos;
		if (side && data->rays.dir_y > 0)
			paint(data, &data->texture.so, texY, x);
		if (side && data->rays.dir_y < 0)
			paint(data, &data->texture.no, texY, x);
		if (!side && data->rays.dir_x > 0)
			paint(data, &data->texture.ea, texY, x);
		if (!side && data->rays.dir_x < 0)
			paint(data, &data->texture.we, texY, x);
		texPos += data->a.step;
		data->a.draw_start++;
	}
}

void	find_step(t_data *data, t_textinfo *texture, int line_hgt, int flag)
{
	data->a.texX = (int)(data->a.wallX * texture->width);
	if (flag)
		data->a.texX = texture->width - data->a.texX - 1;
	data->a.texX = defense(data->a.texX, texture->width);
	data->a.step = (float) texture->width / line_hgt;
	if (texture->width > texture->height)
		data->a.step = (float)texture->width / line_hgt / ((float)
				texture->width / (float)texture->height);
	else if (texture->width < texture->height)
		data->a.step = (float)texture->height / line_hgt;
}
