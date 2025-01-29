/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:17:36 by eismail           #+#    #+#             */
/*   Updated: 2025/01/28 12:38:07 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void chose_angle(t_game *data, char p)
{
	if (p == 'S')
		data->ply.rotation_angle = M_PI / 2;
	if (p == 'N')
		data->ply.rotation_angle = 3 * (M_PI / 2);
	if (p == 'W')
		data->ply.rotation_angle = M_PI;
	if (p == 'E')
		data->ply.rotation_angle = 0;
	data->ply.side_angle = data->ply.rotation_angle + (M_PI /2);
}

void rander_minimap(t_game *data, bool p)
{
	int i;
	int j;
	int x;
	int y;
	
	i = -1;
	while(data->map[++i])
	{
		j = -1;
		while(data->map[i][++j])
		{
			x = (j * CELL);
			y = (i * CELL);
			if (data->map[i][j] && data->map[i][j] == '1')
				mlx_image_to_window(data->mlx, data->wall, x, y);
			if (data->map[i][j] && (data->map[i][j] == 'S' || data->map[i][j] == 'W' 
				|| data->map[i][j] == 'N' || data->map[i][j] == 'E') && p)
			{
				chose_angle(data, data->map[i][j]);
				mlx_image_to_window(data->mlx, data->player, x, y);
				data->x = x;
				data->y = y;
			}
		}
	}
}

void reander_walls(t_game *data, double **rays)
{
	double dis;
	double dis_plane;
	double wall_height;
	double angle;
	int i;

	i = 0;
	angle = data->ply.rotation_angle - (FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		data->color = rays[i][2];
		data->rays[i].angle = angle;
		dis = distance(data->x, data->y, rays[i][0], rays[i][1]) * cos(angle - data->ply.rotation_angle);
		fill_rays(data, rays[i], i, dis);
		dis_plane = (W / 2) / tan(FOV_ANGLE / 2);
		wall_height = (CELL / dis) * dis_plane;
		// rectangle(data, i * WALL_STRIP_WIDTH, (H / 2) - (wall_height/ 2), WALL_STRIP_WIDTH, wall_height);
		i++;
		angle += FOV_ANGLE / NUM_RAYS;
	}
}
