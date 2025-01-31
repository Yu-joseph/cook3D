/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:55:39 by eismail           #+#    #+#             */
/*   Updated: 2025/01/29 13:39:12 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pint(mlx_image_t *img, int h, int w, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			mlx_put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}

t_line	*init_line(int x0, int y0, int x1, int y1)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	line->dy = y1 - y0;
	line->dx = x1 - x0;
	line->steps = 0;
	line->x_inc = 0;
	line->y_inc = 0;
	if (abs(line->dx) > abs(line->dy))
		line->steps = abs(line->dx);
	else 
		line->steps = abs(line->dy);
	line->x_inc = (float)line->dx / (float)line->steps;
	line->y_inc = (float)line->dy / (float)line->steps;
	return (line);
}

// void	draw_line(mlx_image_t *mlx, int x0, int y0, int x1, int y1)
// {
// 	int		i;
// 	t_line	*line;

// 	i = 0;
// 	line = init_line(x0, y0, x1, y1);
// 	while(i < line->steps && y0 >= 0 && x0 >= 0)
// 	{
// 		mlx_put_pixel(mlx, round(x0), round(y0), 0xFF0000FF);
// 		x0 += line->x_inc;
// 		y0 += line->y_inc;
// 		i++;
// 	}
// 	free(line);
// }

void	draw_square(void *img, int startx, int starty, int size)
{
	int	i;
	int	j;

	i = starty;
	while (i < (starty + size))
	{
		j = startx;
		while (j < (startx + size))
		{
			mlx_put_pixel(img, j, i, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

void	pint_bg(t_game *data, mlx_image_t *img, double x, double y)
{
	double	i;
	double	j;
	int		sky_color;
	int		flor_color;

	sky_color = rgb(data->path->c_r, data->path->c_g, data->path->c_b, 255);
	flor_color = rgb(data->path->f_r, data->path->f_g, data->path->f_b, 255);
	i = x;
	while (i < W)
	{
		j = y;
		while (j < H)
		{
			if (j < (y + (H / 2)))
				mlx_put_pixel(img, i, j, sky_color);
			else
				mlx_put_pixel(img, i, j, flor_color);
			j++;
		}
		i++;
	}
}
