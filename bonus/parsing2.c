#include "cub3d.h"

void	current_line2(char *line, int *i, t_data *data)
{
	if (line[*i] == 'R' && line[(*i) + 1] == ' ')
		get_resolution(line, i, &data->window, data);
	else if ((line[*i] == 'F' || line[*i] == 'C') && line[(*i) + 1] == ' ')
		get_floor_ceiling(line, i, data);
	else if (line[*i] == 'N' && line[(*i) + 1] == 'O' && line[(*i) + 2] == ' ')
		get_texture(line, i, &data->mlx, &data->texture.no);
	else if (line[*i] == 'S' && line[(*i) + 1] == 'O' && line[(*i) + 2] == ' ')
		get_texture(line, i, &data->mlx, &data->texture.so);
	else if (line[*i] == 'W' && line[(*i) + 1] == 'E' && line[(*i) + 2] == ' ')
		get_texture(line, i, &data->mlx, &data->texture.we);
	else if (line[*i] == 'E' && line[(*i) + 1] == 'A' && line[(*i) + 2] == ' ')
		get_texture(line, i, &data->mlx, &data->texture.ea);
	else if (line[*i] == 'S' && line[(*i) + 1] == ' ')
		get_texture(line, i, &data->mlx, &data->texture.s);
	else if (line[*i] == 'N' && line[(*i) + 1] == ' ')
		get_texture(line, i, &data->mlx, &data->texture.n);
	else if (line[*i] == 'G' && line[(*i) + 1] == ' ')
		get_texture(line, i, &data->mlx, &data->texture.g);
	else if (line[*i] == ' ')
	{
		skip_spaces(line, i, 0);
		if (line[*i] != '1')
			check_error(3);
	}
}

void	current_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	first_spaces(line, &i, data);
	if (data->map.start_map == 0)
	{
		current_line2(line, &i, data);
		if (line[i] != '1' && i == 0 && line[i] != '\0')
			check_error(5);
	}
	else
		skip_spaces(line, &i, 0);
	if (line[i] == '1')
		get_map(line, &data->map);
	else if (!line[i] && i != 0 && data->map.start_map)
		get_map(line, &data->map);
	else if (data->map.start_map)
		check_error(15);
}
