/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_y3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:56:01 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/29 22:08:08 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	skip_sp(char **str)
{
	while (**str)
	{
		if (**str != ' ')
			break ;
		(*str)++;
	}
}

bool	fill_elem(char *str, t_elem *elem, t_path *l)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		elem->no++;
	else if (ft_strncmp(str, "SO ", 3) == 0)
		elem->so++;
	else if (ft_strncmp(str, "WE ", 3) == 0)
		elem->we++;
	else if (ft_strncmp(str, "EA ", 3) == 0)
		elem->ea++;
	else if (ft_strncmp(str, "F ", 2) == 0)
		elem->f++;
	else if (ft_strncmp(str, "C ", 2) == 0)
		elem->c++;
	else
		return (false);
	check_path(str, l);
	return (true);
}

void	init_elem(t_elem *elem)
{
	elem->c = false;
	elem->f = false;
	elem->ea = false;
	elem->so = false;
	elem->no = false;
	elem->we = false;
	elem->path = NULL;
}

bool	check_elem(t_elem *elem)
{
	if (elem->c == 1 && elem->f == 1 && elem->no == 1 
		&& elem->ea == 1 && elem->we == 1 && elem->so == 1)
		return (true);
	return (false);
}

void	map_checker(char **str, int j, int i)
{
	if (i == 0)
		exit(write(2, "ERROR\nMAP NOT !\n", 16));
	else if (ft_strlen(str[j]) > (size_t)i && (str[j][i + 1] != '1' 
		&& str[j][i + 1] != '0' && is_redir(str[j][i + 1]) == false))
	{
		exit(write(2, "ERROR\nMAP NOT !\n", 16));
	}
	else if (j != 0 && (str[j - 1][i] != '1' 
		&& str[j - 1][i] != '0' && is_redir(str[j - 1][i]) == false))
	{
		exit(write(2, "ERROR\nMAP NOT VA=!!\n", 20));
	}
	else if (str_long(str) > j && (str[j + 1][i] != '1' 
		&& str[j + 1][i] != '0' && is_redir(str[j + 1][i]) == false))
	{
		exit(write(2, "ERROR\nMAP NOT VA=!!\n", 20));
	}
	else if (i != 0 && (str[j][i - 1] != '1' 
		&& str[j][i - 1] != '0' && is_redir(str[j][i - 1]) == false))
	{
		exit(write(2, "ERROR\nMAP NOT VA=!!\n", 20));
	}
}
