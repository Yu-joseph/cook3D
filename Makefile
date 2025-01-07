CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LIB = libft/libft.a

SRC = cub.c get/get_next_line.c  get/get_next_line_utils.c main.c map_y.c y_utils.c 

OBJ = $(SRC:.c=.o)

NAME = cub3D

HDR = cub3D.h

MLX_LIB_PATH = MLX/build/libmlx42.a
GLFW_LIB_PATH = $(shell brew --prefix glfw)/lib
MLX_LIB = -L$(MLX_LIB_PATH) -lMLX42
GLFW_LIB = -L$(GLFW_LIB_PATH) -lglfw

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIB)  $(MLX_LIB_PATH) $(GLFW_LIB) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all