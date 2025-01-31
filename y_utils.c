/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:26:18 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/29 22:15:18 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_redir(char c)
{
	if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
		return (true);
	return (false);
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

bool	check_name(char *str)
{
	bool	x;
	int		i;

	i = 0;
	x = false;
	while (str[i])
	{
		if (str_cmp(&str[i], ".cub") == 0 && str_len(&str[i]) >= 4)
			x = true;
		else if (str_len(&str[i]) >= 4)
			x = false;
		i++;
	}
	return (x);
}

int	str_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	str_long(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
