/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_y.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:09:58 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/29 13:23:52 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_arg(char **c)
{
	char	**l;
	int		j;

	l = NULL;
	j = -1;
	while (c[++j])
	{
		l = ft_split(c[j], ' ');
		if (str_long(l) != 1)
		{
			free_d(l);
			free_d(c);
			return (true);
		}
		free_d(l);
	}
	return (false);
}

void	check_path(char *str, t_path *l)
{
	int		i;
	char	**c;

	i = 0;
	if (ft_strncmp(str, "C ", 2) == 0 || ft_strncmp(str, "F ", 2) == 0)
	{
		i += 2;
		if (str[i] == ' ')
		{
			while (str[i])
			{
				if (str[i] != ' ')
					break ;
				i++;
			}
		}
		c = ft_split(&str[i], ',');
		if (str_long(c) != 3 || check_arg(c) == true)
		{
			exit(write(2, "ERROR\nerror many arg\n", 21));
		}
		check_number(c, l, str);
	}
	else
		handle_redir(str, l);
}

void	emt_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '1')
		{
			while (line[i])
			{
				if (line[i] == '\n' && line[i + 1] == '\n')
					exit(write(2, "Error\nemtpyline", 15));
				i++;
			}
			break ;
		}
		i++;
	}
}

void	parse_map(char **str, t_game *game, t_path *l)
{
	int		j;
	t_elem	elem;

	j = 0;
	init_elem(&elem);
	while (str[j])
	{
		if (str[j][0] == ' ')
			skip_sp(&str[j]);
		if (fill_elem(&str[j][0], &elem, l) == false)
			exit(write(2, "ERROR\nbad lines\n", 16));
		else if (elem.c == 1 && elem.f == 1 && elem.no == 1 
			&& elem.ea == 1 && elem.we == 1 && elem.so == 1)
			break ;
		j++;
	}
	if (elem.c != 1 || elem.f != 1 || elem.no != 1 
		|| elem.ea != 1 || elem.we != 1 || elem.so != 1)
		exit(write(2, "ERROR\nbad lines\n", 16));
	check_li(game->ls, str[j + 1]);
	handle_map(&str[j + 1]);
	game->map = &str[j + 1];
}
