/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallhit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:53:17 by eismail           #+#    #+#             */
/*   Updated: 2025/01/31 10:05:17 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	phaswall(double x, double y, t_game *data)
{
	int	cell_x;
	int	cell_y;
	int	dx;
	int	dy;

	if (x < 0 || x > (data->w * CELL) || y < 0 || y > (data->h * CELL))
		return (true);
	if ((size_t)floor(x / CELL) 
		>= ft_strlen(data->map[(size_t)floor(y / CELL)]))
		return (true);
	dx = 0; 
	while (dx < PLAYER)
	{
		dy = 0;
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

bool	haswall(double x, double y, t_game *data)
{
	long	cell_x;
	long	cell_y;

	cell_x = floor(x / CELL);
	cell_y = floor(y / CELL);
	if (x < 0 || x > (data->w * CELL) || y < 0 || y > (data->h * CELL))
		return (true);
	if ((size_t)(cell_x) >= ft_strlen(data->map[cell_y]))
		return (true);
	if (data->map[cell_y][cell_x] == '1')
		return (true);
	return (false);
}

double	*wallhit(t_game *data, double xinter, double yinter, double *steps)
{
	double	*wallhit;

	wallhit = ft_calloc(sizeof(double), 2);
	while ((yinter >= 0 && xinter >= 0 && yinter < (data->h * CELL)
			&& xinter < (data->w * CELL) && (size_t)floor(xinter / CELL)
			< ft_strlen(data->map[(size_t)floor(yinter / CELL)])))
	{
		if (haswall(xinter, yinter, data))
		{
			wallhit[0] = xinter;
			wallhit[1] = yinter;
			break ;
		}
		else
		{
			xinter += steps[0];
			yinter += steps[1];
		}
	}
	return (wallhit);
}
