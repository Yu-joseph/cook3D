/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:01:10 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/31 11:10:01 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_texture(t_game *data)
{
	int		i;
	double	t_pix;
	double	b_pix;

	t_pix = 0;
	b_pix = 0;
	i = 0;
	while (i < NUM_RAYS)
	{
		t_pix = (H / 2) - (data->rays[i].wall_height / 2);
		if (t_pix < 0)
			t_pix = 0;
		draw_wall(data, t_pix, b_pix, i);
		b_pix += WALL_STRIP_WIDTH;
		i++;
	}
}

void	free_int(int **arry, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		free(arry[i]);
	}
	free(arry);
}

void	free_path(t_path *p, t_game *g)
{
	free(p->ea);
	free(p->so);
	free(p->we);
	free(p->no);
	if (!g)
		return ;
	free_int(g->clr.ea, g->i_ea->height);
	mlx_delete_image(g->mlx, g->i_ea);
	mlx_delete_texture(g->ea);
	free_int(g->clr.so, g->i_so->height);
	mlx_delete_image(g->mlx, g->i_so);
	mlx_delete_texture(g->so);
	free_int(g->clr.no, g->i_no->height);
	mlx_delete_image(g->mlx, g->i_no);
	mlx_delete_texture(g->no);
	free_int(g->clr.we, g->i_we->height);
	mlx_delete_image(g->mlx, g->i_we);
	mlx_delete_texture(g->we);
}

// void	aa(void)
// {
// 	system("leaks cub3D");
// }

int	main(int ac, char **av)
{
	t_path	l;
	char	**map;
	t_game	game;

	if (ac != 2)
		return (1);
	(void) ac;
	if (check_name(av[1]) == false)
		return (1);
	map = check_map(av[1], &game);
	parse_map(map, &game, &l);
	game.path = &l;
	game.ply = init_ply();
	if (!ft_mlx_init(&game))
		return (free_path(&l, NULL), free_d(map), free(game.ls), 1);
	load_img(&game, &l);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	clean_img(&game);
	free_path(&l, &game);
	free_d(map);
	free(game.ls);
	return (0);
}
