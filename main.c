/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:01:10 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/13 22:38:34 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


// void load_img(t_game *game, t_path *l)
// {
// 	game->so = mlx_load_png(l->SO);	
// 	game->no = mlx_load_png(l->NO);	
// 	game->we = mlx_load_png(l->WE);	
// 	game->ea = mlx_load_png(l->EA);	
// 	if (!game->so || !game->no || !game->ea || !game->we)
// 	{
// 		exit(write(2, "ERROR\nbad images\n", 17));
// 	}
	
// 	// if (!xpm_file(l->EA) || !xpm_file(l->NO) || !xpm_file(l->SO) || !xpm_file(l->WE))
// 	// 	exit(write(2, "ERROR\nBad format\n",17));
// 	// (void) game;
// 	// mlx_xpm_file_to_image();
// }
// int calculate_wall_top(t_game *data, int ray_index)
// {
//     double wall_height = data->rays[ray_index].wall_height;  // Already stored
//     int wall_top = (data->h / 2) - (int)(wall_height / 2);   // Centered vertically
//     if (wall_top < 0) wall_top = 0;                          // Clamp to top of screen
//     return wall_top;
// }

// int calculate_wall_bottom(t_game *data, int i) 
// {
//     double wall_height = data->rays[i].wall_height;  // Same wall height as above
//     int wall_bottom = calculate_wall_top(data, i) + (int)wall_height;
//     if (wall_bottom > data->h) wall_bottom = data->h;        // Clamp to bottom of screen
//     return wall_bottom;
// }
// void set_pixel(mlx_image_t *img, int x, int y, int color) 
// {
//     int	i;
// 	int	j;

// 	j = 0;
// 	while(j < H)
// 	{
// 		i = 0;
// 		while(i < W)
// 		{
// 			mlx_put_pixel(img, i, j, color);
// 			i++;
// 		}
// 		j++;
// 	}
// }
// void draw_texter(t_game *data)
// {
// 	// load_img()
//     int i = 0;
//     while (i < data->rays)
//     {
//         int wall_top = calculate_wall_top(data, i);    // Calculate top pixel of the wall slice
//         int wall_bottom = calculate_wall_bottom(data, i);  // Bottom pixel of the wall slice
//         int wall_height = wall_bottom - wall_top;     // Height of the wall slice
//         int texture_x = calculate_texture_x(data, i); // Texture x-coordinate

//         int y = wall_top;
//         while (y <= wall_bottom)
//         {
//             int texture_y = ((y - wall_top) * data->ea->height) / wall_height;
// 			int texture_index = (texture_y * data->ea->width * (data->ea->bytes_per_pixel / 8)) + (texture_x * (data->ea->bytes_per_pixel / 8));
//             int color = *(int *)(data->ea->pixels + texture_index); // Assume data->ea->data is texture pixel data

//             set_pixel(data->im, i, y, color); // Draw pixel to screen image
//             y++;
//         }
//         i++;
//     }
// }


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
	// load_img(&game, &l);
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
