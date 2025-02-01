CC = cc

CFLAGS = -Wall -Wextra -Werror

LIB = libft/libft.a

SRC = cub.c get/get_next_line.c get/get_next_line_utils.c main.c map_y.c y_utils.c animation_utils.c calcul_utils.c draw_utils.c hook_utils.c render_utils.c wallhit_utils.c  ray_cast.c	dr.c\
		map_y2.c map_y3.c	map_y4.c	map_y5.c

LIB_SRC := libft/ft_isalpha.c    libft/ft_memcmp.c     libft/ft_strlcat.c    libft/ft_strrchr.c\
		libft/ft_atoi.c       libft/ft_isascii.c    libft/ft_memcpy.c     libft/ft_strlcpy.c    libft/ft_tolower.c\
		libft/ft_bzero.c      libft/ft_isdigit.c    libft/ft_memmove.c    libft/ft_strlen.c     libft/ft_toupper.c\
		libft/ft_calloc.c     libft/ft_isprint.c    libft/ft_memset.c     libft/ft_strncmp.c    libft/ft_strdup.c\
		libft/ft_isalnum.c    libft/ft_memchr.c     libft/ft_strchr.c     libft/ft_strnstr.c    libft/ft_substr.c\
		libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c\
		libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \

OBJ = $(SRC:.c=.o)
LIB_OBJ = $(LIB_SRC:.c=.o)

NAME = cub3D

HDR = cub3D.h
LIBH = libft/libft.h

MLX_LIB_PATH = MLX/build/libmlx42.a
GLFW_LIB_PATH = /goinfre/eismail/homebrew/opt/glfw/lib
MLX_LIB = -L$(MLX_LIB_PATH) -lMLX42
GLFW_LIB = -L$(GLFW_LIB_PATH) -lglfw

all: $(NAME)

$(NAME): $(OBJ) $(LIBH) $(LIB_OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIB)  $(MLX_LIB_PATH) $(GLFW_LIB) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus