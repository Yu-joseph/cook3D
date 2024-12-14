/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:04:11 by eismail           #+#    #+#             */
/*   Updated: 2024/12/14 12:06:28 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include "cub.h"

static mlx_image_t* image;
static mlx_image_t* player;

int close_window(int keycode, void *param)
{
    (void) param;
    if (keycode == 53) // 53 is the keycode for the ESC key on macOS
        exit(0);
    return (0);
}
int cross(t_game *data)
{
    (void) data;
        exit(0);
    return (0);
}
int	ft_height(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_wedth(char **s)
{
	return (ft_strlen(s[0]));
}

void desplay_wall(t_game *data, int x, int y)
{
    (void) data;
    for (int dx = 0; dx < CELL; dx++)
    {
        for (int dy = 0; dy < CELL; dy++)
        {
            mlx_put_pixel(image, x + dx, y + dy, 0xFFFFFFFF);
        }
    }
}

void desplay_player(t_game *data, int x, int y)
{
    (void) data;
       int player_offset = (CELL - PLAYER) / 2;
        for (int dx = 0; dx < PLAYER; dx++)
        {
            for (int dy = 0; dy < PLAYER; dy++)
            {
                mlx_put_pixel(player, x + player_offset +dx, y + player_offset +dy, 0xFF0000FF);
            }
        }
}

void pint(mlx_image_t *img, int h, int w, int color)
{
    int i;
    int j;
    
    i =0;
    while (i < h)
    {
        j =0;
        while (j < w)
        {
            mlx_put_pixel(img, i, j, color);
            j++;
        }
        i++;
    }
}

void desplay_map(t_game *data)
{
    int h;
    int w;
    int i;
    int j;
    
    h = ft_height(data->map) * CELL;
    w = ft_wedth(data->map) * CELL;
    data->h = ft_height(data->map);
    data->w = ft_wedth(data->map);
    data->mlx = mlx_init(320, 200, "cub", true);
    image = mlx_new_image(data->mlx, w, h);
    player = mlx_new_image(data->mlx, 5, 5);
    pint(player, 5, 5, 0xFF0000FF);
    mlx_image_to_window(data->mlx, image, 0, 0);
    
    i = 0;
    j = 0;
    int x;
    int y;
    while(data->map[i])
    {
        for (j = 0; data->map[i][j]; j++)
        {
            x = j * CELL;
            y = i * CELL;
            if (data->map[i][j] == '1')
                desplay_wall(data, x, y);
            if (data->map[i][j] == 'P')
            {
                mlx_image_to_window(data->mlx, player, x, y);
                data->x = j;
                data->y = i;
            }
        }
        i++;
    }
}

void ft_hook(void* param)
{
	t_game* data = param;
    mlx_t * mlx = data->mlx;
    int x = player->instances->x;
    int y = player->instances->y;
    int cell_x = x / CELL;
    int cell_y = y / CELL;
    data->ply.x = cell_x;
    data->ply.y = cell_y;
    
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
    {
        // if (data->map[(y - 1) / CELL][cell_x] != '1' &&
        //     data->map[(y - 1) / CELL][(x + PLAYER - 1) / CELL] != '1')
        //     {
        //         player->instances->y -= 1;
        //         data->ply.walk_direction = +1;
        //     }
        image->instances->y = -1;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
    {
        // if (data->map[(y + PLAYER) / CELL][cell_x] != '1' &&
        //     data->map[(y + PLAYER) / CELL][(x + PLAYER - 1) / CELL] != '1')
        //     {
        //         player->instances->y += 1;
        //         data->ply.walk_direction = -1;
        //     }
        image->instances->y = +1;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
    {
        // if (data->map[cell_y][(x - 1) / CELL] != '1' &&
        //     data->map[(y + PLAYER - 1) / CELL][(x - 1) / CELL] != '1')
        //     {
		//         player->instances->x -= 1;
        //         data->ply.turn_direction = +1;
        //     }
        image->instances->x = -1;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
    {
        // if (data->map[cell_y][(x + PLAYER) / CELL] != '1' && 
        //     data->map[(y + PLAYER - 1) / CELL][(x + PLAYER) / CELL] != '1')
        //     {
		//         player->instances->x += 1;  
        //         data->ply.turn_direction = -1;
        //     }
        image->instances->x = +1;
    }
}

char **get_map(char *file)
{
    int fd;
    char *map;
    char *temp;
    char *line;

    fd = open(file, O_RDONLY);
    map = get_next_line(fd);
    while ((line = get_next_line(fd)) != NULL)
    {
        temp = map;
        map = ft_strjoin(map, line);
        free(temp);
        free(line);
    }
    close(fd);
    return (ft_split(map, '\n'));
}

t_ply_info init_ply()
{
    t_ply_info ply;
    ply.turn_direction = 0; // -1 if left , +1 id right
    ply.walk_direction = 0; // -1 if back , +1 id front
    ply.rotation_angle = M_PI / 2;
    ply.move_speed = 2;
    ply.rotationSpeed = 2 * (M_PI / 180);
    return (ply);
}

int main(int ac, char **av)
{
    (void) ac;
    t_game game;
    
    game.ply = init_ply();
    game.map = get_map(av[1]);
    desplay_map(&game);
    mlx_loop_hook(game.mlx, ft_hook, &game);
    mlx_loop(game.mlx);
    int i = 0;
    while (game.map[i])
    {
        free(game.map[i]);
        i++;
    }
    free(game.map);
    return (0);
}
