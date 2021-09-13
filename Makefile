SRC = bmp.c drawing.c drawing2.c floor.c get_next_line.c get_next_line_utils.c get_next_line_utils2.c hooks.c main.c map_check.c parsing.c parsing2.c sprites.c utils.c utils2.c utils3.c
SRC_BONUS = ./bonus/bmp.c ./bonus/drawing.c ./bonus/drawing2.c ./bonus/floor.c ./bonus/get_next_line.c ./bonus/get_next_line_utils.c ./bonus/get_next_line_utils2.c ./bonus/hooks.c \
./bonus/main.c ./bonus/map_check.c ./bonus/parsing.c ./bonus/parsing2.c ./bonus/sprites.c ./bonus/utils.c ./bonus/utils2.c ./bonus/utils3.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MLX = mlxopengl
LXFLAGS = -lmlx -framework OpenGL -framework AppKit
SCREENSHOT = bitmap.bmp

MLXFT = mlxopengl/libmlx.a

NAME = cub3D
NAME_BONUS = cub3D_bonus

all: $(NAME)
$(NAME):  $(SRC) $(MLXFT) cub3d.h
	$(CC) $(SRC) $(CFLAGS) -o $(NAME) -L $(MLX) $(LXFLAGS)
$(MLXFT):
		make -C mlxopengl
clean:
	$(RM) $(NAME) $(NAME_BONUS) $(SCREENSHOT)
fclean: clean
	make clean -C mlxopengl
re: fclean all
bonus: $(SRC_BONUS) $(MLXFT) bonus/cub3d.h
	$(CC) $(SRC_BONUS) $(CFLAGS) -o $(NAME_BONUS) -L $(MLX) $(LXFLAGS)
start: $(NAME)
	./$(NAME) inv.cub
start_bonus: bonus
	./$(NAME_BONUS) ./bonus/inv.cub
save: $(NAME)
	./$(NAME) inv.cub --save
save_bonus: bonus
	./$(NAME_BONUS) ./bonus/inv.cub --save
.PHONY: all clean fclean re bonus start start_bonus save save_bonus

