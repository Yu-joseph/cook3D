/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_y.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:09:58 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/27 10:43:02 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_rest(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] != '\n')
			return (false);
		else if(str[i] == '\n')
			i++;
	}
	return true;
}

int		count_lingth(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return i;
}
bool is_valid(char c)
{
	if (c == '0' || c == '1')
		return (true);
	return (false);
}
void	check_li(char *line, char *str)
{
	int i = 0;
	bool err = false;
	if(!line || !str)
		exit(write(2, "ERROR\nMAPERROR\n",15));
	while(line[i])
	{
		if (ft_strncmp(&line[i], str, ft_strlen(str))== 0)
			break;
		i++;
	}
	while (line[i])
	{
		if (ft_strncmp(&line[i], "\n\n", 2) == 0 && err == false)
		{
			printf("here\n");
			err = true;
		}
		if(err == true && (is_redir(line[i]) == true || is_valid(line[i]) == true))
			exit(write(2, "Error\nemtp0yline", 16));
		i++;
	}
}
char	**check_map(char *str, t_game *game)
{
	int		fd;
	char	*tmp;
	char *t;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		exit(write(2, "Error\n", 6));
	game->ls = NULL;
	tmp = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break;
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

void	skip_sp(char **str)
{
	while (**str)
	{
		if (**str != ' ')
			break;
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
	if (elem->c == 1 && elem->f == 1 && elem->no == 1 && elem->ea == 1 && elem->we == 1 && elem->so == 1)
		return true;
	return (false);
}

void    map_checker(char **str, int j, int i)
{
	if (i == 0)
		exit(write(2, "ERROR\nMAP NOT !\n", 16));
    else if (ft_strlen(str[j]) > (size_t)i && (str[j][i+1] != '1' && str[j][i+1] != '0' && is_redir(str[j][i+1]) == false))
    {
        exit(write(2, "ERROR\nMAP NOT !\n", 16));
    }
    else if (j != 0 && (str[j-1][i] != '1' && str[j-1][i] != '0' && is_redir(str[j-1][i]) == false))
    {
        exit(write(2, "ERROR\nMAP NOT VA=!!\n", 20));
    }
    else if (str_long(str) > j &&(str[j+1][i] != '1' && str[j+1][i] != '0' && is_redir(str[j+1][i]) == false))
    {
        exit(write(2, "ERROR\nMAP NOT VA=!!\n", 20));
    }
    else if (i != 0 && (str[j][i-1] != '1' && str[j][i-1] != '0' && is_redir(str[j][i-1]) == false))
    {
        exit(write(2, "ERROR\nMAP NOT VA=!!\n", 20));
    }
}

int	line_parse(char **str, t_game *g, int j, int c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[j][i])
	{
		if ((str[j][i] != ' ' && str[j][i] != '1' ) && (j == 0 || j == c-1))
			exit(write(2, "ERROR\nMAP NOT VALID!!\n", 22));
		else if (str[j][i] == '0')
			map_checker(str, j, i);
		else if(str[j][i] != '0' && str[j][i] != '1' && str[j][i] != ' ' && is_redir(str[j][i]) == false)
			exit(write(2, "ERROR\nMAP NOT VALID!!\n", 22));
		else if (is_redir(str[j][i]) == true)
		{
			map_checker(str, j, i);
			g->x = i;
			g->y = j;
			x++;
		}
		printf("lslslls\n");
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
	t_util t;

	init_util(&t);
	if(!str[t.j])
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
	if(t.x != 1)
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
	// free_d(c);
}

void	fill_path(char *s, char *l, t_path *p)
{
	if (ft_strncmp(s, "NO", 2) == 0)
		p->NO = ft_strdup(l);
	else if (ft_strncmp(s, "WE", 2) == 0)
		p->WE = ft_strdup(l);
	else if (ft_strncmp(s, "SO", 2) == 0)
		p->SO = ft_strdup(l);
	else if (ft_strncmp(s, "EA", 2) == 0)
		p->EA = ft_strdup(l);
}
void	handle_redir(char *str, t_path *s)
{
	int i;
	char	**l;
	i = 2;

	l = ft_split(str, ' ');
	if(!l[1] || str_long(l) != 2)
		exit(write(2, "ERROR\nbad [PATH]\n", 17));
	i = open(l[1], O_RDONLY);
	if (i < 0)
		exit(write(2, "ERROR\ninvalid path\n", 19));
	else
		close(i);
	fill_path(l[0],l[1], s);
	free_d(l);
}

void	free_d(char **t)
{
	int i;

	i = -1;
	while (t[++i])
	{
		free(t[i]);
	}
	free(t);
}
bool	check_arg(char **c)
{
	char **l = NULL;
	int j = -1;
	while (c[++j])
	{
		l = ft_split(c[j], ' ');
		if(str_long(l) != 1)
		{
			free_d(l);
			return (true);
		}
		free_d(l);
	}
	return false;
}
void	check_path(char *str, t_path *l)
{
	int		i;
	char	**c;
	i = 0;
	if (ft_strncmp(str, "C ", 2) == 0 || ft_strncmp(str, "F ", 2) == 0)
	{
		i += 2;
		if(str[i] == ' ')
		{
			while (str[i])
			{
				if(str[i] != ' ')
					break;
				i++;
			}
		}
		c = ft_split(&str[i], ',');
		if(str_long(c) != 3 || check_arg(c) == true)
		{
			free_d(c);
			exit(write(2, "ERROR\nerror many arg\n", 21));
		}
		check_number(c, l, str);
		free_d(c);
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
		if (line[i] == '\n' && line[i+1] == '1')
		{
			while (line[i])
			{
				if (line[i] == '\n' && line[i + 1] == '\n')
					exit(write(2, "Error\nemtpyline", 15));
				i++;
			}
			break;
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
		if (fill_elem(&str[j][0], &elem , l) == false)
			exit(write(2, "ERROR\nbad lines\n", 16));
		else if (elem.c == 1 && elem.f == 1 && elem.no == 1 && elem.ea == 1 && elem.we == 1 && elem.so == 1)
			break;
		j++;
	}
	if (elem.c != 1 || elem.f != 1 || elem.no != 1 || elem.ea != 1 || elem.we != 1 || elem.so != 1)
		exit(write(2, "ERROR\nbad lines\n", 16));
	check_li(game->ls, str[j+1]);
	handle_map(&str[j+1]);
	game->map = &str[j+1];
}
