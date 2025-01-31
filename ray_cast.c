/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:49:26 by eismail           #+#    #+#             */
/*   Updated: 2025/01/29 22:15:38 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	*ft_vertical(t_game *data, double startx, double starty, double angl)
{
	double	yinter;
	double	xinter;
	double	*steps;
	double	*verwallhit;

	steps = malloc(sizeof(double) * 2);
	xinter = floor(startx / CELL) * CELL;
	if (data->right)
		xinter += CELL;
	yinter = starty + ((xinter - startx) * tan(angl));
	steps[0] = CELL;
	if (data->left)
		steps[0] *= -1;
	steps[1] = CELL * tan(angl);
	if (data->up && steps[1] > 0)
		steps[1] *= -1;
	if (data->down && steps[1] < 0)
		steps[1] *= -1;
	if (data->left)
		verwallhit = wallhit(data, xinter - 0.0000001, yinter, steps);
	else
		verwallhit = wallhit(data, xinter, yinter, steps);
	return (free(steps), verwallhit);
}

double	*ft_horisontal(t_game *data, double startx, double starty, double angl)
{
	double	yinter;
	double	xinter;
	double	*steps;
	double	*horwallhit;

	steps = malloc(sizeof(double) * 2);
	yinter = floor(starty / CELL) * CELL;
	if (data->down)
		yinter += CELL;
	xinter = startx + ((yinter - starty) / tan(angl));
	steps[0] = CELL / tan(angl);
	steps[1] = CELL;
	if (data->up)
		steps[1] *= -1;
	if (data->left && steps[0] > 0)
		steps[0] *= -1;
	if (data->right && steps[0] < 0)
		steps[0] *= -1;
	if (data->up)
		horwallhit = wallhit(data, xinter, yinter - 0.000001, steps);
	else
		horwallhit = wallhit(data, xinter, yinter, steps);
	return (free(steps), horwallhit);
}

double	*get_distance(t_game *data, double *horwallhit, double *verwallhit)
{
	double	*d_arry;

	d_arry = malloc(sizeof(double) * 2);
	if (!d_arry)
		return (NULL);
	d_arry[0] = __INT_MAX__;
	d_arry[1] = __INT_MAX__;
	if (horwallhit && horwallhit[0] > 0 && horwallhit[1] > 0)
		d_arry[0] = distance(data->x, data->y, horwallhit[0], horwallhit[1]);
	if (verwallhit && verwallhit[0] > 0 && verwallhit[1] > 0)
		d_arry[1] = distance(data->x, data->y, verwallhit[0], verwallhit[1]);
	return (d_arry);
}

double	*cmp_hv(t_game *data, double startx, double starty, double angle)
{
	double	*wallhit;
	double	*distances;
	double	*horwallhit;
	double	*verwallhit;

	wallhit = malloc(sizeof(double) * 3);
	if (!wallhit)
		return (NULL);
	horwallhit = ft_horisontal(data, startx, starty, angle);
	verwallhit = ft_vertical(data, startx, starty, angle);
	distances = get_distance(data, horwallhit, verwallhit);
	if (distances[0] < distances[1])
	{
		wallhit[0] = horwallhit[0];
		wallhit[1] = horwallhit[1];
		wallhit[2] = rgb(0, 103, 72, 255);
	}
	else 
	{
		wallhit[0] = verwallhit[0];
		wallhit[1] = verwallhit[1];
		wallhit[2] = rgb(238, 216, 186, 255);
	}
	return (free(horwallhit), free(verwallhit), free(distances), wallhit);
}

void	cast_all_rays(t_game *data)
{
	int		colm;
	double	angle;
	double	*rays[NUM_RAYS];

	colm = 0;
	angle = data->ply.rotation_angle - (FOV_ANGLE / 2);
	while (colm < NUM_RAYS)
	{
		norm_engle(data, &angle);
		data->rays[colm].down = data->down;
		data->rays[colm].up = data->up;
		data->rays[colm].left = data->left;
		data->rays[colm].right = data->right;
		rays[colm] = cmp_hv(data, data->x, data->y, angle);
		colm++;
		angle += FOV_ANGLE / NUM_RAYS;
	}
	reander_walls(data, rays);
	colm = 0;
	while (colm < NUM_RAYS)
	{
		free(rays[colm]);
		colm++;
	}
}
// draw_line(data->line, data->x, data->y, 
	// rays[colm][0], rays[colm][1], 0xFF0000FF);
