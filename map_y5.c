/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_y5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:07:33 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/30 11:27:12 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_path(char *s, char *l, t_path *p)
{
	if (ft_strncmp(s, "NO", 2) == 0)
		p->no = ft_strdup(l);
	else if (ft_strncmp(s, "WE", 2) == 0)
		p->we = ft_strdup(l);
	else if (ft_strncmp(s, "SO", 2) == 0)
		p->so = ft_strdup(l);
	else if (ft_strncmp(s, "EA", 2) == 0)
		p->ea = ft_strdup(l);
}

void	handle_redir(char *str, t_path *s)
{
	int		i;
	char	**l;

	i = 2;
	l = ft_split(str, ' ');
	if (!l[1] || str_long(l) != 2)
		exit(write(2, "ERROR\nbad [PATH]\n", 17));
	i = open(l[1], O_RDONLY);
	if (i < 0)
		exit(write(2, "ERROR\ninvalid path\n", 19));
	else
		close(i);
	fill_path(l[0], l[1], s);
	free_d(l);
}

void	free_d(char **t)
{
	int	i;

	i = -1;
	while (t[++i])
	{
		free(t[i]);
	}
	free(t);
}
