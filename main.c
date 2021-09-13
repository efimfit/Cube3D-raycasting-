#include "cub3d.h"

void	lodev(t_data *data)
{
	draw_floor(data);
	draw_walls(data);
	mlx_put_image_to_window(data->mlx, data->window.win, data->image.img, 0,
						 0);
}

void	start_mlx(t_data *data)
{
	data->image.img = mlx_new_image(data->mlx, data->window.x + 1,
			data->window.y);
	if (data->a.screenshot)
	{
		data->image.img = mlx_new_image(data->mlx, data->window.x,
				data->window.y);
		data->image.addr = (unsigned int *)mlx_get_data_addr(data->image.img,
				&data->image.bpp, &data->image.line_length, &data->image.end);
		draw_floor(data);
		draw_walls(data);
		create_bmp(data);
		exit(0);
	}
	data->image.addr = (unsigned int *)mlx_get_data_addr(data->image.img,
			&data->image.bpp, &data->image.line_length, &data->image.end);
	data->window.win = mlx_new_window(data->mlx, data->window.x + 1,
			data->window.y, "Cub3D");
	lodev(data);
	mlx_hook(data->window.win, 17, 1L << 0, &ft_closed, data);
	mlx_hook(data->window.win, 2, 1L << 0, &keyboard, data);
	mlx_loop(data->mlx);
}

void	check_after_reading(int bytes, int fd)
{
	if (bytes < 0)
		check_error(2);
	close(fd);
}

void	ft_parser(char *map, t_data data)
{
	char	*line;
	int		fd;
	int		bytes;

	data.mlx = mlx_init();
	fd = open(map, O_RDONLY);
	if (fd < 1)
		check_error(2);
	bytes = get_next_line(fd, &line);
	while (bytes > 0)
	{
		current_line(line, &data);
		free(line);
		bytes = get_next_line(fd, &line);
	}
	check_after_reading(bytes, fd);
	current_line(line, &data);
	free(line);
	final_check(&data);
	start_mlx(&data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.c = 0xFF000000;
	data.f = 0xFF000000;
	if (argc == 2 && check_extension(argv[1], ".cub"))
		ft_parser(argv[1], data);
	else if (argc == 3 && check_extension(argv[1], ".cub")
		&& !strcmp(argv[2], "--save"))
	{
		data.a.screenshot = 1;
		ft_parser(argv[1], data);
	}
	else
		check_error(1);
	return (0);
}
