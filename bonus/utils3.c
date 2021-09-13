#include "cub3d.h"

int	defense(int X_or_Y, int texture)
{
	if (X_or_Y < 0)
		X_or_Y = 0;
	if (X_or_Y >= texture)
		X_or_Y = texture - 1;
	return (X_or_Y);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (char *)data->image.addr + (y * data->image.line_length + x
			* (data->image.bpp / 8));
	*(unsigned int *)dst = color;
}

void	skip_spaces(char *line, int *i, int zpt)
{
	if (zpt == 0)
	{
		while (line[*i] == ' ')
			(*i)++;
	}
	if (zpt == 1)
	{
		if (line[*i] == ',')
			(*i)++;
	}
}
