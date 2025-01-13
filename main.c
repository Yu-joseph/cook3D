/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:01:10 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/13 14:40:58 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	//
	if(ac  != 2)
		return (1);
	(void) ac;
	t_game game;
	if(check_name(av[1]) == false)
		return (1);
	// game.map = check_map(av[1], &game);
	parse_map(check_map(av[1], &game), &game);
	game.ply = init_ply();
	ft_mlx_init(&game);
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
