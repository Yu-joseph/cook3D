/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:04:11 by eismail           #+#    #+#             */
/*   Updated: 2024/12/18 13:54:40 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include "cub.h"

static mlx_image_t* wall;
static mlx_image_t* player;
// static mlx_image_t *line;

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
    data->mlx = mlx_init(w, h, "cub", true);
    wall = mlx_new_image(data->mlx, 30, 30);
    player = mlx_new_image(data->mlx, PLAYER, PLAYER);
    pint(player, PLAYER, PLAYER, 0xFF0000FF);
    pint(wall, 30, 30, 0xFFFFFFFF);
    data->line = mlx_new_image(data->mlx, w, h);
    mlx_image_to_window(data->mlx, data->line, 0, 0);

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
            {
                mlx_image_to_window(data->mlx, wall, x, y);
            }
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

void draw_line(mlx_image_t *mlx, int x0, int y0, int x1, int y1, int color)
{
	int dy = y1 - y0;
	int dx = x1 - x0;
	int steps = 0;;
	float	x_inc = 0;
	float	y_inc = 0;
	int i = 0;
	float y = y0;
	float x = x0;

	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else 
		steps = abs(dy);
	x_inc = (float)dx / (float)steps;
	y_inc = (float)dy / (float)steps;
	while(i < steps && y >= 0 && x >= 0)
	{
		mlx_put_pixel(mlx, round(x), round(y), color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

bool haswall(double x, double y, t_game *data)
{
    int cell_x;
    int cell_y;
    
    if (x < 0 || x > (data->w * CELL) || y < 0 || y > (data->h * CELL))
        return (true);
    int dx = 0; 
    while(dx < PLAYER)
    {
        int dy = 0;
        while (dy < PLAYER)
        {
            cell_x = floor((x + dx) / CELL);
            cell_y = floor((y + dy) / CELL);
            if (data->map[cell_y][cell_x] == '1')
                return (true);
            dy += PLAYER - 1;
        }
        dx += PLAYER - 1;
    }
    return (false);
}

long h_intersec(t_game *data, double x, double y, double angl)
{
    long xinter;
    long yinter;
    long xstep;
    long ystep;
    long count;

    count = 0;
    yinter = round(y / CELL) * CELL;
    xinter = x + ((y - yinter) / tan(angl));
    xstep = CELL / tan(angl);
    ystep = CELL;
    printf("xstep %ld\n",xstep);
    ystep *= data->up ? -1 : 1;
    xstep *= (data->left && xstep > 0) ? -1 : 1;
    xstep *= (data->right && xstep < 0) ? -1 : 1;
    while ((yinter >= 0 && xinter >= 0 && xinter < (data->w * CELL) && yinter < (data->h * CELL)))
    {
        if (data->map[yinter/CELL][xinter/CELL] == 1)
            break;
        xinter += xstep;
        yinter += CELL;
        count++;
    }
    return (count);
}

int v_intersec(t_game *data, double x, double y, double angl)
{
    long xinter;
    long yinter;
    long ystep;
    long count;

    count = 0;
    yinter = round(y / CELL) * CELL;
    xinter = x + ((y - yinter) / tan(angl));
    ystep = CELL * tan(angl);
    // printf("ystep %ld\n",ystep);
    while ((yinter >= 0 && xinter >= 0 && xinter < (data->w * CELL) && yinter < (data->h * CELL)))
    {
        // printf("count = %ld \n",count);
        if (data->map[yinter / CELL][xinter / CELL] == 1)
            break;
        xinter += CELL;
        yinter += ystep;
        count++;
    }
    return (count);
}

double* closest(t_game *data, double angl)
{
    long v_inter;
    long h_inter;
    long xstep;
    long ystep;
    double *end;

    end = malloc(sizeof(double) * 2);
    if (!end)
        return (NULL);
    xstep = CELL / tan(angl);
    ystep = CELL * tan(angl);
    v_inter = v_intersec(data, data->x , data->y, angl);
    h_inter = h_intersec(data, data->x , data->y, angl);
    // printf("v = %ld h = %ld\n", v_inter, h_inter);
    if (v_inter < h_inter)
    {
        end[0] = (v_inter * CELL);
        end[1] = (h_inter * ystep);
    }
    else
    {
        end[0] = (v_inter * xstep);
        end[1] = (h_inter * CELL);
    }
    return (end);
}

void cast_all_rays(t_game *data)
{
    int colm;
    double angl;
    double startx;
    double starty;
    // double *end;
    
    startx = data->x + (PLAYER) / 2;
    starty = data->y + (PLAYER) / 2;
    colm = 0;
    // angl = data->ply.rotation_angle;
    angl = fmod(data->ply.rotation_angle , (2 * M_PI));
    if (angl < 0)
        angl = (2 * M_PI) + angl;
    printf("angl %f \n", angl / (M_PI / 180));
    data->down   = angl > 0 && angl < M_PI;
    data->up     = !data->down;
    data->right  = angl < 0.5 * M_PI || angl > 1.5 * M_PI;
    data->left   = !data->right;
    // draw_line(data->line, startx, starty, data->x + (cos(angl) * 60), (data->y) + (sin(angl) * 60), 0xFFFF00FF);
    // end = closest(data, angl / (M_PI / 180));
    // printf("x = %f y = %f\n", end[0], end[1]);
    // draw_line(data->line, startx, starty,startx +  end[0], starty + end[1], 0xFFFF00FF);
    // free(end);
    angl = data->ply.rotation_angle - (FOV_ANGLE / 2);
    while (colm < NUM_RAYS)
    {
        draw_line(data->line, startx, starty, data->x + (cos(angl) * 60), (data->y) + (sin(angl) * 60), 0xFFFF00FF);
        colm++;
        angl += FOV_ANGLE / NUM_RAYS;
    }
}

void ft_hook(void* param)
{
    t_game* data = param;
    mlx_t * mlx = data->mlx;
    data->x = player->instances->x;
    data->y = player->instances->y;
    double movestep;
    
    data->ply.turn_direction = 0;
    data->ply.walk_direction = 0;
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
    if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
        data->ply.walk_direction = +1;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
        data->ply.walk_direction = (-1);

    if (mlx_is_key_down(mlx, MLX_KEY_A) && !haswall(data->x-1, data->y, data))
        player->instances->x -= 1; 
    if (mlx_is_key_down(mlx, MLX_KEY_D)  && !haswall(data->x+1, data->y, data))
        player->instances->x += 1; 
        
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        data->ply.turn_direction = (-1);
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        data->ply.turn_direction = (+1);
    data->ply.rotation_angle += data->ply.turn_direction * data->ply.rotationSpeed;  
    movestep = data->ply.walk_direction * data->ply.move_speed;
    
    double newx = player->instances->x + round(cos(data->ply.rotation_angle) * movestep);
    double newy = player->instances->y + round(sin(data->ply.rotation_angle) * movestep);
    if (!haswall(newx, newy, data))
    {
        player->instances->x = newx;
        player->instances->y = newy;
    }
    mlx_delete_image(mlx, data->line);
    data->line = mlx_new_image(data->mlx, data->w * CELL, data->h * CELL);
    mlx_image_to_window(data->mlx, data->line, 0, 0);
    cast_all_rays(data);
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
    ply.move_speed = 2.0;
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
