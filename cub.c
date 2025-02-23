/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:04:11 by eismail           #+#    #+#             */
/*   Updated: 2025/01/31 10:45:32 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include "cub3D.h"

bool	ft_mlx_init(t_game *data)
{
	mlx_image_t	*bg;

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
	if (!load_animation(data))
		return (false);
	return (true);
}

void	fill_rays(t_game *data, double *ray, int i, double dis)
{
	double	dis_plane;

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

void	minimap(t_game *d)
{
	int		x;
	int		y;
	int		*arry;
	size_t	c_x;
	int		c_y;

	c_x = 0;
	c_y = 0;
	arry = minimap_size(d);
	y = -1;
	while (++y < MINI_H - CELL)
	{
		x = -1;
		while (++x < MINI_W - CELL && (int)c_x < arry[2] && c_y < arry[3])
		{
			c_x = ((arry[0] + x) / CELL);
			c_y = ((arry[1] + y) / CELL);
			mlx_put_pixel(d->minimap, x, y, 0x000000CC);
			if (c_y >= 0 && c_y < d->h && c_x >= 0
				&& c_x < ft_strlen(d->map[c_y]) && d->map[c_y][c_x] == '1')
				mlx_put_pixel(d->minimap, x, y, 0xFFFFFF99);
		}
	}
	draw_square(d->minimap, MINI_W / 2, MINI_H / 2, PLAYER);
	free(arry);
}

t_ply_info	init_ply(void)
{
	t_ply_info	ply;

	ply.turn_direction = 0;
	ply.walk_direction = 0;
	ply.rotation_angle = 0;
	ply.side_angle = 0;
	ply.move_speed = 3;
	ply.rotationspeed = 2 * (M_PI / 180);
	ply.movestep = 0;
	return (ply);
}
