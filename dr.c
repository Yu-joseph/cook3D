/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:48:15 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/30 11:26:12 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_img(t_game *game, t_path *l)
{
	game->so = mlx_load_png(l->so);
	game->no = mlx_load_png(l->no);
	game->we = mlx_load_png(l->we);
	game->ea = mlx_load_png(l->ea);
	if (!game->so || !game->no || !game->ea || !game->we)
	{
		exit(write(2, "ERROR\nbad images1\n", 18));
	}
	game->i_no = mlx_texture_to_image(game->mlx, game->no);
	game->i_so = mlx_texture_to_image(game->mlx, game->so);
	game->i_we = mlx_texture_to_image(game->mlx, game->we);
	game->i_ea = mlx_texture_to_image(game->mlx, game->ea);
	if (!game->i_so || !game->i_no || !game->i_ea || !game->i_we)
	{
		exit(write(2, "ERROR\nbad images\n", 17));
	}
	game->clr.ea = get_pixels(game->i_ea);
	game->clr.so = get_pixels(game->i_so);
	game->clr.no = get_pixels(game->i_no);
	game->clr.we = get_pixels(game->i_we);
}

int	**get_pixels(mlx_image_t *img)
{
	int	**pixels;
	int	i;
	int	j;
	int	count;
	int	*pixel;

	i = 0;
	count = 0;
	if (!img)
		return (NULL);
	pixels = malloc(sizeof(int *) * img->height);
	while (i < (int) img->height)
	{
		j = 0;
		pixel = malloc(sizeof(int) * img->width);
		while (j < (int)img->width)
		{
			pixel[j++] = rgb(img->pixels[count], img->pixels[count + 1], 
					img->pixels[count + 2], img->pixels[count + 3]);
			count += 4;
		}
		pixels[i++] = pixel;
	}
	return (pixels);
}

mlx_image_t	*get_texture(t_game *data, int ***clr, int i)
{
	if (data->rays[i].vertical)
	{
		if (data->rays[i].right) 
		{
			*clr = data->clr.ea;
			return (data->i_ea);
		}
		*clr = data->clr.we;
		return (data->i_we);
	}
	else
	{
		if (data->rays[i].up)
		{
			*clr = data->clr.no;
			return (data->i_no);
		}
		else
		{
			*clr = data->clr.so;
			return (data->i_so);
		}
	}
}

void	count_x(t_game *data, mlx_image_t *txt, int i)
{
	data->img_x = 0;
	data->img_y = 0;
	if (data->rays[i].vertical == true)
		data->img_x = ((data->rays[i].y / CELL) 
				- floor(data->rays[i].y / CELL)) * txt->height;
	else
		data->img_x = ((data->rays[i].x / CELL) 
				- floor(data->rays[i].x / CELL)) * txt->height;
}

void	draw_wall(t_game *data, double t_pix, double b_pix, int i)
{
	int			**color;
	mlx_image_t	*txt;
	int			j;

	j = -1;
	txt = get_texture(data, &color, i);
	count_x(data, txt, i);
	data->texture_step = txt->height / data->rays[i].wall_height;
	if (data->rays[i].wall_height > H)
		data->texture_pos = data->texture_step 
			* ((data->rays[i].wall_height - H) / 2);
	else
		data->texture_pos = 0;
	while (++j < data->rays[i].wall_height)
	{
		if (t_pix + j >= H)
			break ;
		if (t_pix + j >= 0)
		{
			data->img_y = (int)data->texture_pos % txt->height;
			mlx_put_pixel(data->game, b_pix, (t_pix + j),
				color[data->img_y][data->img_x]);
		}
		data->texture_pos += data->texture_step;
	}
}
