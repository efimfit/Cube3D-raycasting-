#include "cub3d.h"

void	check_error2(int n)
{
	if (n == 10)
		write(1, "wrong colours\n", 14);
	if (n == 11)
		write(1, "resolution already exists\n", 26);
	if (n == 12)
		write(1, "wrong resolution\n", 17);
	if (n == 13)
		write(1, "there isn't map or it's too small\n", 34);
	if (n == 14)
		write(1, "bad empty lines\n", 16);
	if (n == 15)
		write(1, "problems with the map\n", 22);
	if (n == 16)
		write(1, "there isn't one player\n", 23);
	exit(1);
}

void	check_error(int n)
{
	write(2, "Error\n", 6);
	if (n == 1)
		write(1, "invalid arguments while starting\n", 33);
	if (n == 2)
		write(1, "can't open file\n", 16);
	if (n == 3)
		write(1, "bad spaces\n", 11);
	if (n == 4)
		write(1, "map isn't the last\n", 19);
	if (n == 5)
		write(1, "invalid data\n", 13);
	if (n == 6)
		write(1, "fu**ing malloc\n", 15);
	if (n == 7)
		write(1, "problems with textures\n", 23);
	if (n == 8)
		write(1, "wrong texture extension\n", 24);
	if (n == 9)
		write(1, "colours already exist\n", 22);
	if (n > 9)
		check_error2(n);
	exit(1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long int	ft_atoi(char *nptr, int *i)
{
	int			sign;
	long int	pow;
	int			flag;

	flag = 0;
	sign = 1;
	if (nptr[*i] == '-')
		sign = -1;
	if (nptr[*i] == '-' || nptr[*i] == '+')
		(*i)++;
	if (nptr[*i] >= '0' && nptr[*i] <= '9')
		pow = 0;
	else
		return (-1);
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		pow = pow * 10 + (nptr[(*i)++] - '0');
		if (pow > 2147483647)
			flag = 1;
	}
	if (flag)
		return (2560 * sign);
	return (pow * sign);
}

void	first_spaces(char *line, int *i, t_data *data)
{
	if (data->first_line == 0)
	{
		if (line[*i] == '\0')
			check_error(14);
		data->first_line = 1;
	}
}
