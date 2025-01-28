/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:55:39 by eismail           #+#    #+#             */
/*   Updated: 2025/01/28 12:54:33 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void pint(mlx_image_t *img, int h, int w, int color)
{
	int i;
	int j;
	
	i =0;
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

void draw_square(void *img, int startx, int starty, int size, int color) 
{
    int i;
	int j;
	
	i = starty;
    while (i < (starty + size)) 
	{
		j = startx;
        while (j < (startx + size)) 
		{
            mlx_put_pixel(img,j , i, color);
			j++;
		}
		i++;
    }
}

void pint_bg(t_game *data, mlx_image_t *img, double x, double y)
{
	double i;
	double j;
	int sky_color;
	int flor_color;
	(void) data;
	sky_color = rgb(125, 166, 189, 255);
	flor_color = rgb(117,107,93,255);
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

void rectangle(t_game *data, double x, double y, double width, double height)
{
	double i;
	double j;
	if (x < 0)
		x = 0;
    if (y < 0) 
		y = 0;
    if (x + width > data->game->width)
		width = data->game->width - x;
    if (y + height > data->game->height)
		height = data->game->height - y;
	
	i = x;
	while (i < (x + width))
	{	
		j = y;
		while (j < (y + height))
		{
			mlx_put_pixel(data->game, i, j, data->color);
			j++;
		}
		i++;
	}
}