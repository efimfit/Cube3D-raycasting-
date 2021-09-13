#include "cub3d.h"

void	fill_header1(t_data *data, int fd)
{
	unsigned char	header1[40];
	int				n;

	n = -1;
	while (++n < 40)
		header1[n] = (unsigned char)(0);
	header1[0] = (unsigned char)(40);
	n = data->window.x;
	header1[4] = (unsigned char)(n % 256);
	header1[5] = (unsigned char)(n / 256 % 256);
	header1[6] = (unsigned char)(n / 256 / 256 % 256);
	header1[7] = (unsigned char)(n / 256 / 256 / 256);
	n = data->window.y;
	header1[8] = (unsigned char)(n % 256);
	header1[9] = (unsigned char)(n / 256 % 256);
	header1[10] = (unsigned char)(n / 256 / 256 % 256);
	header1[11] = (unsigned char)(n / 256 / 256 / 256);
	header1[12] = (unsigned char)(1);
	header1[14] = (unsigned char)(32);
	write(fd, header1, 40);
}

void	draw_screen(t_data *data, int fd)
{
	int				i;
	int				j;
	unsigned char	buffer[4];

	i = data->window.x * (data->window.y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < data->window.x)
		{
			buffer[0] = (unsigned char)(data->image.addr[i] % 256);
			buffer[1] = (unsigned char)(data->image.addr[i] / 256 % 256);
			buffer[2] = (unsigned char)(data->image.addr[i] / 256 / 256 % 256);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			i++;
			j++;
		}
		i -= 2 * data->window.x;
	}
}

void	create_bmp(t_data *data)
{
	int				fd;
	int				n;
	unsigned char	header[14];

	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd < 1)
		check_error(2);
	n = 1;
	while (++n < 14)
		header[n] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	n = data->window.x * data->window.y * 4 + 54;
	header[2] = (unsigned char)(n % 256);
	header[3] = (unsigned char)(n / 256 % 256);
	header[4] = (unsigned char)(n / 256 / 256 % 256);
	header[5] = (unsigned char)(n / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
	fill_header1(data, fd);
	draw_screen(data, fd);
	close(fd);
}
