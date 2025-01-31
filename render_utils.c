/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:17:36 by eismail           #+#    #+#             */
/*   Updated: 2025/01/31 10:12:00 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	chose_angle(t_game *data, char p)
{
	if (p == 'S')
		data->ply.rotation_angle = M_PI / 2;
	if (p == 'N')
		data->ply.rotation_angle = 3 * (M_PI / 2);
	if (p == 'W')
		data->ply.rotation_angle = M_PI;
	if (p == 'E')
		data->ply.rotation_angle = 0;
	data->ply.side_angle = data->ply.rotation_angle + (M_PI / 2);
}

void	rander_minimap(t_game *d, bool p)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	while (d->map[++i])
	{
		j = -1;
		while (d->map[i][++j])
		{
			x = (j * CELL);
			y = (i * CELL);
			if (d->map[i][j] && d->map[i][j] == '1')
				mlx_image_to_window(d->mlx, d->wall, x, y);
			if (d->map[i][j] && (d->map[i][j] == 'S' || d->map[i][j] == 'W' 
				|| d->map[i][j] == 'N' || d->map[i][j] == 'E') && p)
			{
				chose_angle(d, d->map[i][j]);
				mlx_image_to_window(d->mlx, d->player, x, y);
				d->x = x;
				d->y = y;
			}
		}
	}
}

void	reander_walls(t_game *data, double **rays)
{
	double	dis;
	double	angle;
	int		i;

	i = 0;
	angle = data->ply.rotation_angle - (FOV_ANGLE / 2);
	while (i < NUM_RAYS)
	{
		data->color = rays[i][2];
		data->rays[i].angle = angle;
		dis = distance(data->x, data->y, rays[i][0], rays[i][1]) 
			* cos(angle - data->ply.rotation_angle);
		fill_rays(data, rays[i], i, dis);
		i++;
		angle += FOV_ANGLE / NUM_RAYS;
	}
}

void	rectangle(t_game *data, double x, double y)
{
	double	i;
	double	j;

	i = x;
	while (i < (x + W))
	{
		j = y;
		while (j < (y + H))
		{
			mlx_put_pixel(data->game, i, j, data->color);
			j++;
		}
		i++;
	}
}
