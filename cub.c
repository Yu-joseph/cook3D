/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:04:11 by eismail           #+#    #+#             */
/*   Updated: 2025/01/28 12:46:30 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include "cub3D.h"
	
void ft_mlx_init(t_game *data)
{
	mlx_image_t *bg;
	data->h = ft_height(data->map);
	data->w = ft_wedth(data->map);
	data->mlx = mlx_init(W, H, "cub", true);
	data->minimap = mlx_new_image(data->mlx, MINI_W, MINI_H);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	data->player = mlx_new_image(data->mlx, PLAYER, PLAYER);
	pint(data->player, PLAYER, PLAYER, 0xFF000000);
	bg = mlx_new_image(data->mlx, W, H);
	mlx_image_to_window(data->mlx, bg, 0, 0);
	pint_bg(data, bg, 0, 0);
	data->game = mlx_new_image(data->mlx, W, H);
	mlx_image_to_window(data->mlx, data->game, 0, 0);
	data->line = mlx_new_image(data->mlx, W, H);
	mlx_image_to_window(data->mlx, data->line, 0, 0);
	data->wall = mlx_new_image(data->mlx, CELL, CELL);
	pint(data->wall, CELL, CELL, 0xFFFFFF00);
    mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	rander_minimap(data, true);
	load_animation(data);
}

void fill_rays(t_game *data, double *ray, int i, double dis)
{
	double dis_plane;
	
	dis_plane = (W / 2) / tan(FOV_ANGLE / 2);
	data->rays[i].x = ray[0];
	data->rays[i].y = ray[1];
	data->rays[i].wall_height = (CELL / dis) * dis_plane;
	data->rays[i].distance = distance(data->x, data->y, ray[0], ray[1]);
	if (ray[2] == rgb(238, 216, 186, 255))
		data->rays[i].vertical = true;
	else
		data->rays[i].vertical = false;
}

void minimap(t_game *data)
{
	int x;
	int y;
	int *arry;
	size_t cell_x;
	int cell_y;

	cell_x = 0;
	cell_y = 0;
	arry = minimap_size(data);
	y = -1;
	while(++y < MINI_H - CELL)
	{
		x = -1;
		while(++x < MINI_W - CELL && (int)cell_x < arry[2] && cell_y < arry[3])
		{
			cell_x = ((arry[0] + x) / CELL);
			cell_y = ((arry[1] + y) / CELL);
			mlx_put_pixel(data->minimap, x, y, 0x000000CC);
			if (cell_y >= 0 && cell_y < data->h && cell_x >= 0 
				&& cell_x < ft_strlen(data->map[cell_y]) && data->map[cell_y][cell_x] == '1')
				mlx_put_pixel(data->minimap, x, y, 0xFFFFFF99);
		}
	}
	draw_square(data->minimap, MINI_W / 2 , MINI_H / 2, PLAYER, 0xFF0000FF);
	free(arry);
}

t_ply_info init_ply()
{
	t_ply_info ply;
	ply.turn_direction = 0; // -1 if left , +1 if right
	ply.walk_direction = 0; // -1 if back , +1 if front
	ply.rotation_angle = 0;
	ply.side_angle = 0;
	ply.move_speed = 2.0;
	ply.rotationSpeed = 2 * (M_PI / 180);
	ply.movestep = 0;
	return (ply);
}
