#ifndef CUB3D_H
# define CUB3D_H
# include "./mlxopengl/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>

# define ANGLE 0.15
# define SPEED 0.2

typedef struct s_win
{
	void	*win;
	int		x;
	int		y;
}			t_win;

typedef struct s_img
{
	void			*img;
	unsigned int	*addr;
	int				bpp;
	int				line_length;
	int				end;
}					t_img;

typedef struct s_map
{
	char	**tab;
	int		start_map;
	int		max_len;
	int		count_lines;
	int		count_sprites;
	int		count_players;
}			t_map;

typedef struct s_textinfo
{
	unsigned int	*addr;
	int				width;
	int				height;
	int				bits;
	int				size_line;
	int				end;
}					t_textinfo;

typedef struct s_tex
{
	t_textinfo	no;
	t_textinfo	so;
	t_textinfo	we;
	t_textinfo	ea;
	t_textinfo	s;
}				t_tex;

typedef struct s_plr
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}			t_plr;

typedef struct s_spr
{
	double	x;
	double	y;
}			t_spr;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_ray;

typedef struct s_help
{
	float	floor_stepX;
	float	floor_stepY;
	float	floorX;
	float	floorY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	int		mapX;
	int		mapY;
	double	perp;
	int		draw_start;
	int		draw_end;
	double	wallX;
	int		texX;
	double	transformX;
	double	transformY;
	int		drawStartY;
	int		drawEndY;
	int		spriteHeight;
	int		spriteWidth;
	double	step;
	int		screenshot;
}			t_help;

typedef struct s_data
{
	void			*mlx;
	unsigned int	c;
	unsigned int	f;
	int				first_line;
	t_win			window;
	t_img			image;
	t_map			map;
	t_tex			texture;
	t_plr			player;
	t_spr			*sprites;
	t_ray			rays;
	t_help			a;
}					t_data;

typedef struct s_list
{
	int				fd;
	char			*ostatok;
	struct s_list	*next;
}				t_list;

void		ft_parser(char *map, t_data data);
void		check_after_reading(int bytes, int fd);
void		start_mlx(t_data *data);
void		lodev(t_data *data);

void		aim(t_data *data);
void		draw_bred(t_data *data);

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		fill_header1(t_data *data, int fd);
void		draw_screen(t_data *data, int fd);
void		create_bmp(t_data *data);
void		init_floor(t_data *data, int y);
void		draw_floor(t_data *data);
void		walls_part_one(t_data *data, int x);
void		walls_part_two(t_data *data, double deltaDistX, double deltaDistY,
				int x);
void		walls_part_three(t_data *data, int x, double deltaDistX, double
				deltaDistY);
void		walls_part_four(t_data *data, int side, int x, int line_hgt);
void		walls_part_five(t_data *data, double texPos, int side, int x);
void		draw_walls(t_data *data);
void		find_step(t_data *data, t_textinfo *texture, int line_hgt,
				int flag);
void		paint(t_data *data, t_textinfo *texture, int texY, int x);

void		walk_forward_backward(t_data *data, int keycode);
void		walk_aside(t_data *data, int keycode);
void		rotate(t_data *data, int keycode, double ol1, double ol2);
int			keyboard(int keycode, t_data *data);
int			ft_closed(t_data *data, int a);

void		map_plus_spaces(t_map *map);
void		check_map_2(t_map *map);
void		find_player_n_sprites(t_data *data);
void		final_check(t_data *data);
void		check_map(t_map *map);

void		get_resolution(char *line, int *i, t_win *win, t_data *data);
void		get_floor_ceiling(char *line, int *i, t_data *data);
void		get_texture(char *line, int *i, void **mlx, t_textinfo *text);
void		get_map(char *line, t_map *map);
void		current_line(char *line, t_data *data);
void		current_line2(char *line, int *i, t_data *data);

t_list		*ft_lstnew(int content);
char		*ft_strchr(char *s, char c);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char *s1, char *s2);
int			clear(t_list **list, int fd, char *buf, int code);
int			get_next_line(int fd, char **line);
char		*ft_empty(void);

void		ft_sortsprite(t_data *data, double *dist, int i);
void		sprites_part_three(t_data *data, int stripe, int spriteScreenX,
				double *ZBuffer);
void		sprites_part_two(t_data *data, int spriteScreenX, double *ZBuffer);
void		sprites_part_one(t_data *data, double *ZBuffer, int i);
void		draw_sprites(t_data *data, double *ZBuffer);

void		check_error2(int n);
void		check_error(int n);
int			ft_strlen(char *s);
long int	ft_atoi(char *nptr, int *i);
void		skip_spaces(char *line, int *i, int zpt);
void		first_spaces(char *line, int *i, t_data *data);
int			check_extension(char *str, char *ideal);
void		detect_direction(t_data *data, char c, int i, int j);
void		ft_bzero(void *s, size_t n);
int			defense(int X_or_Y, int texture);

#endif
