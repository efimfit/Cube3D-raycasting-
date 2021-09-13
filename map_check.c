#include "cub3d.h"

void	map_plus_spaces(t_map *map)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	while (map->tab[++i])
	{
		if (ft_strlen(map->tab[i]) < map->max_len)
		{
			j = -1;
			new = (char *)malloc(sizeof(char) * (map->max_len + 1));
			if (!new)
				check_error(6);
			while (++j < ft_strlen(map->tab[i]))
				new[j] = map->tab[i][j];
			while (j < map->max_len)
				new[j++] = ' ';
			new[j] = '\0';
			free(map->tab[i]);
			map->tab[i] = new;
			new = NULL;
		}
	}
}

void	check_map_2(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (++i < map->count_lines - 1)
	{
		j = 0;
		while (++j < map->max_len - 1)
		{
			if (ft_strchr("02NSWE", map->tab[i][j]))
			{
				if (map->tab[i - 1][j - 1] == 32 || map->tab[i - 1][j] == 32
					|| map->tab[i - 1][j + 1] == 32 || map->tab[i][j + 1] == 32
					|| map->tab[i + 1][j + 1] == 32 || map->tab[i + 1][j] == 32
					|| map->tab[i + 1][j - 1] == 32 || map->tab[i][j - 1] == 32)
					check_error(15);
			}
			if (map->tab[i][j] == '2')
				map->count_sprites++;
			if (ft_strchr("NSWE", map->tab[i][j]))
				map->count_players++;
		}
	}
}

void	check_map(t_map *map)
{
	int	i;
	int	j;

	if (map->count_lines < 3 || map->max_len < 3)
		check_error(13);
	map_plus_spaces(map);
	i = -1;
	while (++i < map->count_lines)
	{
		j = -1;
		while (++j < map->max_len)
		{
			if (!ft_strchr("012NSWE ", map->tab[i][j]))
				check_error(15);
			if ((!ft_strchr("1 ", map->tab[i][j]) && i == 0)
				|| (!ft_strchr("1 ", map->tab[i][j]) && i == map->count_lines
						- 1)
				|| (!ft_strchr("1 ", map->tab[i][j]) && j == 0)
				|| (!ft_strchr("1 ", map->tab[i][j]) && j == map->max_len - 1))
				check_error(15);
		}
	}
	check_map_2(map);
}

void	find_player_n_sprites(t_data *data)
{
	int	i;
	int	j;
	int	instance;

	i = 0;
	instance = 0;
	data->sprites = malloc(sizeof(t_spr) * data->map.count_sprites);
	if (!data->sprites)
		check_error(6);
	while (++i < data->map.count_lines - 1)
	{
		j = 0;
		while (++j < data->map.max_len - 1)
		{
			if (ft_strchr("NSWE", data->map.tab[i][j]))
				detect_direction(data, data->map.tab[i][j], i, j);
			if (data->map.tab[i][j] == '2')
				data->sprites[instance].y = (double)i + 0.500000000000001;
			if (data->map.tab[i][j] == '2')
				data->sprites[instance++].x = (double)j + 0.5000000000001;
		}
	}
}

void	final_check(t_data *data)
{
	check_map(&data->map);
	if (!data->texture.no.addr || !data->texture.so.addr
		|| !data->texture.we.addr || !data->texture.ea.addr
		|| !data->texture.s.addr)
		check_error(7);
	if (data->c == 0xFF000000 || data->f == 0xFF000000)
		check_error(10);
	if (data->map.count_players != 1)
		check_error(16);
	if (!data->window.x || !data->window.y)
		check_error(12);
	find_player_n_sprites(data);
}
