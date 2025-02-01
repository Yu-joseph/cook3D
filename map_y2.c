/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_y2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:53:16 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/29 19:29:11 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_rest(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != '\n')
			return (false);
		else if (str[i] == '\n')
			i++;
	}
	return (true);
}

int	count_lingth(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i);
}

bool	is_valid(char c)
{
	if (c == '0' || c == '1')
		return (true);
	return (false);
}

void	check_li(char *line, char *str)
{
	int		i;
	bool	err;

	i = 0;
	err = false;
	if (!line || !str)
		exit(write(2, "ERROR\nMAPERROR\n", 15));
	while (line[i])
	{
		if (ft_strncmp(&line[i], str, ft_strlen(str)) == 0)
			break ;
		i++;
	}
	while (line[i])
	{
		if (ft_strncmp(&line[i], "\n\n", 2) == 0 && err == false)
			err = true;
		if (err == true && (is_redir(line[i]) == true 
				|| is_valid(line[i]) == true))
			exit(write(2, "Error\nemtp0yline", 16));
		i++;
	}
}

char	**check_map(char *str, t_game *game)
{
	int		fd;
	char	*tmp;
	char	*t;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		exit(write(2, "Error\nxxx\n", 10));
	game->ls = NULL;
	tmp = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		t = ft_strjoin(game->ls, tmp);
		free(game->ls);
		game->ls = ft_strdup(t);
		free(t);
		free(tmp);
	}
	close(fd);
	if (!game->ls)
		exit(write(2, "Error\nEMTHY\n", 12));
	return (ft_split(game->ls, '\n'));
}
