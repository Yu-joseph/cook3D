/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_y4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:01:20 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/29 22:11:16 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	line_parse(char **str, t_game *g, int j, int c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[j][i])
	{
		if ((str[j][i] != ' ' && str[j][i] != '1' ) && (j == 0 || j == c - 1))
			exit(write(2, "ERROR\nMAP NOT VALID!!\n", 22));
		else if (str[j][i] == '0')
			map_checker(str, j, i);
		else if (str[j][i] != '0' && str[j][i] != '1' 
			&& str[j][i] != ' ' && is_redir(str[j][i]) == false)
			exit(write(2, "ERROR\nMAP NOT VALID!!\n", 22));
		else if (is_redir(str[j][i]) == true)
		{
			map_checker(str, j, i);
			g->x = i;
			g->y = j;
			x++;
		}
		i++;
	}
	return (x);
}

void	init_util(t_util *t)
{
	t->c = 0;
	t->i = 0;
	t->j = -1;
	t->x = 0;
}

bool	some_err(char c, t_util t)
{
	if (c != '0' && c != '1' && c != ' ' && is_redir(c) == false)
		return (true);
	else if (c != ' ' && c != '1' && (t.j == 0 || t.j == t.c - 1))
		return (true);
	return (false);
}

void	handle_map(char **str)
{
	t_util	t;

	init_util(&t);
	if (!str[t.j])
		exit(write(2, "ERROR\nno map\n", 13));
	while (str[t.c])
		t.c++;
	while (++t.j < t.c)
	{
		t.i = -1;
		while (str[t.j][++t.i])
		{
			if ((some_err(str[t.j][t.i], t) == true))
				exit(write(2, "ERROR\nMAqqqP NOT VALID!!\n", 25));
			else if (str[t.j][t.i] == '0')
				map_checker(str, t.j, t.i);
			else if (is_redir(str[t.j][t.i]) == true)
			{
				map_checker(str, t.j, t.i);
				t.x++;
			}
		}
	}
	if (t.x != 1)
		exit(write(2, "ERROR\nMAP NOT VALID!!\n", 22));
}

void	check_number(char **c, t_path *l, char *str)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!(ft_atoi(c[i]) <= 255 && ft_atoi(c[i]) >= 0))
			exit(write(2, "ERROR\nBAD RGB\n", 14));
		i++;
	}
	if (ft_strncmp(str, "C ", 2) == 0)
	{
		l->c_r = ft_atoi(c[0]);
		l->c_g = ft_atoi(c[1]);
		l->c_b = ft_atoi(c[2]);
	}
	else
	{
		l->f_r = ft_atoi(c[0]);
		l->f_g = ft_atoi(c[1]);
		l->f_b = ft_atoi(c[2]);
	}
	free_d(c);
}
