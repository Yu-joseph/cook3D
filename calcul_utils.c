/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:27:16 by eismail           #+#    #+#             */
/*   Updated: 2025/01/28 13:22:59 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	distance(double x0, double y0, double x1, double y1)
{
	return (sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0))));
}

void	norm_engle(t_game *data, double *angle)
{
	*angle = remainder(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle = (2 * M_PI) + *angle;
	if (*angle > 0 && *angle < M_PI)
		data->down = true;
	else
		data->down = false;
	if (*angle < 0.5 * M_PI || *angle > 1.5 * M_PI)
		data->right = true;
	else
		data->right = false;
	data->left = !data->right;
	data->up = !data->down;
}

int	ft_height(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_wedth(char **s)
{
	size_t	max_lenght;
	int		i;

	i = 0;
	max_lenght = ft_strlen(s[0]);
	while (s[i])
	{
		if (ft_strlen(s[i]) > max_lenght)
			max_lenght = ft_strlen(s[i]);
		i++;
	}
	return (max_lenght);
}

int	*minimap_size(t_game *data)
{
	int	*bounds;

	bounds = malloc(sizeof(int) * 4);
	if (!bounds)
		return (NULL);
	bounds[0] = (data->x - (MINI_W / 2));
	bounds[1] = (data->y - (MINI_H / 2));
	bounds[2] = (data->x + (MINI_W / 2));
	bounds[3] = (data->y + (MINI_H / 2));
	return (bounds);
}
