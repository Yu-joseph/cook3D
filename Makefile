CC = cc

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

LIB = libft/libft.a

SRC = cub.c get/get_next_line.c get/get_next_line_utils.c main.c map_y.c y_utils.c animation_utils.c calcul_utils.c draw_utils.c hook_utils.c render_utils.c wallhit_utils.c  ray_cast.c	dr.c\
		map_y2.c map_y3.c	map_y4.c	map_y5.c

OBJ = $(SRC:.c=.o)

NAME = cub3D

HDR = cub3D.h

MLX_LIB_PATH = MLX/build/libmlx42.a
GLFW_LIB_PATH = $(shell brew --prefix glfw)/lib
MLX_LIB = -L$(MLX_LIB_PATH) -lMLX42
GLFW_LIB = -L$(GLFW_LIB_PATH) -lglfw

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIB)  $(MLX_LIB_PATH) $(GLFW_LIB) -framework OpenGL -framework AppKit -o $(NAME)
	@echo "Done"

%.o: %.c $(HDR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C libft clean
	@rm -f $(OBJ)
	@echo "cleaned"

fclean: clean
	make -C libft fclean
	@rm -f $(NAME)
	@echo "fcleaned"

re: fclean all