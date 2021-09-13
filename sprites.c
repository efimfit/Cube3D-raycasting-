#include "cub3d.h"

void	ft_sortsprite(t_data *data, double *dist, int i)
{
	int			j;
	double		temp_dist;
	double		temp_y;
	double		temp_x;

	while (++i < data->map.count_sprites)
	{
		j = i;
		while (++j < data->map.count_sprites)
		{
			if ((dist)[i] < (dist)[j])
			{
				temp_dist = (dist)[j];
				temp_x = data->sprites[j].x;
				temp_y = data->sprites[j].y;
				(dist)[j] = (dist)[i];
				data->sprites[j].x = data->sprites[i].x;
				data->sprites[j].y = data->sprites[i].y;
				(dist)[i] = temp_dist;
				data->sprites[i].x = temp_x;
				data->sprites[i].y = temp_y;
			}
		}
	}
}

void	sprites_part_three(t_data *data, int stripe, int spriteScreenX,
						double *ZBuffer)
{
	int				texX;
	int				texY;
	int				y;
	int				d;
	unsigned int	color;

	texX = (int)(256 * (stripe - (-data->a.spriteWidth / 2 + spriteScreenX))
			* data->texture.s.width / data->a.spriteWidth) / 256;
	texX = defense(texX, data->texture.s.width);
	if (data->a.transformY > 0 && stripe < data->window.x
		&& data->a.transformY < ZBuffer[stripe])
	{
		y = data->a.drawStartY - 1;
		while (++y < data->a.drawEndY)
		{
			d = y * 256 - data->window.y * 128 + data->a.spriteHeight * 128;
			texY = (d * data->texture.s.height / data->a.spriteHeight) / 256;
			texY = defense(texY, data->texture.s.height);
			color = data->texture.s.addr[data->texture.s.width * texY + texX];
			if (color != 0xFF000000)
				my_mlx_pixel_put(data, stripe, y, color);
		}
	}
}

void	sprites_part_two(t_data *data, int spriteScreenX, double *ZBuffer)
{
	int	drawStartX;
	int	drawEndX;
	int	stripe;

	if (data->a.drawEndY > data->window.y)
		data->a.drawEndY = data->window.y;
	data->a.spriteWidth = abs((int)(data->window.x / data->a.transformY));
	drawStartX = -data->a.spriteWidth / 2 + spriteScreenX;
	if (drawStartX < 0)
		drawStartX = 0;
	drawEndX = data->a.spriteWidth / 2 + spriteScreenX;
	if (drawEndX > data->window.x)
		drawEndX = data->window.x;
	stripe = drawStartX;
	while (stripe < drawEndX)
	{
		sprites_part_three(data, stripe, spriteScreenX, ZBuffer);
		stripe++;
	}
}

void	sprites_part_one(t_data *data, double *ZBuffer, int i)
{
	double	spriteX;
	double	spriteY;
	double	invDet;
	int		spriteScreenX;

	spriteX = data->sprites[i].x - data->player.pos_x;
	spriteY = data->sprites[i].y - data->player.pos_y;
	invDet = 1.0 / (data->rays.plane_x * data->player.dir_y - data->player
			.dir_x * data->rays.plane_y);
	data->a.transformX = invDet * (data->player.dir_y * spriteX
			- data->player.dir_x * spriteY);
	data->a.transformY = invDet * (-data->rays.plane_y * spriteX
			+ data->rays.plane_x * spriteY);
	spriteScreenX = (int)(data->window.x / 2 * (1 - data->a.transformX
				/ data->a.transformY));
	data->a.spriteHeight = abs((int)(data->window.y / data->a.transformY));
	data->a.drawStartY = -data->a.spriteHeight / 2 + data->window.y / 2;
	if (data->a.drawStartY < 0)
		data->a.drawStartY = 0;
	data->a.drawEndY = data->a.spriteHeight / 2 + data->window.y / 2;
	sprites_part_two(data, spriteScreenX, ZBuffer);
}

void	draw_sprites(t_data *data, double *ZBuffer)
{
	int		i;
	double	*spriteDist;

	i = -1;
	spriteDist = malloc(sizeof(double) * data->map.count_sprites);
	if (!spriteDist)
		check_error(6);
	while (++i < data->map.count_sprites)
	{
		spriteDist[i] = ((data->player.pos_x - data->sprites[i].x)
				* (data->player.pos_x - data->sprites[i].x)
				+ (data->player.pos_y - data->sprites[i].y)
				* (data->player.pos_y - data->sprites[i].y));
	}
	ft_sortsprite(data, spriteDist, -1);
	i = -1;
	while (++i < data->map.count_sprites)
		sprites_part_one(data, ZBuffer, i);
	free(spriteDist);
}
