/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:22:36 by eismail           #+#    #+#             */
/*   Updated: 2025/01/31 11:15:54 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_img(t_game *data)
{
	int	i;

	i = 0;
	while (i < ANIM)
	{
		if (data->img[i])
			mlx_delete_image(data->mlx, data->img[i]);
		i++;
	}
}

void	txt_to_img_to_win(t_game *d, mlx_texture_t *texture, int i)
{
	d->img[i] = mlx_texture_to_image(d->mlx, texture);
	mlx_delete_texture(texture);
	mlx_image_to_window(d->mlx, d->img[i], (W / 2)
		- (d->img[i]->width / 2), H - d->img[i]->height);
	d->img[i]->enabled = false;
}

bool	load_animation(t_game *d)
{
	int				i;
	char			*img_name;
	char			*tmp;
	char			*nums;
	mlx_texture_t	*texture[ANIM];

	i = -1;
	nums = "123456789ABCDE";
	while (++i < ANIM)
	{
		img_name = ft_substr(nums, i, 1);
		tmp = ft_strjoin("a/", img_name);
		free(img_name);
		img_name = ft_strjoin(tmp, ".png");
		texture[i] = mlx_load_png(img_name);
		if (!texture[i])
			return (clean_img(d), free(tmp), free(img_name), false);
		d->img[i] = mlx_texture_to_image(d->mlx, texture[i]);
		txt_to_img_to_win(d, texture[i], i);
		free(tmp);
		free(img_name);
	}
	return (true);
}

void	animation(t_game *data)
{
	int			animation_speed;
	static int	current_image;

	animation_speed = 3;
	data->frame_counter++;
	if (data->frame_counter % animation_speed == 0)
	{
		data->img[current_image]->enabled = false;
		current_image = (current_image + 1) % ANIM;
		data->img[current_image]->enabled = true;
	}
}
