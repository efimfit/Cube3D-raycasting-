#include "cub3d.h"

int	check_extension(char *str, char *ideal)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i >= 5 && str[i - 1] == ideal[3] && str[i - 2] == ideal[2]
		&& str[i - 3] == ideal[1] && str[i - 4] == ideal[0])
		return (1);
	return (0);
}

void	detect_direction(t_data *data, char c, int i, int j)
{
	if (c == 'N')
	{
		data->player.dir_y = -1;
		data->rays.plane_x = -0.66;
	}
	if (c == 'S')
	{
		data->player.dir_y = 1;
		data->rays.plane_x = 0.66;
	}
	if (c == 'W')
	{
		data->player.dir_x = -1;
		data->rays.plane_y = 0.66;
	}
	if (c == 'E')
	{
		data->player.dir_x = 1;
		data->rays.plane_y = -0.66;
	}
	data->player.pos_x = (double)j + 0.5;
	data->player.pos_y = (double)i + 0.5;
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*b;
	size_t			i;

	i = 0;
	b = (unsigned char *)s;
	while (i < n)
	{
		b[i] = '\0';
		i++;
	}
}

void	music_off(int non_usable)
{
	(void)non_usable;
	system("killall afplay");
	exit(0);
}

int	ft_closed(t_data *data, int a)
{
	if (a == 1)
		mlx_destroy_window(data->mlx, data->window.win);
	system("killall afplay");
	exit(0);
	return (1);
}
