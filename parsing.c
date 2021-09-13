#include "cub3d.h"

void	get_resolution(char *line, int *i, t_win *win, t_data *data)
{
	int	x;
	int	y;
	int	c;
	int	d;

	if (win->x || win->y)
		check_error(11);
	(*i)++;
	skip_spaces(line, i, 0);
	x = ft_atoi(line, i);
	skip_spaces(line, i, 0);
	y = ft_atoi(line, i);
	if (x < 1 || y < 1 || line[*i])
		check_error(12);
	mlx_get_screen_size(&c, &d);
	if (!data->a.screenshot)
	{
		if (x > c)
			x = c;
		if (y > d)
			y = d;
	}
	win->x = x;
	win->y = y;
}

void	get_floor_ceiling(char *line, int *i, t_data *data)
{
	int		r;
	int		g;
	int		b;
	char	help;

	if ((line[*i] == 'F' && data->f != 0xFF000000) || (line[*i] == 'C'
				&& data->c != 0xFF000000))
		check_error(9);
	help = line[*i];
	(*i)++;
	skip_spaces(line, i, 0);
	r = ft_atoi(line, i);
	skip_spaces(line, i, 1);
	g = ft_atoi(line, i);
	skip_spaces(line, i, 1);
	b = ft_atoi(line, i);
	if (line[*i] || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		check_error(10);
	if (help == 'F')
		data->f = r << 16 | g << 8 | b;
	if (help == 'C')
		data->c = r << 16 | g << 8 | b;
}

void	get_texture(char *line, int *i, void **mlx, t_textinfo *text)
{
	int		j;
	int		len;
	char	*path;
	void	*new_img;

	if (text->addr)
		check_error(7);
	*i += 2;
	j = 0;
	skip_spaces(line, i, 0);
	len = ft_strlen(line + *i);
	path = (char *)malloc(len + 1);
	if (!path)
		check_error(6);
	while (j < len)
		path[j++] = line[(*i)++];
	path[j] = '\0';
	if (!(check_extension(path, ".xpm")))
		check_error(8);
	new_img = mlx_xpm_file_to_image(*mlx, path, &text->width, &text->height);
	if (!new_img)
		check_error(7);
	free(path);
	text->addr = (unsigned int *)mlx_get_data_addr(new_img, &text->bits,
			&text->size_line, &text->end);
}

char	**help_map(t_map *map, char *line)
{
	char	**tmp;

	map->start_map = 1;
	if (ft_strlen(line) > map->max_len)
		map->max_len = ft_strlen(line);
	tmp = (char **)malloc(sizeof(char *) * (map->count_lines + 2));
	if (!tmp)
		check_error(6);
	return (tmp);
}

void	get_map(char *line, t_map *map)
{
	char	**tmp;
	char	*str;
	int		j;
	int		i;

	tmp = help_map(map, line);
	i = -1;
	while (++i < map->count_lines)
		tmp[i] = map->tab[i];
	free(map->tab);
	str = (char *)malloc(sizeof(char *) * ft_strlen(line + 1));
	if (!str)
		check_error(6);
	j = -1;
	while (++j < ft_strlen(line))
		str[j] = line[j];
	str[j] = '\0';
	tmp[i] = str;
	str = NULL;
	tmp[i + 1] = NULL;
	map->tab = tmp;
	tmp = NULL;
	map->count_lines++;
}
