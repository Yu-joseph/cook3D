/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:01:10 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/15 16:15:49 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void load_img(t_game *game, t_path *l)
{
	// printf("%s\n", l->SO);
	
	game->so = mlx_load_png(l->SO);	
	game->no = mlx_load_png(l->NO);	
	game->we = mlx_load_png(l->WE);	
	game->ea = mlx_load_png(l->EA);	
	if (!game->so || !game->no || !game->ea || !game->we)
	{
		exit(write(2, "ERROR\nbad images\n", 17));
	}
	
}

void draw_texture(t_game *data)
{
	static double i = 0;
	// (void)data;
	// double x_txt;
	double s[2];
	if (s[0] < 0)
		s[0] = 0;
	s[1] = i;
	i += WALL_STRIP_WIDTH;
	s[0] = (H /  2) - (data-> / 2); 
	printf("ll=%f\n", s[0]);
	// while (i < NUM_RAYS)
	// {
		
	// 	// printf(" x = %f\n" , data->rays[i].x);
	// 	// printf(" y = %f\n" , data->rays[i].y);
	// 	i++;
	// }
	// printf("jjjj/jjj=%d\n",i);
	
}


int	main(int ac, char **av)
{
	t_path l;
	if(ac  != 2)
		return (1);
	(void) ac;
	t_game game;
	if(check_name(av[1]) == false)
		return (1);
	// game.map = check_map(av[1], &game);
	parse_map(check_map(av[1], &game), &game, &l);
	game.ply = init_ply();
	ft_mlx_init(&game);
	load_img(&game, &l);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	int i = 0;
	while (game.map[i])
	{
		// printf("%s\n",game.map[i]);
		free(game.map[i]);
		i++;
	}
	// system("leaks -q cub3D");
	return (0);
	//
	// t_game *game;

	// game = malloc(sizeof(t_game));
	
	
	// for(int i = 0; i < 3; i++)
	// 	printf("%s\n", game->map[i]);
}
