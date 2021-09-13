#include "cub3d.h"

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (char *)data->image.addr + (y * data->image.line_length + x
			* (data->image.bpp / 8));
	*(unsigned int *)dst = color;
}
